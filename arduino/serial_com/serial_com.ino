int motorPin=33;
String message = "";
char incomingChar;

void setup() {
  Serial.begin(115200);
  pinMode(motorPin,OUTPUT);
}

void loop() {
// analogWrite(motorPin, 255);
// delay(1000);
// analogWrite(motorPin, 0);
// delay(1000);
// digitalWrite(motorPin,HIGH);
  if (Serial.available() > 0) {
    incomingChar = Serial.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
  }
  else {
    Serial.println("Looking for a device");
    delay(100);
  }
  if (message == "go"){
  Serial.println("going");  
  analogWrite(motorPin,  255);
  }
  if (message == "mid"){
  Serial.println("going");  
  analogWrite(motorPin,  128);
  }
  if (message == "no"){
  Serial.println("noing");  
  analogWrite(motorPin, 0);
  }
  // delay(100);
}
