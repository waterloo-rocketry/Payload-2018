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
#include "Timer.h"
#include <SPI.h>
#include <SD.h>
#include "SDFileHeaders.h"

MS5xxx sensor(&Wire);
LSM6DS3 IMU1(I2C_MODE, 0x6A);

Timer RadioTimer;
float lastSample = 0; //Last time a data sample was taken

int lastLight = 0;

float lastPressure = 0; //last pressure measurement taken (in pA)
float lastPresTemp = 0;	//last temperature measurement taken from the pressure sensor (in 0.01C)

float lastAccX = 0;
float lastAccY = 0;
float lastAccZ = 0;

float lastGyroX = 0;
float lastGyroY = 0;
float lastGyroZ = 0;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Wire.begin();
	InitializeSDFile();

	//Ambient Light
	pinMode(AMBIENT_LIGHT_PIN, INPUT);
	
	//Setup Pressure Sensor
	sensor.connect();

	//Setup IMU's
	IMU1.begin();

	RadioTimer.every(1000, SendLastData);
}

// the loop function runs over and over again until power down or reset
void loop() {
	RadioTimer.update();
	//Get data from all sensors
	lastSample = millis();
	GetAmbientLightData();
	GetPressureData();
	GetIMUData();
	WriteLastDataToSD();
	//delay(1);
}

void SendLastData() {
	SendAmbientLightData();
	SendPressureData();
	SendIMUData();
}

void GetAmbientLightData() {
	lastLight = analogRead(AMBIENT_LIGHT_PIN);
}

void GetPressureData() {
	sensor.ReadProm();
	sensor.Readout();
	lastPressure = sensor.GetPres();
	lastPresTemp = sensor.GetTemp();
}

void GetIMUData() {
	lastAccX = IMU1.readFloatAccelX();
	lastAccY = IMU1.readFloatAccelY();
	lastAccZ = IMU1.readFloatAccelZ();

	lastGyroX = IMU1.readFloatGyroX();
	lastGyroY = IMU1.readFloatGyroY();
	lastGyroZ = IMU1.readFloatGyroZ();;
}

float GetThermistorData(int thermistor) {
	return analogRead(thermistor == 1 ? THERM_1_PIN : thermistor == 2 ? THERM_2_PIN : THERM_3_PIN);
}

void SendIMUData() {

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(ACCELEROMETER);
	Wire.print("0");
	Wire.print(DATA_STOP);
	Wire.print(lastAccX);
	Wire.print(DATA_STOP);
	Wire.print(lastAccY);
	Wire.print(DATA_STOP);
	Wire.print(lastAccZ);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GYROSCOPE);
	Wire.print("0");
	Wire.print(DATA_STOP);
	Wire.print(lastGyroX);
	Wire.print(DATA_STOP);
	Wire.print(lastGyroY);
	Wire.print(DATA_STOP);
	Wire.print(lastGyroZ);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();
}


void SendAmbientLightData() {

	Wire.beginTransmission(SLAVE_NUMBER); // transmit to device #9
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(AMBIENT_LIGHT);
	Wire.print(lastLight);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();    // stop transmitting
}

void SendPressureData() {
	

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(PRESSURE_SENSOR);
	Wire.print(lastPressure);
	Wire.print(DATA_STOP);
	Wire.print(lastPresTemp);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();    // stop transmitting
}