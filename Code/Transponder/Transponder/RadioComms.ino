#include "RadioMessages.h"

#define SERIAL_BUFFER_SIZE 1024

String ReadFromSerial() {
	String inString = "";
	char inChar;
	while (Serial.available()) {
		inChar = (char)Serial.read();
		if (inChar == MESSAGE_BEGIN) {
			inString += inChar;
			break;
		}
	}
	while (Serial.available()) {
		inChar = (char)Serial.read();
		if (inChar == MESSAGE_STOP) {
			//debugsenddata(inString);
			return inString;
		}
		else inString += inChar;
	}

	return "";
}

void SendNewState() {
	int newState = 0;

	if (TransponderState == StatusMode || TransponderState == EditStatusMode) {
		if (SelectedStatusState == OFF) newState = 0;
		else if (SelectedStatusState == ON) newState = 1;
	}
	else if (TransponderState == ArmedMode || TransponderState) {
		if (SelectedArmedState == OFF) newState = 0;
		else if (SelectedArmedState == ON) newState = 2;
	}

	String message = String(MESSAGE_BEGIN) + DATA_MESSAGE + TRANSPONDER_SOURCE + STATE + (int)newState + String(DATA_STOP) + DATA_STOP + MESSAGE_STOP;
	Serial.print(message); 

	SendingData = true;
	RadioTimer.after(5000, []() -> void {SendingData = false; RefreshLCD(); });
}

void GetMessageFromRadio() {
	String message;
	while (Serial.available()) {
		message = ReadFromSerial();
		if (message != "") {
			MessageReceived = true;
			if (CubesatConnected == false) {
				CubesatConnected = true;
				RefreshLCD();
			}
			ParseMessage(message);
		}
	}
	delay(100);
	//WriteLastDataToSD();
	Serial.flush();
	
}

void CheckForConnectivity() {
	InstrConnected = InstrDetected;
	InstrDetected = false;

	if (MessageReceived == false) {
		if (CubesatConnected == true) {
			CubesatConnected = false;
			StatusState = OFF;
			ArmedState = OFF;
		}
	}
	MessageReceived = false;
	RefreshLCD();
}