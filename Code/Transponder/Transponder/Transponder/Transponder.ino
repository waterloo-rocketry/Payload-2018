/*
 Name:		Transponder.ino
 Created:	4/23/2018 12:08:16 PM
 Author:	paula
*/
#include <LiquidCrystal.h>
#include "transponderStrings.h"

enum DisplayStateOptions {
	LowPowerMode,
	ActiveMode,
	ArmedMode,
	GPSData,
	AltitudeData,
	TemperatureData,
	FlightData,
	SpeedData
};

enum ModeState {
	OFF,
	SENDING,
	ON
};

ModeState LowPowerState;
ModeState ActiveState;
ModeState ArmedState;

DisplayStateOptions TransponderState;

bool CubesatConnected = false;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
	// I think the LCD has 32 spots for characters, divided into 2 lines. if I'm wrong just change the wording so it fits. As long as we understand its :ok_hand:
	switch(TransponderState) {
		case LowPowerMode:
			lcd.setCursor(0, 0);
			lcd.print(LOW_POWER_1);
			if (!CubesatConnected) {
				lcd.setCursor(0, 1);
				lcd.print(NO_CONNECTION);
			}
			else {
				lcd.setCursor(0, 1);
				lcd.print((String)LowPowerState);
					if (selectButton is pressed && lowPowerState != sending) {
						switch lowPowerState from off to sending or from on to off
							add the updated state to dataPackage
					}
			}
		case ActiveMode:
			Write "ACTIVE MODE" to first line
				if (!cubesatConnected) {
					Write "ERR: NO CONN" to second line
				}
				else {
					Write activeState to second line //If the state is off, left justify it. If its sending, center it, and if its on right justify it
						if (selectButton is pressed && activeState != sending) {
							switch activeState from off to sending or from on to off
								add the updated state to dataPackage
						}
				}
		case ArmedMode:
			Write "ARMED MODE" to first line
				if (!cubesatConnected) {
					Write "ERR: NO CONN" to second line
				}
				else {
					Write ArmedMode to second line //If the state is off, left justify it. If its sending, center it, and if its on right justify it
						if (selectButton is pressed && ArmedMode != sending) {
							switch ArmedMode from off to sending or from on to off
								add the updated state to dataPackage
						}
				}
		case GPSData:
			Write "GPS: " + GPSX to first line
				Write "GPS: " + GPSY to second line
		case AltitudeData:
			Write "ALTITUDE: " + altitude + " ft" to first line
				Write "APOGEE: " + apogee + " ft" to second line		//get apogee from pressure sensor altitude data (highest recorded)
		case TemperatureData:
			Write "AVGTEMP:" to first line
				Write avgTemp to second line
		case FlightData:
			///////////////////////////
			//Determine deploy from the ambient light sensor. Bright means it deployed
			//Determine chute if velocity is within a range that would indicate good chute. Find velocity from altimeter data
			//Determine landed if velocity is ~0
			//////////////////////////
			Write "DEPLY: " + (Y if deployed = true, N if deployed = false) + " CHUTE: " + (Y if chute = true, N if chute = false) to first line
				Write "LANDED: " + (Y if landed = true, N if landed = false) to second line
		case SpeedData:
			Write "VERT SPEED: " + velocity to first line
				Write "ACC " + ACCX + ACCY + ACCZ to second line
	}
	Write xbeeData to SDCard
		send dataPackage over xbee
}
