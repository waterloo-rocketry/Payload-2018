#define stratRelayPin 12
#define instrRelayPin 13

#include "RadioMessages.h"

enum RecoveryState {
  Idle,
  Active,
  Armed
};

RecoveryState state;

void setup() {

}

void loop() {
  String xbeeData = ReadFromSerial();
  if (xbeeData == "") return;
  ParseReceivedMessage(xbeeData);
}

void ParseReceivedMessage(String Message) {
  if (Message[1] == STATE) {    //only valid message we can receive is a state change
    SwitchState(SubstringToInt(Message, 2, Message.length()-2));
  }
}

void SwitchState(int stateNumber) {
  state = stateNumber;
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

