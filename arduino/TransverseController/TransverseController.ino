#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <ArduinoJson.h>
StaticJsonDocument<300> doc;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Define input pins
  int leftPin = 27;
  int rightPin = 12;
  int topPin = 26;
  int bottomPin = 14;
  int togglePin = 16;
  int switchPin = 17;
  int xPin = 32;
  int yPin = 33;
  int powerPin = 4;

//Define input variables
  int leftButton;
  int rightButton;
  int topButton;
  int bottomButton;
  int toggleSwitch;
  int joySwitch;
  int tempX;
  int tempY;
  float joyX;
  float joyY;

//Define serial print timing
long  lastSerialPrint = 0;
long serialCycle = 100;

//Define screen print timing
long  lastScreenPrint = 0;
long  printCycle = 2000;
int printText=0;

//Keep track of time
unsigned long now;


void setup() {
  // Serial.begin(115200);
  SerialBT.begin("Transverse Bluetooth");
  activatePins();
  activateLCD();
}

void loop() {
  readButtons();
  now=millis();
  // printButtons();
  writeJSON();
  printJSON();
  printScreen();
}

void readButtons(){
  leftButton = digitalRead(leftPin);
  rightButton = digitalRead(rightPin);
  topButton = digitalRead(topPin);
  bottomButton = digitalRead(bottomPin);
  toggleSwitch = digitalRead(togglePin);
  joySwitch = digitalRead(switchPin);
  
  tempX = analogRead(xPin);
  joyX = map(tempX,1540,4095,-100,100);
  if (0>joyX && joyX>-10){
    joyX=0;
  }
  joyX=-joyX/100.0;

  tempY = analogRead(yPin);
  joyY = map(tempY,1540,4095,-100,100);
  if (0>joyY && joyY>-10){
    joyY=0;
  }
  joyY=-joyY/100.0;

}


void printButtons(){
  if(now-lastSerialPrint>serialCycle){
    lastSerialPrint=now;
    Serial.print("leftButton: ");
    Serial.print(leftButton);
    Serial.print(" - ");
    Serial.print("rightButton: ");
    Serial.print(rightButton);
    Serial.print(" - ");
    Serial.print("topButton: ");
    Serial.print(topButton);
    Serial.print(" - ");
    Serial.print("bottomButton: ");
    Serial.print(bottomButton);
    Serial.print(" - ");
    Serial.print("toggleSwitch: ");
    Serial.print(toggleSwitch);
    Serial.print(" - ");
    Serial.print("joySwitch: ");
    Serial.print(joySwitch);
    Serial.print(" - ");
    Serial.print("joyX: ");
    Serial.print(joyX);
    Serial.print(" - ");
    Serial.print("joyY: ");
    Serial.print(joyY);
    Serial.println(" ");
    }
}

void writeJSON(){
  doc["leftButton"]=leftButton;
  doc["rightButton"]=rightButton;
  doc["topButton"]=topButton;
  doc["bottomButton"]=bottomButton;
  doc["toggle"]=toggleSwitch;
  doc["joySwitch"]=joySwitch;
  doc["joyX"]=joyX;
  doc["joyY"]=joyY;
}

void printJSON(){
   if(now-lastSerialPrint>serialCycle){
    // serializeJsonPretty(doc, SerialBT);
    serializeJson(doc, SerialBT);
    SerialBT.println();
    lastSerialPrint=now;
    }
}

void printScreen(){
    if(now-lastScreenPrint>printCycle){
      //Firt Text
      if (printText==0){
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Transverse");
        lcd.setCursor(2,1);
        lcd.print("September 30");
        printText=1;
      }
      //Second Text
      else if (printText==1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Vortex Art Club");
        lcd.setCursor(5,1);
        lcd.print("Ankara");
        printText=0;
      }
      lastScreenPrint=now;
    }
}

void activatePins(){
  // Activate power transistor
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin,HIGH);

  // Toggle Switch
  pinMode(togglePin, INPUT_PULLUP);

  // Tact Buttons
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(topPin, INPUT);
  pinMode(bottomPin, INPUT);

  // Joystick Switch
  pinMode(switchPin, INPUT_PULLUP);
}

void activateLCD(){
  //LCD
  lcd.init();
  lcd.backlight();
}
