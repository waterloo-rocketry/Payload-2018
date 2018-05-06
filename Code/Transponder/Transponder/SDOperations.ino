#include "SDFileHeaders.h"

int fileUID;
bool FileSuccess = false;

void InitializeSDFile() {
	if (!SD.begin()) return;
	FileSuccess = true;

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
	if (!FileSuccess) return;
	String fileName = "Data" + (String)fileUID + ".csv";
	File dataFile = SD.open(fileName, FILE_WRITE);
	dataFile.print(sampleTime);
	dataFile.print(",");
	dataFile.print(lightValue);
	dataFile.print(",");
	dataFile.print(pressureData);
	dataFile.print(",");
	dataFile.print(presTempData);
	dataFile.print(",");
	dataFile.print(accDataX);
	dataFile.print(",");
	dataFile.print(accDataY);
	dataFile.print(",");
	dataFile.print(accDataZ);
	dataFile.print(",");
	dataFile.print(gyroDataX);
	dataFile.print(",");
	dataFile.print(gyroDataY);
	dataFile.print(",");
	dataFile.print(gyroDataZ);
	dataFile.print("\n");
	dataFile.close();
}