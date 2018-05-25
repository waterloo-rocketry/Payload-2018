void RefreshLCD() {
	switch (TransponderState)
	{
	case StatusMode:
		RefreshStatusMode();
		break;
	case EditStatusMode:
		RefreshStatusMode();
		break;
	case ArmedMode:
		RefreshArmedMode();
		break;
	case GPSData:
		RefreshGPSData();
		break;
	case AltitudeData:
		RefreshAltitudeData();
		break;
	case TemperatureData:
		RefreshTemperatureData();
		break;
	case FlightData:
		RefreshFlightData();
		break;
	case SpeedData:
		RefreshSpeedData();
		break;
	default:
		break;
	}
}

void RefreshStatusMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(STATUS_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(13, 0);
		lcd.print(OFFMESSAGE);
		lcd.setCursor(13, 1);
		lcd.print(ONMESSAGE);

		if (TransponderState == StatusMode) {
			if (StatusState == ON) {
				lcd.setCursor(11, 1);
			}
			else {
				lcd.setCursor(11, 0);
			}
		}
		else if (TransponderState == EditStatusMode) {
			if (SelectedStatusState == ON) {
				lcd.setCursor(11, 1);
			}
			else {
				lcd.setCursor(11, 0);
			}
		}		
		if ((TransponderState == EditStatusMode && blink) || TransponderState == StatusMode) {
			lcd.print("->");
		}		
		if (SendingData) {
			lcd.setCursor(0, 1);
			lcd.print(SENDINGMESSAGE);
		}
	}
}


void RefreshArmedMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ARMED_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		//lcd.print(ModeStateStrings[ArmedState]);
	}
}

void RefreshGPSData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(GPSCOORDS);
	lcd.setCursor(0, 1);
	lcd.print(gpsLat);
	lcd.print(" ");
	lcd.print(gpsLong);
}

void RefreshAltitudeData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ALTITUDE);
	lcd.setCursor(0, 1);

	if (presTempData == 0 || pressureData == 0) {
		lcd.print("NODATA");
	}
	else {
		altitude = (((pow((1013.25 / (pressureData*.01)), (1 / 5.257)) - 1)*(presTempData*.01 + 273.15)) / 0.0065) * 3.28084;
		lcd.print(altitude);
	}
}

void RefreshTemperatureData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(AVGTEMP);
	lcd.setCursor(0, 1);
	lcd.print((thermData[0] + thermData[1] + thermData[2]) / 3);
}

void RefreshFlightData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(DEPLOY);
	//if (!CubesatConnected) lcd.print("?");
	if (lightValue > lightDeployThreshold) lcd.print("Y");
	else lcd.print("N");
	//TODO: Determine if deployment event has happened
	lcd.print(CHUTE);
	//TODO: Determine if chute is out
	lcd.setCursor(0, 1);
	lcd.print(LANDED);
	//TODO: Determine if landed
}

void RefreshSpeedData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(VERTSPEED);
	lcd.setCursor(0, 1);
	lcd.print(sampleTime);
	//TODO: Determine vert speed
	/*
	lcd.setCursor(0, 1);
	lcd.print(ACCELERATION);
	lcd.print(accDataX);
	lcd.print(" ");
	lcd.print(accDataY);
	lcd.print(" ");
	lcd.print(accDataZ);
	*/
}