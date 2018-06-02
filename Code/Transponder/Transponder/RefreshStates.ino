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
	case EditArmedMode:
		RefreshArmedMode();
		break;
	case ConnectionData:
		RefreshConnectionData();
		break;
	case FlightData:
		RefreshFlightData();
		break;
	case TempData:
		RefreshTemperatureData();
		break;
	case GPSData:
		RefreshGPSData();
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
			if (StatusState == ON || ArmedState) {
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
		lcd.setCursor(13, 0);
		lcd.print(OFFMESSAGE);
		lcd.setCursor(13, 1);
		lcd.print(ONMESSAGE);

		if (TransponderState == ArmedMode) {
			if (ArmedState == ON) {
				lcd.setCursor(0, 1);
				lcd.print(ArmedCountdown);
				lcd.setCursor(11, 1);
			}
			else {
				lcd.setCursor(11, 0);
			}
		}
		else if (TransponderState == EditArmedMode) {
			if (SelectedArmedState == ON) {
				lcd.setCursor(11, 1);
			}
			else {
				lcd.setCursor(11, 0);
			}
		}
		if ((TransponderState == EditArmedMode && blink) || TransponderState == ArmedMode) {
			lcd.print("->");
		}
		if (SendingData) {
			lcd.setCursor(0, 1);
			lcd.print(SENDINGMESSAGE);
		}
	}
}

void RefreshConnectionData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(CONN1);
	lcd.print(SD1Connected ? "Y" : "N");
	lcd.print(" ");
	lcd.print(CONN2);
	lcd.print(SD2Connected ? "Y" : "N");
	lcd.print(" ");
	lcd.print(CONN3);
	lcd.print(CubesatConnected ? "Y" : "N");
	lcd.setCursor(0, 1);
	lcd.print(CONN4);
	lcd.print(InstrConnected ? "Y" : "N");
	lcd.print(" ");
	lcd.print(CONN5);
	lcd.print(AltimeterConnected ? "Y" : "N");
}

void RefreshFlightData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(ALTITUDE);
	lcd.print(round(altitude-groundLevel));
	lcd.print(" ");
	lcd.print(LIGHT);
	lcd.print(round(((float)lightValue / (float)1023) * 100));
	lcd.setCursor(0, 1);
	lcd.print(VERTSPEED);
	lcd.print(round(velocity));
	lcd.print(" ");
	lcd.print(CONN3);
	lcd.print(CubesatConnected ? "Y" : "N");  
}

void RefreshGPSData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(GPS);
	lcd.setCursor(11, 0);
	lcd.print(GPSFIX);
	lcd.print(GPSFix ? "Y" : "N");
	lcd.setCursor(0, 1);
	lcd.print(gpsLat);
	lcd.print(" ");
	lcd.print(gpsLong);
}

void RefreshTemperatureData() {
	lcd.clear();
	lcd.setCursor(0, 0);
	//lcd.print(TEMP0);
	lcd.print(TEMP1);
	lcd.print(round(GoProTherm));
	lcd.setCursor(0, 1);
	lcd.print(TEMP2); 
	lcd.print(round(OutsideTherm));
	lcd.print(" ");
	lcd.print(TEMP3);
	lcd.print(round(InsideTherm));
}