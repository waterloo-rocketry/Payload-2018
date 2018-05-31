SdFat SD;
char comma = ',';

void InitializeSDFile() {
	if (!SD.begin()) return;
	FileSuccess = true;

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
	
	dataFile.print(ACC_1_X_HEADER);
	dataFile.print(comma);
	dataFile.print(ACC_1_Y_HEADER);
	dataFile.print(comma);
	dataFile.print(ACC_1_Z_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_1_X_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_1_Y_HEADER);
	dataFile.print(comma);
	dataFile.print(GYRO_1_Z_HEADER);
	dataFile.print(comma);

	dataFile.print(GPS_LAT_HEADER);
	dataFile.print(comma);
	dataFile.print(GPS_LONG_HEADER);
	dataFile.print("\n");
	dataFile.close();
}

void WriteLastDataToSD() {
	if (!FileSuccess) {
		InitializeSDFile();
		return;
	}
	File data = SD.open("Flight Data.csv", FILE_WRITE);
	if (!data) {
		FileSuccess = false;
		return;
	}
	data.print(lastSample);
	data.print(comma);
	data.print(lastLight);
	data.print(comma);
	data.print(lastPressure);
	data.print(comma);
	data.print(lastPresTemp);
	data.print(comma);
	data.print(lastAcc0X);
	data.print(comma);
	data.print(lastAcc0Y);
	data.print(comma);
	data.print(lastAcc0Z);
	data.print(comma);
	data.print(lastGyro0X);
	data.print(comma);
	data.print(lastGyro0Y);
	data.print(comma);
	data.print(lastGyro0Z);
	data.print(comma);
	data.print(lastAcc1X);
	data.print(comma);
	data.print(lastAcc1Y);
	data.print(comma);
	data.print(lastAcc1Z);
	data.print(comma);
	data.print(lastGyro1X);
	data.print(comma);
	data.print(lastGyro1Y);
	data.print(comma);
	data.print(lastGyro1Z);
	data.print(comma);
	data.print(fix.latitude());
	data.print(comma);
	data.print(fix.longitude());
	data.print("\n");
	data.close();
}
