float sensorValue;

void setup() {
  Serial.begin(115200);
}
void loop() {
  sensorValue = analogRead(32);
  Serial.println(sensorValue);
  delay(200);
    }
