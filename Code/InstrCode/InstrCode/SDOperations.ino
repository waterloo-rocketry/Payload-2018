int fileUID;

void InitializeSDFile() {
	SD.begin();

	fileUID = 0;
	while (SD.exists("Data" + (String)fileUID + ".csv")) {
		fileUID++;
	}

	String fileName = "Data" + (String)fileUID + ".csv";
	File dataFile = SD.open(fileName, FILE_WRITE);

	dataFile.print(TIME_HEADER);
	dataFile.print(",");
	dataFile.print(LIGHT_HEADER);
	dataFile.print(",");
	dataFile.print(PRESSURE_HEADER);
	dataFile.print(",");
	dataFile.print(PRESSURE_TEMP_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_X_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_Y_HEADER);
	dataFile.print(",");
	dataFile.print(ACC_Z_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_X_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_Y_HEADER);
	dataFile.print(",");
	dataFile.print(GYRO_Z_HEADER);
	dataFile.print("\n");
	dataFile.close();
}

void WriteLastDataToSD() {
	String fileName = "Data" + (String)fileUID + ".csv";
	File dataFile = SD.open(fileName, FILE_WRITE);
	dataFile.print(lastSample);
	dataFile.print(",");
	dataFile.print(lastLight);
	dataFile.print(",");
	dataFile.print(lastPressure);
	dataFile.print(",");
	dataFile.print(lastPresTemp);
	dataFile.print(",");
	dataFile.print(lastAccX);
	dataFile.print(",");
	dataFile.print(lastAccY);
	dataFile.print(",");
	dataFile.print(lastAccZ);
	dataFile.print(",");
	dataFile.print(lastGyroX);
	dataFile.print(",");
	dataFile.print(lastGyroY);
	dataFile.print(",");
	dataFile.print(lastGyroZ);
	dataFile.print("\n");
	dataFile.close();
}