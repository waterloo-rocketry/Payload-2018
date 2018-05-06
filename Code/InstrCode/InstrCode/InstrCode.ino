/*
 Name:		InstrCode.ino
 Created:	4/30/2018 11:31:15 PM
 Author:	paula
*/
//#define GPSECHO  true

#include <Adafruit_GPS.h>
#include <SparkFunLSM6DS3.h>
#include "PinRefs.h"
#include "RadioMessages.h"
#include <Wire.h>
#include <MS5xxx.h>
#include "Timer.h"
#include <SPI.h>
#include <SD.h>
#include "SDFileHeaders.h"
#include <SoftwareSerial.h>

MS5xxx sensor(&Wire);
LSM6DS3 IMU1(I2C_MODE, 0x6A);

//SoftwareSerial mySerial(5, 4);
//Adafruit_GPS Gps(&mySerial);

//boolean usingInterrupt = false;
//void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

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
	//Gps.begin(9600);
	//Gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	//Gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
	//Gps.sendCommand(PGCMD_ANTENNA);
	//useInterrupt(true);

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
/*
// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
	char c = Gps.read();
	// if you want to debug, this is a good time to do it!
#ifdef UDR0
	if (GPSECHO)
		if (c) UDR0 = c;
	// writing direct to UDR0 is much much faster than Serial.print 
	// but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
	if (v) {
		// Timer0 is already used for millis() - we'll just interrupt somewhere
		// in the middle and call the "Compare A" function above
		OCR0A = 0xAF;
		TIMSK0 |= _BV(OCIE0A);
		usingInterrupt = true;
	}
	else {
		// do not call the interrupt function COMPA anymore
		TIMSK0 &= ~_BV(OCIE0A);
		usingInterrupt = false;
	}
}

uint32_t timer = millis();
*/
// the loop function runs over and over again until power down or reset
void loop() {
	/*
	if (!usingInterrupt) {
		// read data from the GPS in the 'main loop'
		char c = Gps.read();
		// if you want to debug, this is a good time to do it!
		if (GPSECHO) {
			if (c) {
				//Serial.print(c);
			}
		}
			
	}
	// if a sentence is received, we can check the checksum, parse it...
	if (Gps.newNMEAreceived()) {
		// a tricky thing here is if we print the NMEA sentence, or data
		// we end up not listening and catching other sentences! 
		// so be very wary if using OUTPUT_ALLDATA and trytng to print out data
		//Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

		if (!Gps.parse(Gps.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
			return;  // we can fail to parse a sentence in which case we should just wait for another
	}

	// if millis() or timer wraps around, we'll just reset it
	if (timer > millis())  timer = millis();

	// approximately every 2 seconds or so, print out the current stats
	if (millis() - timer > 2000) {
		timer = millis(); // reset the timer
		if (Gps.fix) {
			Serial.print(Gps.latitudeDegrees, 4);
			Serial.print(", ");
			Serial.println(Gps.longitudeDegrees, 4);
			Serial.print("/n");
		}
	}
	*/
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
	SendTimerData();
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
}

void SendIMUData() {
	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(ACCELEROMETER);
	//Wire.print("0");
	//.print(DATA_STOP);
	Wire.print(lastAccX);
	Wire.print(DATA_STOP);
	Wire.print(lastAccY);
	Wire.print(DATA_STOP);
	Wire.print(lastAccZ);
	Wire.print(DATA_STOP);
	Wire.print(MESSAGE_STOP);
	Wire.endTransmission();

	Wire.beginTransmission(SLAVE_NUMBER);
	Wire.print(MESSAGE_BEGIN);
	Wire.print(DATA_MESSAGE);
	Wire.print(INSTR_SOURCE);
	Wire.print(GYROSCOPE);
	//Wire.print("0");
	//Wire.print(DATA_STOP);
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