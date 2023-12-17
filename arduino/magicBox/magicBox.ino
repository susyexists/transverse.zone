const int numButton=3;
const int buttonPin[3]={19,23,18};

const int bjtPin =32;

const int knobPin1 = 14;
const int knobPin2 = 25;
const int knobPin3 = 27; 
const int knobRead = 33;
int knobState[8] = {0};


const int redPin = 13;
const int greenPin = 15;
const int bluePin = 2;
const int anodePin = 4;

void setup() {
  Serial.begin(9600);
  for(int i=0;i<numButton;i++){
  pinMode(buttonPin[i],INPUT);
  }

  pinMode(bjtPin,OUTPUT);
  digitalWrite(bjtPin,HIGH);

  pinMode(knobPin1, OUTPUT);
  pinMode(knobPin2, OUTPUT);
  pinMode(knobPin3, OUTPUT);

  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
  pinMode(anodePin,OUTPUT);
  digitalWrite(anodePin,HIGH);

}

void loop() {
    updateMux1();
  for(int i = 0; i < 8; i ++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(knobState[i]);
    Serial.print(" ; ");  
  }
  Serial.println("");
  for(int i=0;i<numButton;i++){
    int buttonState = digitalRead(buttonPin[i]);
    if(buttonState == 1){
    Serial.print("pressed ");
    }
    else{
    Serial.print("not pressed ");
    }
  }
  Serial.println("");
  //delay(1000);
    setColor(255, 0, 0);
    delay(100);
    setColor(0, 255, 0);
    delay(100);
    setColor(0, 0, 255);
    delay(100);

}

void updateMux1 () {
  for (int i = 0; i < 8; i++){
    digitalWrite(knobPin1, HIGH && (i & B00000001));
    digitalWrite(knobPin2, HIGH && (i & B00000010));
    digitalWrite(knobPin3, HIGH && (i & B00000100));
    knobState[i] = analogRead(knobRead);
    }
  }

  void setColor(int R, int G, int B) {
  analogWrite(redPin,   255-R);
  analogWrite(greenPin, 255-G);
  analogWrite(bluePin,  255-B);}
