#define stratRelayPin 12
#define instrRelayPin 13
#define stratSoftSerialPin 8
#define slaveNum 1

#include "RadioMessages.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "PinRefs.h"

enum RecoveryState {
	Idle,
	Active,
	Armed
};

RecoveryState state;
String i2cData = "";
int ArmedTimeout = 120; //Amount of time in minutes to default to disarmed after arming
int ArmedCountdown = 0;

void setup() {
	pinMode(stratSoftSerialPin, INPUT);
	pinMode(stratRelayPin, OUTPUT);
	pinMode(instrRelayPin, OUTPUT);

	
	pinMode(LED_BUILTIN, OUTPUT);

	// initialize serial and wire:
	Wire.begin(SLAVE_NUMBER);//join i2c bus, address optional for master
	Wire.onReceive(ReceivedMessage);
	Serial.begin(9600);
	state = Idle;
	SwitchState(1);
}

void ReceivedMessage(int bytes) {
	while (Wire.available())
	{
		i2cData += (char)Wire.read();
	}
}

void loop() {
	
	String xbeeData = ReadFromSerial();
	if (xbeeData != "")
		ParseMessage(xbeeData);

	if (state == 0) {
		delay(2500);
		SendStateDataOverRadio();
	}
	else if (state == 1) {
		delay(500);
		SendStateDataOverRadio();
		SendInstrDataOverRadio();
	}
	else if (state == 2) {
		delay(500);

		if (millis() - ArmedCountdown > (ArmedTimeout * 60000)) {
			SwitchState(0);
		}

		SendStateDataOverRadio();
		SendInstrDataOverRadio();
	}
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