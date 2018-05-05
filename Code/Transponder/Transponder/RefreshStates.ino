void RefreshLCD() {
	switch (TransponderState)
	{
	case LowPowerMode:
		RefreshLowPowerMode();
		break;
	case ActiveMode:
		RefreshActiveMode();
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

void RefreshLowPowerMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(LOW_POWER_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print(ModeStateStrings[LowPowerState]);
	}
}

void RefreshActiveMode() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ACTIVE_1);
	if (!CubesatConnected) {
		lcd.setCursor(0, 1);
		lcd.print(NO_CONNECTION);
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print(ModeStateStrings[ActiveState]);
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
		lcd.print(ModeStateStrings[ArmedState]);
	}
}

void RefreshGPSData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(GPS);
	lcd.setCursor(0, 1);
	lcd.print(gpsData[0]);
	lcd.print(" ");
	lcd.print(gpsData[1]);
}

void RefreshAltitudeData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ALTITUDE);
	lcd.setCursor(0, 1);

	float result = (((pow((1013.25/(pressureData*.01)),(1/5.257))-1)*(presTempData*.01+273.15)) / 0.0065) * 3.28084;
	lcd.print(result);

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
	if (!CubesatConnected) lcd.print("?");
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
	//TODO: Determine vert speed
	lcd.setCursor(0, 1);
	lcd.print(ACCELERATION);
	lcd.print(accData[0]);
	lcd.print(" ");
	lcd.print(accData[1]);
	lcd.print(" ");
	lcd.print(accData[2]);
}