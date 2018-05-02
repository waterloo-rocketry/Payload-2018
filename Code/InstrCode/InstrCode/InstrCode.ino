/*
 Name:		InstrCode.ino
 Created:	4/30/2018 11:31:15 PM
 Author:	paula
*/
#include "PinRefs.h"
#include "RadioMessages.h"
#include <Wire.h>

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Wire.begin();

	//Ambient Light
	pinMode(AMBIENT_LIGHT_PIN, INPUT);

}

// the loop function runs over and over again until power down or reset
void loop() {
	delay(1000);
	int x = GetAmbientLightData();
	Serial.print(x);
	SendAmbientLightMessage(x);
}

int GetAmbientLightData() {
	return analogRead(AMBIENT_LIGHT_PIN);
}

float GetThermistorData(int thermistor) {
	return analogRead(thermistor == 1 ? THERM_1_PIN : thermistor == 2 ? THERM_2_PIN : THERM_3_PIN);
}

void SendAmbientLightMessage(int data) {

	Wire.beginTransmission(SLAVE_NUMBER); // transmit to device #9
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(AMBIENT_LIGHT);
	Wire.print(data);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();    // stop transmitting
	
}