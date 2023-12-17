int knobPin1 = 26;
int knobPin2 = 25;
int knobPin3 = 33;
int knobRead = 32;
int knobState[8] = {0};

int ledPin1 = 17;
int ledPin2 = 18;
int ledPin3 = 19;
int ledRead = 16;
int ledState[8] = {0};


void setup() {
  pinMode(knobPin1, OUTPUT);
  pinMode(knobPin2, OUTPUT);
  pinMode(knobPin3, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledRead, OUTPUT);

  Serial.begin(9600);
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
    for (int i = 0; i < 8; i++){
    digitalWrite(ledPin1, HIGH && (i & B00000001));
    digitalWrite(ledPin2, HIGH && (i & B00000010));
    digitalWrite(ledPin3, HIGH && (i & B00000100));
    digitalWrite(ledRead,HIGH);
    delay(10);
    digitalWrite(ledRead,LOW);
    }
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
