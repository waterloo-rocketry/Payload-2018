#include "RadioMessages.h"


String ReadFromSerial() {
	String inString = "";
	while (Serial.available()) {
		char inChar = (char)Serial.read();
		if (inChar == MESSAGE_BEGIN || inString != "") inString += inChar; //search for message begin
		if (inString != "" && inChar == MESSAGE_STOP) break;
	}
	return inString;
}