#define stratRelayPin 12
#define instrRelayPin 13
#define stratSoftSerialPin 8
#define slaveNum 1

#include "RadioMessages.h"
#include <Wire.h>

enum RecoveryState {
  Idle,
  Active,
  Armed
};

RecoveryState state;

void setup() {
	pinMode(stratSoftSerialPin, INPUT);
	pinMode(stratRelayPin, OUTPUT);
	pinMode(instrRelayPin, OUTPUT);

	SwitchState(1);

	// initialize serial and wire:
	Wire.begin();//join i2c bus, address optional for master
	Serial.begin(9600);
	// reserve 200 bytes for the xbeeIn:
	
}

void loop() {
  String outgoingData = MESSAGE_BEGIN + DATA_MESSAGE + RECOVERY_SOURCE +  STATE + (int)state + DATA_STOP + DATA_STOP;
  String xbeeData = ReadFromSerial();
  if (xbeeData != "")
	ParseReceivedMessage(xbeeData);
  
  if (state == 1) {
	
  }
  else if (state == 2) {
	//read from i2C bus
      Wire.requestFrom(slaveNum, 6); //request 6 bytes from slave device 
	  String I2CData = "";
      while (Wire.available()) {  //slave may send less than requested
        char temp = Wire.read();   //receive a byte as a char
		I2CData += temp;       // add char to data package
      }
	  if (I2CData != "") {
		  outgoingData += INSTR_SOURCE
	  }
      if (outgoingData == ""){
		  outgoingData = "disInstrError"; //  add disabled instr arduino error to dataPackage if bus empty
      }
  }
  else if (state == 3) {
  
  }

}

void ParseReceivedMessage(String Message) {
  if (Message[1] == STATE) {    //only valid message we can receive is a state change
    SwitchState(SubstringToInt(Message, 2, Message.length()-2));
  }
}

void SwitchState(int stateNumber) {
  state = static_cast<RecoveryState>(stateNumber);
  switch(state) {
    case 1:
      digitalWrite(instrRelayPin, LOW);
      digitalWrite(stratRelayPin, LOW);
      break;
    case 2: 
      digitalWrite(instrRelayPin, HIGH);
      digitalWrite(stratRelayPin, LOW);
      break;
    case 3:
      digitalWrite(instrRelayPin, HIGH);
      digitalWrite(stratRelayPin, HIGH);
      break; 
  }
}

int SubstringToInt(String string, int intBegin, int intEnd) {
  return string.substring(intBegin, intEnd+1).toInt();
}

