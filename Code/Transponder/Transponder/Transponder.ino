/*
 Name:		Transponder.ino
 Created:	4/23/2018 12:08:16 PM
 Author:	paula
*/

#include <LiquidCrystal.h>
#include "transponderStrings.h"
#include "PinRefs.h"
#include "RadioMessages.h"
#include "Timer.h"

#include <SPI.h>
#include <SD.h>

enum DisplayStateOptions {
	StatusMode,
	EditStatusMode,
	ArmedMode,
	EditArmedMode,
	ConnectionData,
	FlightData,
	TempData,
	GPSData
};

enum ModeState {
	OFF,
	ON
};

bool SendingData = false;

ModeState StatusState;
ModeState SelectedStatusState;

ModeState ArmedState;
ModeState SelectedArmedState;

DisplayStateOptions TransponderState;

bool CubesatConnected = false;
bool MessageReceived = false;

bool SD1Connected = false;
bool SD2Connected = false;
bool InstrConnected = false;
bool AltimeterConnected = false;
bool GPSFix = false;
bool InstrDetected = false;

// Push Buttons
int LeftButtonState = 0;
int RightButtonState = 0;
int SelectButtonState = 0;

// LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//Thermistor
float therm1 = 0;
float therm2 = 0;
float therm3 = 0;

//Light sensor
int lightValue = 0;
const int lightDeployThreshold = 5;

//Accelerometer
float accDataX = 0;
float accDataY = 0;
float accDataZ = 0;

//Gyroscope
float gyroDataX = 0;
float gyroDataY = 0;
float gyroDataZ = 0;

//float gyroData[3] = { 0,0,0 };

//Pressure sensor
float pressureData = 0;
float presTempData = 0;
float altitude = 0;
float altitudeDelta = 0;
float velocity;

//GPS
float gpsLat = 0;
float gpsLong = 0;

int sampleTime = 0;	//last time data was sampled from the cubesat

Timer RadioTimer;

bool blink = false;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LeftButton, INPUT);
	pinMode(RightButton, INPUT);
	pinMode(SelectButton, INPUT);

	lcd.begin(16, 2);
	TransponderState = StatusMode;
	RefreshLCD();

	Serial.begin(9600);
	
	RadioTimer.every(1000, GetMessageFromRadio);
	RadioTimer.every(1500, CheckForConnectivity);
	RadioTimer.every(250, []() -> void {blink = !blink; RefreshLCD(); });
	InitializeSDFile();
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	CheckForButtonPress();
	RadioTimer.update();

}

void ParseMessage(String data) {
	char messageType = data[1];
	char messageSource = data[2];

	if (messageType == ERROR_MESSAGE) {
		if (messageSource == INSTR_SOURCE) {
			char instrMessage = data[3];
			int startChar;
			if (instrMessage == SD_STATUS) {
				startChar = 4;
				SD1Connected = ParseInt(data, &startChar) == 1 ? true : false;
				RefreshLCD();  
			}
		}
	}
	else if (messageType == DATA_MESSAGE) {
		if (messageSource == INSTR_SOURCE) {
			InstrDetected = true;
			char instrMessage = data[3];
			int startChar;
			if (instrMessage == SAMPLE_TIME) {
				startChar = 4;
				int newSampleTime = ParseInt(data, &startChar);
				velocity = altitudeDelta / ((newSampleTime - sampleTime)/1000);
				sampleTime = newSampleTime;
				WriteLastDataToSD();
				RefreshLCD();
			}
			if (instrMessage == THERMISTOR) {
				/*
				startChar = 4;
				int thermistorNumber = ParseInt(data, &startChar);
				startChar++;
				float thermistorData = ParseFloat(data, &startChar);
				UpdateThermistorData(thermistorNumber, thermistorData);
				*/
			}
			else if (instrMessage == AMBIENT_LIGHT) {
				
				startChar = 4;
				lightValue = ParseInt(data, &startChar);
				RefreshLCD();
				
			}
			else if (instrMessage == ACCELEROMETER) {
				
				startChar = 4;
				//int accNumber = ParseInt(data, &startChar);
				//startChar++;
				accDataX = ParseFloat(data, &startChar);
				startChar++;
				accDataY = ParseFloat(data, &startChar);
				startChar++;
				accDataZ = ParseFloat(data, &startChar);
				RefreshLCD();
				
				//UpdateAccData(accNumber, accDataX, accDataY, accDataZ);
			}
			else if (instrMessage == GYROSCOPE) {
				/*
				int startChar = 4;
				int gyroNumber = ParseInt(data, &startChar);
				startChar++;
				float gyroDataX = ParseFloat(data, &startChar);
				startChar++;
				float gyroDataY = ParseFloat(data, &startChar);
				startChar++;
				float gyroDataZ = ParseFloat(data, &startChar);
				UpdateGyroData(gyroNumber, gyroDataX, gyroDataY, gyroDataZ);
				*/
			}
			else if (instrMessage == PRESSURE_SENSOR) {
				
				startChar = 4;
				pressureData = ParseFloat(data, &startChar);
				startChar++;
				presTempData = ParseFloat(data, &startChar);
				float newAltitude = (((pow((1013.25 / (pressureData*.01)), (1 / 5.257)) - 1)*(presTempData*.01 + 273.15)) / 0.0065) * 3.28084;
				altitudeDelta = newAltitude - altitude;
				altitude = newAltitude;
				RefreshLCD();
				
			}
			else if (instrMessage == GPSCOORDS) {
				startChar = 4;
				float newGPSLat = ParseFloat(data, &startChar);
				startChar++;
				float newGPSLong = ParseFloat(data, &startChar);

				if (newGPSLat == -1 || newGPSLong == -1) {
					GPSFix = false;
				}
				else {
					GPSFix = true;
					gpsLat = newGPSLat;
					gpsLong = newGPSLong;
				}
				RefreshLCD();
			}
		}
		else if (messageSource == RECOVERY_SOURCE) {
			char recoveryMessage = data[3];
			int stateChar = 4;
			switch (recoveryMessage)
			{
			case STATE:
				UpdateState(ParseInt(data, &stateChar));
				break;
			default:
				break;
			}
		}
	}

}

#pragma region CreateStates

void switchDisplayState(bool increase) {
	switch (TransponderState)
	{
	case StatusMode:
		if (increase) {
			TransponderState = ArmedMode;
		}
		else {
			TransponderState = GPSData;
		}
		break;
	case EditStatusMode:
		if (SelectedStatusState == ON) SelectedStatusState = OFF;
		else if (SelectedStatusState == OFF) SelectedStatusState = ON;
		break;
	case ArmedMode:
		if (increase) {
			TransponderState = ConnectionData;
		}
		else {
			TransponderState = StatusMode;
		}
		break;
	case EditArmedMode:
		if (SelectedArmedState == ON) SelectedArmedState = OFF;
		else if (SelectedArmedState == OFF) SelectedArmedState = ON;
		break;
	case ConnectionData:
		if (increase) {
			TransponderState = FlightData;
		}
		else {
			TransponderState = ArmedMode;
		}
		break;
	case FlightData: {
		if (increase) {
			TransponderState = TempData;
		}
		else {
			TransponderState = ConnectionData;
		}
		break;
	}
	case TempData:
		if (increase) {
			TransponderState = GPSData;
		}
		else {
			TransponderState = FlightData;
		}
		break;
	case GPSData:
		if (increase) {
			TransponderState = StatusMode;
		}
		else {
			TransponderState = TempData;
		}
		break;
	default:
		break;
	}
	RefreshLCD();
}

void ChangeCubesatMode() {
	if (!CubesatConnected) return;
	if (TransponderState == StatusMode && !SendingData) {
		TransponderState = EditStatusMode;
		blink = false;
		SelectedStatusState = StatusState;
		RefreshLCD();
	}
	else if (TransponderState == EditStatusMode) {
		TransponderState = StatusMode;
		SendNewState();
		RefreshLCD();
	}

	if (TransponderState == ArmedMode && !SendingData) {
		TransponderState = EditArmedMode;
		blink = false;
		SelectedArmedState = ArmedState;
		RefreshLCD();
	}
	else if (TransponderState == EditArmedMode) {
		TransponderState = ArmedMode;
		SendNewState();
		RefreshLCD();
	}
	/*
	else if (TransponderState == ActiveMode && ActiveState == OFF) {
		ActiveState = SENDING;
		RefreshLCD();
		SendNewState();
	}
	else if (TransponderState == ArmedMode && ArmedState == OFF) {
		ArmedState = SENDING;
		RefreshLCD();
		SendNewState();
	}
	*/
}

#pragma endregion

void LogToSD(String data, String fileName) {
	File dataFile = SD.open(fileName, FILE_WRITE);

	// if the file opened okay, write to it:
	if (dataFile) {
		dataFile.println(millis() + ", " + data);
		// close the file:
		dataFile.close();
	}
}

void UpdateState(int newState) {
	if (newState == 0) {
		if (StatusState == ON) SendingData = false;
		if (ArmedState == ON) SendingData = false;
		StatusState = OFF;
		ArmedState = OFF;	
	}
	else if (newState == 1) {
		if (StatusState == OFF) SendingData = false;
		if (ArmedState == ON) SendingData = false;
		StatusState = ON;
		ArmedState = OFF;
	}
	else if (newState == 2) {
		if (ArmedState == OFF) SendingData = false;
		if (StatusState == ON) SendingData = false;
		StatusState = OFF;
		ArmedState = ON;
	}
	RefreshLCD();

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
	while (data[*startChar] != DATA_STOP && *startChar < data.length()) {
		out += data[*startChar];
		(*startChar)++;
	}
	//lcd.print(out);
	//lcd.print(out.toFloat());
	return out.toFloat();
}