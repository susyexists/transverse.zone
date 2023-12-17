int ledPins[8] = {27,25,32,34,15,0,16,5};
int ledPower[6] = {255,255,255,255,255,255};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i=0;i<6;i++){
  // pinMode(ledPins[i], OUTPUT);
  // digitalWrite(ledPins[i], HIGH);  // turn the LED on (HIGH is the voltage level)/
  analogWrite(ledPins[i],255);
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
