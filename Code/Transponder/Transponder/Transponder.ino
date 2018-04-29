/*
 Name:		Transponder.ino
 Created:	4/23/2018 12:08:16 PM
 Author:	paula
*/
#include <LiquidCrystal.h>
#include "transponderStrings.h"
#include "PinRefs.h"
#include "RadioMessages.h"

#include <SPI.h>
#include <SD.h>

#define DEBUG 0

enum DisplayStateOptions {
	LowPowerMode,
	ActiveMode,
	ArmedMode,
	GPSData,
	AltitudeData,
	TemperatureData,
	FlightData,
	SpeedData
};

enum ModeState {
	OFF,
	SENDING,
	ON
};

ModeState LowPowerState;
ModeState ActiveState;
ModeState ArmedState;

DisplayStateOptions TransponderState;

bool CubesatConnected = false;

// Push Buttons
int LeftButtonState = 0;
int RightButtonState = 0;
int SelectButtonState = 0;

bool LeftPressed = false;
bool RightPressed = false;
bool SelectPressed = false;

// LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//Thermistor
float thermData[3] = { 0,0,0 };

//Light sensor
float lightValue = 0;

//Accelerometer
float accData[3] = { 0,0,0 };

//Gyroscope
float gyroData[3] = { 0,0,0 };

//Pressure sensor
float pressureData = 0;

//GPS
float gpsData[2] = { 0,0 };

int fileUID;	//append this to filenames to avoid overwriting files

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LeftButton, INPUT);
	pinMode(RightButton, INPUT);
	pinMode(SelectButton, INPUT);
	lcd.begin(16, 2);
	TransponderState = LowPowerMode;
	CreateLowPowerMode();

	fileUID = random(32767);

	//Initialize SD Card
	if (!SD.begin()) {
#ifdef DEBUG
		Serial.println("initialization failed!");
#endif // DEBUG		
		return;
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	LeftButtonState = digitalRead(LeftButton);
	RightButtonState = digitalRead(RightButton);
	if (LeftButtonState == HIGH && !LeftPressed) {
		LeftPressed = true;
		switchDisplayState(false);
	}
	if (LeftButtonState == LOW) LeftPressed = false;

	if (RightButtonState == HIGH && !RightPressed) {
		RightPressed = true;
		switchDisplayState(true);
	}
	if (RightButtonState == LOW) RightPressed = false;
}


void ParseMessage(String data) {
	char messageType = data[1];
	char messageSource = data[2];

	if (messageType == ERROR_MESSAGE) {
		//TODO: Handle Error Logic
	}
	else if (messageType == DATA_MESSAGE) {
		if (messageSource == INSTR_SOURCE) {
			char instrMessage = data[3];
			if (instrMessage == THERMISTOR) {
				int* startChar = (int*)4;
				int thermistorNumber = ParseInt(data, startChar);
				(*startChar)++;
				float thermistorData = ParseFloat(data, startChar);
				UpdateThermistorData(thermistorNumber, thermistorData);
			}
			else if (instrMessage == AMBIENT_LIGHT) {
				int* startChar = (int*)4;
				float lightData = ParseFloat(data, startChar);
				UpdateLightData(lightData);
			}
			else if (instrMessage == ACCELEROMETER) {
				int* startChar = (int*)4;
				int accNumber = ParseInt(data, startChar);
				(*startChar)++;
				float accDataX = ParseFloat(data, startChar);
				(*startChar)++;
				float accDataY = ParseFloat(data, startChar);
				(*startChar)++;
				float accDataZ = ParseFloat(data, startChar);
				UpdateAccData(accNumber, accDataX, accDataY, accDataZ);
			}
			else if (instrMessage == GYROSCOPE) {
				int* startChar = (int*)4;
				int gyroNumber = ParseInt(data, startChar);
				(*startChar)++;
				float gyroDataX = ParseFloat(data, startChar);
				(*startChar)++;
				float gyroDataY = ParseFloat(data, startChar);
				(*startChar)++;
				float gyroDataZ = ParseFloat(data, startChar);
				UpdateGyroData(gyroNumber, gyroDataX, gyroDataY, gyroDataZ);
			}
			else if (instrMessage == PRESSURE_SENSOR) {
				int* startChar = (int*)4;
				float pressureData = ParseFloat(data, startChar);
				UpdatePressureData(pressureData);
			}
			else if (instrMessage == GPS) {
				int* startChar = (int*)4;
				float GPSX = ParseFloat(data, startChar);
				(*startChar)++;
				float GPSY = ParseFloat(data, startChar);
				UpdateGPSData(GPSX, GPSY);
			}
		}
	}
	else if (messageSource == RECOVERY_SOURCE) {
		char recoveryMessage = data[3];
		switch (recoveryMessage)
		{
		case STATE:
			ChangeState(ParseInt(data, (int *)(4)));
			break;
		default:
			break;
		}
	}
}

#pragma region UpdateValues
void UpdateThermistorData(int thermistorNumber, float data) {
	thermData[thermistorNumber] = data;
	LogToSD(String(thermData[0]) + ", " + thermData[1] + ", " + thermData[2], THERM_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateLightData(float data) {
	lightValue = data;
	LogToSD(String(data), LIGHT_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateAccData(int accNumber, float dataX, float dataY, float dataZ) {
	accData[0] = dataX;
	accData[1] = dataY;
	accData[2] = dataZ;
	LogToSD(String(accData[0]) + ", " + accData[1] + ", " + accData[2], ACC_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateGyroData(int gyroNumber, float dataX, float dataY, float dataZ) {
	gyroData[0] = dataX;
	gyroData[1] = dataY;
	gyroData[2] = dataZ;
	LogToSD(String(gyroData[0]) + ", " + gyroData[1] + ", " + gyroData[2], GYRO_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdatePressureData(float data) {
	pressureData = data;
	LogToSD(String(data), PRESSURE_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateGPSData(float GPSX, float GPSY) {
	gpsData[0] = GPSX;
	gpsData[1] = GPSY;
	LogToSD(String(gpsData[0]) + ", " + gpsData[1], GPS_DATA_FILENAME + String(fileUID) + ".csv");
}
#pragma endregion

#pragma region CreateStates

void switchDisplayState(bool increase) {
	switch (TransponderState)
	{
	case LowPowerMode:
		if (increase) {
			TransponderState = ActiveMode;
			CreateActiveMode();
		}
		else {
			TransponderState = SpeedData;
			CreateSpeedData();
		}
		break;
	case ActiveMode:
		if (increase) {
			TransponderState = ArmedMode;
			CreateArmedMode();
		}
		else {
			TransponderState = LowPowerMode;
			CreateLowPowerMode();
		}
		break;
	case ArmedMode:
		if (increase) {
			TransponderState = GPSData;
			CreateGPSData();
		}
		else {
			TransponderState = ActiveMode;
			CreateActiveMode();
		}
		break;
	case GPSData:
		if (increase) {
			TransponderState = AltitudeData;
			CreateAltitudeData();
		}
		else {
			TransponderState = ArmedMode;
			CreateArmedMode();
		}
		break;
	case AltitudeData:
		if (increase) {
			TransponderState = TemperatureData;
			CreateTemperatureData();
		}
		else {
			TransponderState = GPSData;
			CreateGPSData();
		}
		break;
	case TemperatureData:
		if (increase) {
			TransponderState = FlightData;
			CreateFlightData();
		}
		else {
			TransponderState = AltitudeData;
			CreateAltitudeData();
		}
		break;
	case FlightData:
		if (increase) {
			TransponderState = SpeedData;
			CreateSpeedData();
		}
		else {
			TransponderState = TemperatureData;
			CreateTemperatureData();
		}
		break;
	case SpeedData:
		if (increase) {
			TransponderState = LowPowerMode;
			CreateLowPowerMode();
		}
		else {
			TransponderState = FlightData;
			CreateFlightData();
		}
		break;
	default:
		break;
	}
}

void CreateLowPowerMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(LOW_POWER_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print((String)LowPowerState);
	}
}

void CreateActiveMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ACTIVE_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print((String)ActiveState);
	}
}

void CreateArmedMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ARMED_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print((String)ArmedState);
	}
}

void CreateGPSData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(GPS);
	lcd.setCursor(0, 1);
	lcd.print(gpsData[0]);
	lcd.print(" ");
	lcd.print(gpsData[1]);
}

void CreateAltitudeData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ALTITUDE);
	//TODO: Convert pressure to alt data
}

void CreateTemperatureData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(AVGTEMP);
	lcd.setCursor(0, 1);
	lcd.print((thermData[0] + thermData[1] + thermData[2]) / 3);
}

void CreateFlightData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(DEPLOY);
	//TODO: Determine if deployment event has happened
	lcd.print(CHUTE);
	//TODO: Determine if chute is out
	lcd.setCursor(0, 1);
	lcd.print(LANDED);
	//TODO: Determine if landed
}

void CreateSpeedData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(VERTSPEED);
	//TODO: Determine vert speed
	lcd.setCursor(0, 1);
	lcd.print(ACCELERATION);
	lcd.print(accData[0]);
	lcd.print(" ");
	lcd.print(accData[1]);
	lcd.print(" ");
	lcd.print(accData[2]);
}
#pragma endregion

void InitializeFile(String fileName) {

}

void LogToSD(String data, String fileName) {
	File dataFile = SD.open(fileName, FILE_WRITE);

	// if the file opened okay, write to it:
	if (dataFile) {
		dataFile.println(millis() + ", " + data);
		// close the file:
		dataFile.close();
	}
}

void ChangeState(int newState) {
	//TODO: CHANGE THE STATE
}

int ParseInt(String data, int* startChar) {
	return (int)ParseFloat(data, startChar);
}

/*
Reads chars in a string up to the stop indicator and converts to float
@param data: the string containing the number
@param startChar, the index of the first digit (inclusive)
*/
float ParseFloat(String data, int* startChar) {
	String out = "";
	while (data[*startChar] != DATA_STOP) {
		out += data[*startChar];
		(*startChar)++;
	}
	return out.toFloat();
}

String ReadFromSerial() {
	String inString = "";
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		if (inChar == MESSAGE_BEGIN || inString != "") inString += inChar; //search for message begin
		if (inString != "" && inChar == MESSAGE_STOP) break;
	}
	return inString;
}







/*
void storage() {
	// I think the LCD has 32 spots for characters, divided into 2 lines. if I'm wrong just change the wording so it fits. As long as we understand its :ok_hand:
	switch (TransponderState) {
	case LowPowerMode:
		lcd.setCursor(0, 0);
		lcd.print(LOW_POWER_1);
		if (!CubesatConnected) {
			lcd.setCursor(0, 1);
			lcd.print(NO_CONNECTION);
		}
		else {
			lcd.setCursor(0, 1);
			lcd.print((String)LowPowerState);
			SelectButtonState = digitalRead(SelectButton);
			if (SelectButtonState == HIGH && LowPowerState == OFF) {
				LowPowerState = SENDING;
				//TODO: ADD NEW STATE TO OUTGOING DATA
			}
		}
	case ActiveMode:
		lcd.setCursor(0, 0);
		lcd.print(ACTIVE_1);
		if (!CubesatConnected) {
			lcd.setCursor(0, 1);
			lcd.print(NO_CONNECTION);
		}
		else {
			lcd.setCursor(0, 1);
			lcd.print((String)ActiveState);//If the state is off, left justify it. If its sending, center it, and if its on right justify it
			SelectButtonState = digitalRead(SelectButton);
			if (SelectButtonState == HIGH && ActiveState == OFF) {
				ActiveState = SENDING;
				//TODO: ADD NEW STATE TO OUTGOING DATA
			}
		}
	case ArmedMode:
		lcd.setCursor(0, 0);
		lcd.print(ARMED_1);
		if (!CubesatConnected) {
			lcd.setCursor(0, 1);
			lcd.print(NO_CONNECTION);
		}
		else {
			lcd.setCursor(0, 1);
			lcd.print((String)ArmedState);//If the state is off, left justify it. If its sending, center it, and if its on right justify it
			SelectButtonState = digitalRead(SelectButton);
			if (SelectButtonState == HIGH && ArmedState == OFF) {
				ArmedState = SENDING;
				//TODO: ADD NEW STATE TO OUTGOING DATA
			}
		}
	case GPSData:
		lcd.setCursor(0, 0);
		lcd.print(GPS);

		Write "GPS: " + GPSX to first line
			Write "GPS: " + GPSY to second line
	case AltitudeData:
		Write "ALTITUDE: " + altitude + " ft" to first line
			Write "APOGEE: " + apogee + " ft" to second line		//get apogee from pressure sensor altitude data (highest recorded)
	case TemperatureData:
		Write "AVGTEMP:" to first line
			Write avgTemp to second line
	case FlightData:
		///////////////////////////
		//Determine deploy from the ambient light sensor. Bright means it deployed
		//Determine chute if velocity is within a range that would indicate good chute. Find velocity from altimeter data
		//Determine landed if velocity is ~0
		//////////////////////////
		Write "DEPLY: " + (Y if deployed = true, N if deployed = false) + " CHUTE: " + (Y if chute = true, N if chute = false) to first line
			Write "LANDED: " + (Y if landed = true, N if landed = false) to second line
	case SpeedData:
		Write "VERT SPEED: " + velocity to first line
			Write "ACC " + ACCX + ACCY + ACCZ to second line
	}
	Write xbeeData to SDCard
		send dataPackage over xbee
}
*/