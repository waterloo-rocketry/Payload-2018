#include <Wire.h>

const stratSoftSerialPin = 8;
const int stratRelayPin = 12;
const int instrRelayPin = 13;
const slaveNum = 1; //Need to initialize number "1" in slave code

String xbeeIn = "";         // a string to hold incoming serial data
boolean stateComplete = false;  // whether the string is complete


enum stateOptions{
  INACTIVE,
  ACTIVE,
  ARMED
};


void setup() {
  //initialize state:
  stateOptions currState = INACTIVE;
  // initialize strat and instr pins as input/output:
  pinMode(stratSoftSerialPin, INPUT);
  pinMode(stratRelayPin, OUTPUT);
  pinMode(instrRelayPin, OUTPUT);
  //initialize strat and instr relay pins to off
  digitalWrite(stratRelayPin, LOW);
  digitalWrite(instrRelayPin, LOW); 
  
  // initialize serial and wire:
  Wire.begin();//join i2c bus, address optional for master
  Serial.begin(9600);
  // reserve 200 bytes for the xbeeIn:
  xbeeIn.reserve(200);
}

void loop() {
  // if new state has succesfully been read:
  if (stateComplete) {
    String dataPack = ""
    if (xbeeIn == currState) {
      //do nothing, just a check-in
    }
    else{
      switch(xbeeIn) {
        case INACTIVE:
          switchToINACTIVE();
          break;
        case ACTIVE:
          switchToACTIVE();
          break;
        case ARMED:
          switchToARMED();
          break;
      }
    }

    if (currState == INACTIVE) {
      //do nothing
    }
    if (currState == ACTIVE) {
      //read from i2C bus
      Wire.requestFrom(slaveNum, 6); //request 6 bytes from slave device 
      
      while (Wire.available()) {  //slave may send less than requested
        char temp = Wire.read();   //receive a byte as a char
        dataPack += temp;       // add char to data package
      }
      if (dataPack == ""){
        dataPack = "disInstrError" //  add disabled instr arduino error to dataPackage if bus empty
      }
    }
    if (currState == ARMED) {
        //  read from i2c bus
      Wire.requestFrom(slaveNum, 6); //request 6 bytes from slave device 
      
      while (Wire.available()) {  //slave may send less than requested
        char temp = Wire.read();   //receive a byte as a char
        dataPack += temp;       // add char to data package
      }
      if (dataPack == ""){
        dataPack = "disInstrError" //  add disabled instr arduino error to dataPackage if bus empty
      }
      
      
      //  read from stratologger softwareserial:  
      //NEED TO IMPLEMENT - https://www.arduino.cc/en/Tutorial/SoftwareSerialExample

 
       // if (softwareserial is empty) {
       //   add disabled stratologger error to dataPackage
       // }
       // add all dataPackage to dataPackage
      
    }
    // clear the xbeeIn state:
    xbeeIn = "";
    stateComplete = false;

    
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the xbeeIn:
    xbeeIn += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stateComplete = true;
    }
  }
}

void switchToACTIVE(){
  digitalWrite(instrRelayPin, HIGH);
  digitalWrite(stratRelayPin, LOW);
  currState = ACTIVE
}

void switchToARMED(){
  digitalWrite(instrRelayPin, HIGH);
  digitalWrite(stratRelayPin, HIGH);
  currState = ARMED
}

void switchToINACTIVE(){
  digitalWrite(instrRelayPin, LOW);
  digitalWrite(stratRelayPin, LOW);
  currState = INACTIVE
}




