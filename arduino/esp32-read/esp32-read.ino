const int numPots = 7;
const int potPins[numPots]= {12,33,32,35,34,27,14};
int potVals[numPots]= {};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=0; i<numPots;i++){
  potVals[i]=analogRead(potPins[i]);
  Serial.print("Pot");
  Serial.print(i+1);
  Serial.print(":");
  Serial.print(potVals[i]);
  Serial.print(" ; ");
  };
  Serial.println(" ");
  delay(100);
}
