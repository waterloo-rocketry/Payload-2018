/*
 Name:		Transponder.ino
 Created:	4/23/2018 12:08:16 PM
 Author:	paula
*/
#include <LiquidCrystal.h>
#include "transponderStrings.h"
#include "PinRefs.h"
#include "RadioMessages.h"

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

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LeftButton, INPUT);
	pinMode(RightButton, INPUT);
	pinMode(SelectButton, INPUT);
	lcd.begin(16, 2);
}

// the loop function runs over and over again until power down or reset
void loop() {
	LeftButtonState = digitalRead(LeftButton);
	RightButtonState = digitalRead(RightButton);
	if (LeftButtonState == HIGH) {
		switchDisplayState(false);
	}
	if (RightButtonState == HIGH) {
		switchDisplayState(true);
	}
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
			switch (instrMessage)
			{
			case THERMISTOR:
				int* startChar = (int*)4;
				int thermistorNumber = ParseInt(data, startChar);
				(*startChar)++;
				float thermistorData = ParseFloat(data, startChar);
				UpdateThermistorData(thermistorNumber, thermistorData);
				break;
			case AMBIENT_LIGHT:
				int* startChar = (int*)4;
				float lightData = ParseFloat(data, startChar);
				UpdateLightData(lightData);
				break;
			case ACCELEROMETER:
				int* startChar = (int*)4;
				int accNumber = ParseInt(data, startChar);
				(*startChar)++;
				float accDataX = ParseFloat(data, startChar);
				(*startChar)++;
				float accDataY = ParseFloat(data, startChar);
				(*startChar)++;
				float accDataZ = ParseFloat(data, startChar);
				UpdateAccData(accNumber, accDataX, accDataY, accDataZ);
				break;
			case GYROSCOPE:
				int* startChar = (int*)4;
				int gyroNumber = ParseInt(data, startChar);
				(*startChar)++;
				float gyroDataX = ParseFloat(data, startChar);
				(*startChar)++;
				float gyroDataY = ParseFloat(data, startChar);
				(*startChar)++;
				float gyroDataZ = ParseFloat(data, startChar);
				UpdateGyroData(gyroNumber, gyroDataX, gyroDataY, gyroDataZ);
				break;
			case PRESSURE_SENSOR:
				int* startChar = (int*)4;
				float pressureData = ParseFloat(data, startChar);
				UpdatePressureData(lightData);
				break;
				break;
			case GPS:
				int* startChar = (int*)4;
				float GPSX = ParseFloat(data, startChar);
				(*startChar)++;
				float GPSY = ParseFloat(data, startChar);
				UpdateGPSData(GPSX, GPSY);
				break;
			default:
				break;
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
}

#pragma region UpdateValues
void UpdateThermistorData(int thermistorNumber, float data) {
	thermData[thermistorNumber] = data;
	//Write to SD
}

void UpdateLightData(float data) {
	lightValue = data;
	//Write to SD
}

void UpdateAccData(int accNumber, float dataX, float dataY, float dataZ) {
	accData[0] = dataX;
	accData[1] = dataY;
	accData[2] = dataZ;
	//Write to SD
}

void UpdateGyroData(int gyroNumber, float dataX, float dataY, float dataZ) {
	gyroData[0] = dataX;
	gyroData[1] = dataY;
	gyroData[2] = dataZ;
	//Write to SD
}

void UpdatePressureData(float data) {
	pressureData = data;
	//Write to SD
}

void UpdateGPSData(float GPSX, float GPSY) {
	gpsData[0] = GPSX;
	gpsData[1] = GPSY;
	//Write to SD
}
#pragma endregion

#pragma region CreateStates

void switchDisplayState(bool increase) {
	switch (TransponderState)
	{
	case LowPowerMode:
		break;
	case ActiveMode:
		break;
	case ArmedMode:
		break;
	case GPSData: 
		break;
	case AltitudeData:
		break;
	case TemperatureData:
		break;
	case FlightData:
		break;
	case SpeedData:
		break;
	default:
		break;
	}
}

void CreateLowPowerMode() {

}

void CreateActiveMode() {

}

void CreateArmedMode() {

}

void CreateGPSData() {

}

void CreateAltitudeData() {

}

void CreateTemperatureData() {

}

void CreateFlightData() {

}

void CreateSpeedData() {

}
#pragma endregion

void LogToSD(String data, int startIndex) {
	//TODO: Write data to an SD card
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
