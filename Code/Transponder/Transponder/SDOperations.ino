SdFat SD;
char comma = ',';

void InitializeSDFile() {
	if (!SD.begin()) return;
	SD2Connected = true;

	File dataFile = SD.open("Flight Data.csv", FILE_WRITE);
	dataFile.print(TIME_HEADER);
	dataFile.print(comma);
	dataFile.print(LIGHT_HEADER);
	dataFile.print(comma);
	dataFile.print(PRESSURE_HEADER);
	dataFile.print(comma);
	dataFile.print(PRESSURE_TEMP_HEADER);
	dataFile.print(comma);

	dataFile.print(ACC_0_X_HEADER);
	dataFile.print(comma);
	dataFile.print(ACC_0_Y_HEADER);
	dataFile.print(comma);
	dataFile.print(ACC_0_Z_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_0_X_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_0_Y_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_0_Z_HEADER);
	dataFile.print(comma);

	dataFile.print(GPS_LAT_HEADER);
	dataFile.print(comma);
	dataFile.print(GPS_LONG_HEADER);
	dataFile.print("\n");
	dataFile.close();
}

void WriteLastDataToSD() {
	if (!SD2Connected) {
		InitializeSDFile();
		return;
	}
	File data = SD.open("Flight Data.csv", FILE_WRITE);
	if (!data) {
		SD2Connected = false;
		return;
	}
	data.print(sampleTime);
	data.print(comma);
	data.print(lightValue);
	data.print(comma);
	data.print(pressureData);
	data.print(comma);
	data.print(presTempData);
	data.print(comma);
	data.print(acc0DataX);
	data.print(comma);
	data.print(acc0DataY);
	data.print(comma);
	data.print(acc0DataZ);
	data.print(comma);
	data.print(gyro0DataX);
	data.print(comma);
	data.print(gyro0DataY);
	data.print(comma);
	data.print(gyro0DataZ);
	data.print(comma);
	data.print(gpsLat);
	data.print(comma);
	data.print(gpsLong);
	data.print("\n");
	data.close();
}
