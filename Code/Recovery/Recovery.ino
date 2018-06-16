#define stratRelayPin 12
#define instrRelayPin 13
#define stratSoftSerialPin 8
#define slaveNum 1

#include "RadioMessages.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "PinRefs.h"
#include "SoftwareSerial.h"
#include "Timer.h"

enum RecoveryState {
	Idle,
	Active,
	Armed
};

RecoveryState state;
String i2cData = "";
int ArmedTimeout = 120; //Amount of time in minutes to default to disarmed after arming
long ArmedCountdown = 0;
SoftwareSerial mySerial(8, 9);
bool altimeterOn = false;
Timer UpdateTimer;		//Time data transmission to the ground

void setup() {
	pinMode(stratSoftSerialPin, INPUT);
	pinMode(stratRelayPin, OUTPUT);
	pinMode(instrRelayPin, OUTPUT);
	mySerial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);

	// initialize serial and wire:
	Wire.begin(SLAVE_NUMBER);//join i2c bus, address optional for master
	Wire.onReceive(ReceivedMessage);
	Serial.begin(9600);
	state = Idle;
	SwitchState(0);

	UpdateTimer.every(2500, UpdateLowPower);
	UpdateTimer.every(1000, UpdateActive);
	UpdateTimer.every(1000, UpdateArmed);

}

void ReceivedMessage(int bytes) {
	String s = "";
	while (Wire.available())
	{
		//s += (char)Wire.read();
		Serial.print( (char)Wire.read());
	}
	//delay(50);
}

void loop() {
	UpdateTimer.update();
	
}

void UpdateLowPower() {
	if (state != 0) return;

	String xbeeData = ReadFromSerial();
	if (xbeeData != "")
		ParseMessage(xbeeData);


	ReadFromAltimeter();
	SendStateDataOverRadio();

}
void UpdateActive() {
	if (state != 1) return;

	String xbeeData = ReadFromSerial();
	if (xbeeData != "")
		ParseMessage(xbeeData);

	ReadFromAltimeter();
	SendStateDataOverRadio();
	//SendInstrDataOverRadio();
}
void UpdateArmed() {
	if (state != 2) return;

	String xbeeData = ReadFromSerial();
	if (xbeeData != "")
		ParseMessage(xbeeData);

	if (long(((ArmedTimeout * 60000) - (millis() - ArmedCountdown)) / 60000) == 0) {
		SwitchState(0);
	}

	ReadFromAltimeter();
	SendStateDataOverRadio();
	//SendInstrDataOverRadio();
	SendTimerDataOverRadio();
}

void SwitchState(int stateNumber) {

	switch (stateNumber) {
	case 0:
		state = Idle;
		digitalWrite(instrRelayPin, LOW);
		digitalWrite(stratRelayPin, LOW);
		break;
	case 1:
		state = Active;
		digitalWrite(instrRelayPin, HIGH);
		digitalWrite(stratRelayPin, LOW);
		break;
	case 2:
		state = Armed;
		ArmedCountdown = millis();
		digitalWrite(instrRelayPin, HIGH);
		digitalWrite(stratRelayPin, HIGH);
		break;
	}
}

int SubstringToInt(String string, int intBegin, int intEnd) {
	return string.substring(intBegin, intEnd + 1).toInt();
}

void ParseMessage(String data) {

	char messageType = data[1];
	char messageSource = data[2];

	if (messageType == ERROR_MESSAGE) {
		//TODO: Handle Error Logic
	}
	else if (messageType == DATA_MESSAGE) {
		if (messageSource == TRANSPONDER_SOURCE) {
			char transponderMessage = data[3];
			if (transponderMessage == STATE) {
				int stateMessage = 4;
				SwitchState(ParseInt(data, &stateMessage));
			}
		}
	}
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