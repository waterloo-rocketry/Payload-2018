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
	LowPowerMode,
	ActiveMode,
	ArmedMode,
	GPSData,
	AltitudeData,
	TemperatureData,
	FlightData,
	SpeedData,
	ErrorData
};

enum ModeState {
	OFF,
	SENDING,
	ON
};
String ModeStateStrings[3] = { "OFF", "SENDING", "ON" };

ModeState LowPowerState;
ModeState ActiveState;
ModeState ArmedState;

DisplayStateOptions TransponderState;

bool CubesatConnected = false;
bool MessageReceived = false;

// Push Buttons
int LeftButtonState = 0;
int RightButtonState = 0;
int SelectButtonState = 0;

// LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//Thermistor
float thermData[3] = { 0,0,0 };

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

//GPS
float gpsLat = 0;
float gpsLong = 0;

int sampleTime = 0;	//last time data was sampled from the cubesat

Timer RadioTimer;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LeftButton, INPUT);
	pinMode(RightButton, INPUT);
	pinMode(SelectButton, INPUT);

	lcd.begin(16, 2);
	TransponderState = LowPowerMode;
	RefreshLCD();

	Serial.begin(9600);
	
	RadioTimer.every(1000, GetMessageFromRadio);
	RadioTimer.every(5000, CheckForConnectivity);

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
		//TODO: Handle Error Logic
	}
	else if (messageType == DATA_MESSAGE) {
		if (messageSource == INSTR_SOURCE) {
			char instrMessage = data[3];
			int startChar;
			if (instrMessage == SAMPLE_TIME) {
				startChar = 4;
				sampleTime = ParseInt(data, &startChar);
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
				//UpdateLightData(lightData);
				
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
				RefreshLCD();
				//UpdatePressureData(presData, tempData);
				
			}
			else if (instrMessage == GPSCOORDS) {
				startChar = 4;
				gpsLat = ParseFloat(data, &startChar);
				startChar++;
				gpsLong = ParseFloat(data, &startChar);
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
	case LowPowerMode:
		if (increase) {
			TransponderState = ActiveMode;
		}
		else {
			TransponderState = SpeedData;
		}
		break;
	case ActiveMode:
		if (increase) {
			TransponderState = ArmedMode;
		}
		else {
			TransponderState = LowPowerMode;
		}
		break;
	case ArmedMode:
		if (increase) {
			TransponderState = GPSData;
		}
		else {
			TransponderState = ActiveMode;
		}
		break;
	case GPSData:
		if (increase) {
			TransponderState = AltitudeData;
		}
		else {
			TransponderState = ArmedMode;
		}
		break;
	case AltitudeData:
		if (increase) {
			TransponderState = TemperatureData;
		}
		else {
			TransponderState = GPSData;
		}
		break;
	case TemperatureData:
		if (increase) {
			TransponderState = FlightData;
		}
		else {
			TransponderState = AltitudeData;
		}
		break;
	case FlightData:
		if (increase) {
			TransponderState = SpeedData;
		}
		else {
			TransponderState = TemperatureData;
		}
		break;
	case SpeedData:
		if (increase) {
			TransponderState = LowPowerMode;
		}
		else {
			TransponderState = FlightData;
		}
		break;
	default:
		break;
	}
	RefreshLCD();
}

void ChangeCubesatMode() {
	if (!CubesatConnected) return;
	if (LowPowerState == SENDING || ActiveState == SENDING || ArmedState == SENDING) return;
	if (TransponderState == LowPowerMode && LowPowerState == OFF) {
		LowPowerState = SENDING;
		RefreshLCD();
		SendNewState();
	}
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
	RadioTimer.after(10000, CheckForSendSuccess);
}

void CheckForSendSuccess() {
	if (LowPowerState == SENDING) {
		LowPowerState = OFF;
	}
	if (ActiveState == SENDING) {
		ActiveState = OFF;
	}
	if (ArmedState == SENDING) {
		ArmedState = OFF;
	}
	RefreshLCD();
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
		LowPowerState = ON;
		if (ActiveState != SENDING) ActiveState = OFF;
		if (ArmedState != SENDING) ArmedState = OFF;
	}
	else if (newState == 1) {
		if (LowPowerState != SENDING) LowPowerState = OFF;
		ActiveState = ON;
		if (ArmedState != SENDING) ArmedState = OFF;
	}
	else if (newState == 2) {
		if (LowPowerState != SENDING) LowPowerState = OFF;
		if (ActiveState != SENDING) ActiveState = OFF;
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