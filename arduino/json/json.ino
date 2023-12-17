#include <ArduinoJson.h>
  StaticJsonDocument<200> doc;

#define BUTTON_PIN1 3
#define BUTTON_PIN2 8
#define BUTTON_PIN3 10
#define BUTTON_PIN4 11
void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  pinMode(BUTTON_PIN3, INPUT);
  pinMode(BUTTON_PIN4, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  doc["button1"] = 0;
  doc["button2"] = 0;
  doc["button3"] = 0;
  doc["button4"] = 0;
  doc["pot1"] = 0;
  doc["pot2"] = 0;
  doc["slide1"] = 0;
  doc["slide2"] = 0;
}
void loop()
{
  byte button1 = digitalRead(BUTTON_PIN1);
  byte button2 = digitalRead(BUTTON_PIN2);
  byte button3 = digitalRead(BUTTON_PIN3);
  byte button4 = digitalRead(BUTTON_PIN4);
  int pot1 = analogRead(A0);
  int pot2 = analogRead(A1);
  int slide1 = analogRead(A2);
  int slide2 = analogRead(A3);
  doc["pot1"]=pot1;
  doc["pot2"]=pot2;
  doc["slide1"]=slide1;
  doc["slide2"]=slide2;
  if (button1 == HIGH) {
      doc["button1"]=1;
  }
  else if (button2 == HIGH){
      doc["button2"]=1;
  }
  else if (button3 == HIGH){
      doc["button3"]=1;
  }
  else if (button4 == HIGH){
      doc["button4"]=1;
  }
  else {
    doc["button1"]=0;
    doc["button2"]=0;
    doc["button3"]=0;
    doc["button4"]=0;
  }
  serializeJson(doc, Serial);
  Serial.println();
    // serializeJsonPretty(doc, Serial);

  delay(100);
}