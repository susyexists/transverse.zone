int ledPins[6] = {17,18,19,22,23,16};
int ledPower[6] = {255,255,255,255,255,255};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i=0;i<6;i++){
  // pinMode(ledPins[i], OUTPUT);
  // digitalWrite(ledPins[i], HIGH);  // turn the LED on (HIGH is the voltage level)/
  analogWrite(ledPins[i],ledPower[i]);
  }
  // pinMode(22, OUTPUT);
// digitalWrite(22, HIGH);  // turn the LED on (HIGH is the voltage level)/
}

// the loop function runs over and over again forever
void loop() {
  
  // digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)/
  // delay(1000);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);                      // wait for a second
}
