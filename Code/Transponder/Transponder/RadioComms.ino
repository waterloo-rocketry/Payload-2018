#include "RadioMessages.h"

String ReadFromSerial() {
	String inString = "";
	char inChar;
	do {
		if (!Serial.available()) return "";
		inChar = (char)Serial.read();
		if (inChar != MESSAGE_STOP && (inChar == MESSAGE_BEGIN || inString != "")) inString += inChar; //search for message begin
	} while (inChar != MESSAGE_STOP);

	return inString;
}

void SendNewState() {
	int newState = 0;

	if (TransponderState == StatusMode || TransponderState == EditStatusMode) {
		if (SelectedStatusState == OFF) newState = 0;
		else if (SelectedStatusState == ON) newState = 1;
	}
	else if (TransponderState == ArmedMode) newState = 2;

	String message = String(MESSAGE_BEGIN) + DATA_MESSAGE + TRANSPONDER_SOURCE + STATE + (int)newState + String(DATA_STOP) + DATA_STOP + MESSAGE_STOP;
	Serial.print(message); 

	SendingData = true;
	RadioTimer.after(5000, []() -> void {SendingData = false; RefreshLCD(); });
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
			StatusState = OFF;
			ArmedState = OFF;

			RefreshLCD();
		}
	}
	MessageReceived = false;
}