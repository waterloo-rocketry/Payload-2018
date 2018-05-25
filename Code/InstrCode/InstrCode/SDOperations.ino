
bool FileSuccess = false;
SdFat SD;

void InitializeSDFile() {
	if (!SD.begin()) return;
	FileSuccess = true;

	File dataFile = SD.open(FILE_NAME, O_CREAT | O_AT_END);

	dataFile.print(TIME_HEADER);
	dataFile.print(",");
	dataFile.print(LIGHT_HEADER);
	dataFile.print(",");
	dataFile.print(PRESSURE_HEADER);
	dataFile.print(",");
	dataFile.print(PRESSURE_TEMP_HEADER);
	dataFile.print(",");

	dataFile.print(ACC_0_X_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_0_Y_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_0_Z_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_0_X_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_0_Y_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_0_Z_HEADER);
	dataFile.print(",");
	/*
	dataFile.print(ACC_1_X_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_1_Y_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_1_Z_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_1_X_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_1_Y_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_1_Z_HEADER);
	dataFile.print(",");
	*/
	dataFile.print(GPS_LAT_HEADER);
	dataFile.print(",");
	dataFile.print(GPS_LONG_HEADER);
	dataFile.print("\n");
	dataFile.close();
	delay(3000);
}

void WriteLastDataToSD() {
	if (!FileSuccess) return;
	File dataFile = SD.open(FILE_NAME, O_AT_END);
	dataFile.print(lastSample);
	dataFile.print(",");
	dataFile.print(lastLight);
	dataFile.print(",");
	dataFile.print(lastPressure);
	dataFile.print(",");
	dataFile.print(lastPresTemp);
	dataFile.print(",");

	dataFile.print(lastAcc0X);
	dataFile.print(",");
	dataFile.print(lastAcc0Y);
	dataFile.print(",");
	dataFile.print(lastAcc0Z);
	dataFile.print(",");
	dataFile.print(lastGyro0X);
	dataFile.print(",");
	dataFile.print(lastGyro0Y);
	dataFile.print(",");
	dataFile.print(lastGyro0Z);
	dataFile.print(",");
	/*
	dataFile.print(lastAcc1X);
	dataFile.print(",");
	dataFile.print(lastAcc1Y);
	dataFile.print(",");
	dataFile.print(lastAcc1Z);
	dataFile.print(",");
	dataFile.print(lastGyro1X);
	dataFile.print(",");
	dataFile.print(lastGyro1Y);
	dataFile.print(",");
	dataFile.print(lastGyro1Z);
	dataFile.print(",");
	dataFile.print(fix.latitude());
	dataFile.print(",");
	dataFile.print(fix.longitude());
	*/
	dataFile.print("\n");
	dataFile.close();
}
