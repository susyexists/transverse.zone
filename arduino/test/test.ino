#include <ArduinoJson.h>
  StaticJsonDocument<200> doc;

#define BUTTON_PIN1 4
#define BUTTON_PIN2 7
#define BUTTON_PIN3 3
void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  pinMode(BUTTON_PIN3, INPUT);
  doc["button1"] = 0;
  doc["button2"] = 0;
  doc["button3"] = 0;
}
void loop()
{
  byte button1 = digitalRead(BUTTON_PIN1);
  byte button2 = digitalRead(BUTTON_PIN2);
  byte button3 = digitalRead(BUTTON_PIN3);
  
  if (button1 == LOW) {
      // Serial.println("Button1 is pressed");
      doc["button1"]=1;
  }
  else if (button2 == LOW){
      // Serial.println("Button2 is pressed");
      doc["button2"]=1;
  }
  else if (button3 == LOW){
      // Serial.println("Button2 is pressed");
      doc["button3"]=1;
  }
  else {
    // Serial.println("Nothing is pressed");
    doc["button1"]=0;
    doc["button2"]=0;
    doc["button3"]=0;
  }
// serializeJson(doc, Serial);
  Serial.println();
    serializeJsonPretty(doc, Serial);

  delay(100);
}