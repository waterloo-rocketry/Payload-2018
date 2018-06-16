/*
 Name:		InstrCode.ino
 Created:	4/30/2018 11:31:15 PM
 Author:	paula
*/
//#define GPSECHO  true
//#include <Adafruit_GPS.h>
#include <SysCall.h>
#include <SdFatConfig.h>
#include <SdFat.h>
#include <MinimumSerial.h>
#include <FreeStack.h>
#include <BlockDriver.h>
#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>

#include <SparkFunLSM6DS3.h>
#include "PinRefs.h"
#include "RadioMessages.h"
#include <Wire.h>
#include <MS5xxx.h>
#include "Timer.h"
#include "SDFileHeaders.h"

#include "thermistor.h"

MS5xxx sensor(&Wire);
LSM6DS3 IMU1(I2C_MODE, 0x6A);
LSM6DS3 IMU2(I2C_MODE, 0x6B);

static NMEAGPS  gps;
static gps_fix  fix;

THERMISTOR* GoProTemp;
THERMISTOR* OutsideTemp;
THERMISTOR* InsideTemp;

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

bool FileSuccess = false;	//Track if we can succesfully write to the SD card

Timer RadioTimer;		//Time data transmission to the ground
int32_t lastSample = 0; //Last time a data sample was taken

int lastLight = 0;		//last ambient light data

float lastPressure = 0; //last pressure measurement taken (in pA)
float lastPresTemp = 0;	//last temperature measurement taken from the pressure sensor (in 0.01C)

int32_t lastValidLat = 0;
int32_t lastValidLong = 0;

bool hasFix = false;

float lastAcc0X = 0;	//last IMU data
float lastAcc0Y = 0;
float lastAcc0Z = 0;

float lastGyro0X = 0;
float lastGyro0Y = 0;
float lastGyro0Z = 0;

float lastAcc1X = 0;
float lastAcc1Y = 0;
float lastAcc1Z = 0;

float lastGyro1X = 0;
float lastGyro1Y = 0;
float lastGyro1Z = 0;

float OutsideTempReading;
float InsideTempReading;
float GoProTempReading;

// the setup function runs once when you press reset or power the board
void setup() {
	//Serial.begin(9600);
	GoProTemp = new THERMISTOR(A3, 220, 3560, 220);
	OutsideTemp = new THERMISTOR(A2, 220, 3560, 220);
	InsideTemp = new THERMISTOR(A1, 220, 3560, 220);

	pinMode(AMBIENT_LIGHT_PIN, INPUT);

	InitializeSDFile();		//Setup SD Card

	sensor.connect();		//Setup Pressure Sensor

	gpsPort.begin(9600);	//Setup GPS

	//Setup IMU's
	IMU1.settings.accelRange = 16;
	IMU2.settings.accelRange = 4;
	IMU1.begin();
	IMU2.begin();

	RadioTimer.every(1000, SendLastData);	//Send data to ground every second

}

// the loop function runs over and over again until power down or reset
void loop() {	
	//delay(100);				//sample data at 10Hz
	lastSample = millis();
	RadioTimer.update();	
	GetGPSData();
	GetPressureData();
	GetIMUData();
	GetThermData();
	GetAmbientLightData();
	WriteLastDataToSD();
}

void SendLastData() {
	SendTimerData();
	RadioTimer.after(50, SendGPSLatData);
	RadioTimer.after(100, SendGPSLongData);
	RadioTimer.after(150, SendAmbientLightData);
	RadioTimer.after(200, SendPressureData);
	RadioTimer.after(250, SendSDStatus);
	RadioTimer.after(300, SendThermistorData);
}

void SendGPSLatData() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GPSCOORDS);
	Wire.print(hasFix ? 1 : 0);
	Wire.print(DATA_STOP);
	Wire.print(0);
	Wire.print(DATA_STOP);
	Wire.print(lastValidLat);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();
}

void SendGPSLongData() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GPSCOORDS);
	Wire.print(hasFix ? 1 : 0);
	Wire.print(DATA_STOP);
	Wire.print(1);
	Wire.print(DATA_STOP);
	Wire.print(lastValidLong);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();
}


void SendThermistorData() {
	//t1.readToArray();
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(TEMPSENSOR);
	Wire.print(GoProTempReading);
	Wire.print(DATA_STOP);
	Wire.print(OutsideTempReading);
	Wire.print(DATA_STOP);
	Wire.print(InsideTempReading);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();
	//Serial.println((float) t1->read() / 10);
}

void SendSDStatus() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(ERROR_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(SD_SOURCE);
	Wire.print(FileSuccess ? 1 : 0);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();
}

void SendTimerData() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(SAMPLE_TIME);
	Wire.print(lastSample);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();
}

void SendIMU0Data() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(ACCELEROMETER);
	//Wire.print(0);
	//Wire.print(DATA_STOP);
	Wire.print(lastAcc0X);
	Wire.print(DATA_STOP);
	Wire.print(lastAcc0Y);
	Wire.print(DATA_STOP);
	Wire.print(lastAcc0Z);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();
	Wire.flush();

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GYROSCOPE);
	//Wire.print(0);
	//Wire.print(DATA_STOP);
	Wire.print(lastGyro0X);
	Wire.print(DATA_STOP);
	Wire.print(lastGyro0Y);
	Wire.print(DATA_STOP);
	Wire.print(lastGyro0Z);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);

	Wire.endTransmission();
	Wire.flush();
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
	Wire.flush();
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
	Wire.flush();
}
static void GetThermData() {
	GoProTempReading = (float)GoProTemp->read() / 10;
	OutsideTempReading = (float)OutsideTemp->read() / 10;
	InsideTempReading = (float)InsideTemp->read() / 10;
}

static void GetGPSData()
{
	while (gps.available(gpsPort)) {
		fix = gps.read();
	}
	if (fix.latitudeL() != 0) {
		hasFix = true;
		lastValidLat = fix.latitudeL();
	}
	else hasFix = false;

	if (fix.longitudeL() != 0) {
		lastValidLong = fix.longitudeL();
	}
} // GPSloop


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
	lastAcc0X = IMU1.readFloatAccelX();
	lastAcc0Y = IMU1.readFloatAccelY();
	lastAcc0Z = IMU1.readFloatAccelZ();

	lastGyro0X = IMU1.readFloatGyroX();
	lastGyro0Y = IMU1.readFloatGyroY();
	lastGyro0Z = IMU1.readFloatGyroZ();

	lastAcc1X = IMU2.readFloatAccelX();
	lastAcc1Y = IMU2.readFloatAccelY();
	lastAcc1Z = IMU2.readFloatAccelZ();

	lastGyro1X = IMU2.readFloatGyroX();
	lastGyro1Y = IMU2.readFloatGyroY();
	lastGyro1Z = IMU2.readFloatGyroZ();
}