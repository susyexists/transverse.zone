#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
int motorPin=33;
String message = "";
char incomingChar;

void setup() {
   pinMode(motorPin,OUTPUT);
   SerialBT.begin("ESP32 Bluetooth");
}
void loop() {
  if (SerialBT.available() >0){
    incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
  }
   if (message == "go"){
  SerialBT.println("going");  
  analogWrite(motorPin,  255);
  }
  if (message == "mid"){
  SerialBT.println("miding");  
  analogWrite(motorPin,  128);
  }
  if (message == "no"){
  SerialBT.println("noing");  
  analogWrite(motorPin, 0);
  }
  // delay(100);
}
