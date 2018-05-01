/*
 Name:		InstrCode.ino
 Created:	4/30/2018 11:31:15 PM
 Author:	paula
*/
#include "PinRefs.h"

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);

	//Ambient Light
	pinMode(AMBIENT_LIGHT_PIN, INPUT);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

float GetAmbientLightData() {
	return analogRead(AMBIENT_LIGHT_PIN);
}

float GetThermistorData(int thermistor) {
	return analogRead(thermistor == 1 ? THERM_1_PIN : thermistor == 2 ? THERM_2_PIN : THERM_3_PIN);
}

float 