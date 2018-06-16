/*
 Name:		Transponder.ino
 Created:	4/23/2018 12:08:16 PM
 Author:	paula
*/
#include "SDFileHeaders.h"
#include <SysCall.h>
#include <SdFatConfig.h>
#include <SdFat.h>
#include <MinimumSerial.h>
#include <FreeStack.h>
#include <BlockDriver.h>
#include <LiquidCrystal.h>
#include "transponderStrings.h"
#include "PinRefs.h"
#include "RadioMessages.h"
#include "Timer.h"

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
float GoProTherm = 0;
float OutsideTherm = 0;
float InsideTherm = 0;

//Light sensor
int lightValue = 0;
const int lightDeployThreshold = 5;

//Accelerometer
float acc0DataX = 0;
float acc0DataY = 0;
float acc0DataZ = 0;


//Gyroscope
float gyro0DataX = 0;
float gyro0DataY = 0;
float gyro0DataZ = 0;


//float gyroData[3] = { 0,0,0 };

//Pressure sensor
float pressureData = 0;
float presTempData = 0;
float altitude = 0;
float altitudeDelta = 0;
float velocity;
float groundLevel = 0;

//GPS
int32_t gpsLat = 0;
int32_t gpsLong = 0;

int32_t sampleTime = 0;	//last time data was sampled from the cubesat

int ArmedCountdown = 120 * 60 * 1000;	//Time until it defaults to off in millis
int lastArmedSample;

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

	//RadioTimer.every(100, GetMessageFromRadio);
	RadioTimer.every(1000, UpdateArmedTimer);
	RadioTimer.every(5000, CheckForConnectivity);
	//RadioTimer.every(1000, WriteLastDataToSD);
	RadioTimer.every(250, []() -> void {blink = !blink; RefreshLCD(); });
	InitializeSDFile();

}

// the loop function runs over and over again until power down or reset
void loop() {
	GetMessageFromRadio();
	CheckForButtonPress();
	RadioTimer.update();

}

void ParseMessage(String data) {
	//debugsenddata(data);

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
				int32_t newSampleTime = ParseInt(data, &startChar);
				velocity = altitudeDelta / ((newSampleTime - sampleTime) / 1000);
				sampleTime = newSampleTime;
				WriteLastDataToSD();
				RefreshLCD();
			}
			if (instrMessage == THERMISTOR) {
				
				startChar = 4;
				//int thermistorNumber = ParseInt(data, &startChar);
				//startChar++;
				GoProTherm = ParseFloat(data, &startChar);
				startChar++;
				OutsideTherm = ParseFloat(data, &startChar);
				startChar++;
				InsideTherm = ParseFloat(data, &startChar);
				RefreshLCD();

				//UpdateThermistorData(thermistorNumber, thermistorData);
				
			}
			else if (instrMessage == AMBIENT_LIGHT) {

				startChar = 4;
				lightValue = ParseInt(data, &startChar);
				RefreshLCD();

			}
			else if (instrMessage == ACCELEROMETER) {
				startChar = 4;
				acc0DataX = ParseFloat(data, &startChar);
				startChar++;
				acc0DataY = ParseFloat(data, &startChar);
				startChar++;
				acc0DataZ = ParseFloat(data, &startChar);
				RefreshLCD();
			}
			else if (instrMessage == GYROSCOPE) {
				startChar = 4;
				gyro0DataX = ParseFloat(data, &startChar);
				startChar++;
				gyro0DataY = ParseFloat(data, &startChar);
				startChar++;
				gyro0DataZ = ParseFloat(data, &startChar);
			}
			else if (instrMessage == PRESSURE_SENSOR) {

				startChar = 4;
				pressureData = ParseFloat(data, &startChar);
				startChar++;
				presTempData = ParseFloat(data, &startChar);
				float newAltitude = (((pow((1013.25 / (pressureData*.01)), (1 / 5.257)) - 1)*(presTempData*.01 + 273.15)) / 0.0065) * 3.28084;
				if (altitude == 0) {
					altitudeDelta = 0;
					altitude = newAltitude;
					groundLevel = newAltitude;
				}
				altitudeDelta = newAltitude - altitude;
				altitude = newAltitude;
				RefreshLCD();

			}
			else if (instrMessage == GPSCOORDS) {
				startChar = 4;
				GPSFix = ParseInt(data, &startChar) == 1 ? true : false;
				startChar++;
				int datapoint = ParseInt(data, &startChar);
				startChar++;
				if (datapoint == 0) {
					gpsLat = ParseInt(data, &startChar);
				}
				else if (datapoint == 1) {
					gpsLong = ParseInt(data, &startChar);
				}
				/*
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
				*/
				RefreshLCD();
			}
		}
		else if (messageSource == RECOVERY_SOURCE) {
			char recoveryMessage = data[3];
			if (recoveryMessage == STATE) {
				int stateChar = 4;
				UpdateState(ParseInt(data, &stateChar));
			}
			if (recoveryMessage == ARMED_TIMER) {
				int stateChar = 4;
				ArmedCountdown = ParseInt(data, &stateChar);
				lastArmedSample = millis();
				RefreshLCD();
			}
			if (recoveryMessage == ALTIMETER) {
				int stateChar = 4;
				AltimeterConnected = ParseInt(data, &stateChar) == 1 ? true : false;
				RefreshLCD();
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

int32_t ParseInt(String data, int* startChar) {
	String out = "";
	while (data[*startChar] != DATA_STOP && *startChar < data.length()) {
		out += data[*startChar];
		(*startChar)++;
	}
	//lcd.print(out);
	//lcd.print(out.toFloat());
	return out.toInt();
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

void UpdateArmedTimer() {
	//ArmedCountdown -= (millis() - lastArmedSample);
	//lastArmedSample = millis();
	RefreshLCD();
}