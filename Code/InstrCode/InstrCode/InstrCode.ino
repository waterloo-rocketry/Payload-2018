/*
 Name:		InstrCode.ino
 Created:	4/30/2018 11:31:15 PM
 Author:	paula
*/
#include <SparkFunLSM6DS3.h>
#include "PinRefs.h"
#include "RadioMessages.h"
#include <Wire.h>
#include <MS5xxx.h>

MS5xxx sensor(&Wire);
LSM6DS3 IMU1(I2C_MODE, 0x6A);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Wire.begin();

	//Ambient Light
	pinMode(AMBIENT_LIGHT_PIN, INPUT);
	
	//Setup Pressure Sensor
	sensor.connect();

	//Setup IMU's
	IMU1.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	delay(1000);
	SendPressureSensorData();

	SendAmbientLightMessage();

	SendIMUData();
}

void SendIMUData() {
	
	float Ax = IMU1.readFloatAccelX();
	float Ay = IMU1.readFloatAccelY();
	float Az = IMU1.readFloatAccelZ();

	float Gx = IMU1.readFloatGyroX();
	float Gy = IMU1.readFloatGyroY();
	float Gz = IMU1.readFloatGyroZ();;

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(ACCELEROMETER);
	Wire.print("0");
	Wire.print(DATA_STOP);
	Wire.print(Ax);
	Wire.print(DATA_STOP);
	Wire.print(Ay);
	Wire.print(DATA_STOP);
	Wire.print(Az);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GYROSCOPE);
	Wire.print("0");
	Wire.print(DATA_STOP);
	Wire.print(Gx);
	Wire.print(DATA_STOP);
	Wire.print(Gy);
	Wire.print(DATA_STOP);
	Wire.print(Gz);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();
}

float GetThermistorData(int thermistor) {
	return analogRead(thermistor == 1 ? THERM_1_PIN : thermistor == 2 ? THERM_2_PIN : THERM_3_PIN);
}

void SendAmbientLightMessage() {

	Wire.beginTransmission(SLAVE_NUMBER); // transmit to device #9
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(AMBIENT_LIGHT);
	Wire.print(analogRead(AMBIENT_LIGHT_PIN));
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();    // stop transmitting
}

void SendPressureSensorData() {
	sensor.ReadProm();
	sensor.Readout();
	float pres = sensor.GetPres();
	float temp = sensor.GetTemp();

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(PRESSURE_SENSOR);
	Wire.print(pres);
	Wire.print(DATA_STOP);
	Wire.print(temp);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();    // stop transmitting
}