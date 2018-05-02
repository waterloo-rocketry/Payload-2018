#include "RadioMessages.h"

String ReadFromSerial() {
	String inString = "";
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		//inString += inChar;
		if (inChar == MESSAGE_BEGIN || inString != "") inString += inChar; //search for message begin
		if (inString != "" && inChar == MESSAGE_STOP) break;
	}
	/*
	if (inString != "") {
		lcd.clear();
		lcd.print(inString);
	}
	*/
	//lcd.print(inString);
	return inString;
}

void SendNewState() {
	int newState;

	if (TransponderState == LowPowerMode) newState = 0;
	else if (TransponderState == ActiveMode) newState = 1;
	else if (TransponderState == ArmedMode) newState = 2;
	else return;

	String message = String(MESSAGE_BEGIN) + DATA_MESSAGE + TRANSPONDER_SOURCE + STATE + (int)newState + String(DATA_STOP) + DATA_STOP + MESSAGE_STOP;
	Serial.print(message); 
}

void GetMessageFromRadio() {
	while (Serial.available()) {
		String message = ReadFromSerial();
		if (message != "") {
			MessageReceived = true;
			if (CubesatConnected == false) {
				CubesatConnected = true;
				RefreshLCD();
			}
			ParseMessage(message);
			
		}
	}
}

void CheckForConnectivity() {
	if (MessageReceived == false) {
		if (CubesatConnected == true) {
			CubesatConnected = false;
			LowPowerState = OFF;
			ActiveState = OFF;
			ArmedState = OFF;

			RefreshLCD();
		}
	}
	MessageReceived = false;
}