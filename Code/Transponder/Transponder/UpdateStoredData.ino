void UpdateThermistorData(int thermistorNumber, float data) {
	thermData[thermistorNumber] = data;
	LogToSD(String(thermData[0]) + ", " + thermData[1] + ", " + thermData[2], THERM_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateLightData(int data) {
	lightValue = data;
	RefreshLCD();
	LogToSD(String(data), LIGHT_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateAccData(int accNumber, float dataX, float dataY, float dataZ) {
	accData[0] = dataX;
	accData[1] = dataY;
	accData[2] = dataZ;
	LogToSD(String(accData[0]) + ", " + accData[1] + ", " + accData[2], ACC_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateGyroData(int gyroNumber, float dataX, float dataY, float dataZ) {
	gyroData[0] = dataX;
	gyroData[1] = dataY;
	gyroData[2] = dataZ;
	LogToSD(String(gyroData[0]) + ", " + gyroData[1] + ", " + gyroData[2], GYRO_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdatePressureData(float data) {
	pressureData = data;
	LogToSD(String(data), PRESSURE_DATA_FILENAME + String(fileUID) + ".csv");
}

void UpdateGPSData(float GPSX, float GPSY) {
	gpsData[0] = GPSX;
	gpsData[1] = GPSY;
	LogToSD(String(gpsData[0]) + ", " + gpsData[1], GPS_DATA_FILENAME + String(fileUID) + ".csv");
}