const int pingPin = 7;  // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6;  // Echo Pin of Ultrasonic Sensor
const int buzzer = 9;   //buzzer to arduino pin 9

// #define NOTE_C4  262
// #define NOTE_D4  294
// #define NOTE_E4  330
// #define NOTE_F4  349
// #define NOTE_G4  392
// #define NOTE_A4  440
// #define NOTE_B4  494
// #define NOTE_C5  523
float noteArray[9] = { 0, 262, 294, 330, 349, 392, 440, 494, 523 };
void setup() {
  Serial.begin(9600);       // Starting Serial Terminal
  pinMode(buzzer, OUTPUT);  // Set buzzer - pin 9 as an output
}

void loop() {

  // tone(buzzer, 250); // Send 1KHz sound signal...
  // // delay(2000);        // ...for 1 sec
  // // noTone(buzzer);     // Stop sound...
  // // delay(1000);        // ...for 1sec
  long duration, distance, prevDistance, note, prevNote;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);
  //  if(abs(distance-prevDistance)<6){
  //     distance = prevDistance;
  //  }
  //  else {
  //    prevDistance = distance;
  //  }
  note = int(distance / 6);
  //  if(note-prevNote>3){
  //    note=prevNote;
  //  }
  //  else{
  //    prevNote=note;
  //  }
  // Serial.print(distance);
  // Serial.print("cm");
  // Serial.println(noteArray[note]);
  // Serial.println();
  // delay(100);
  if (note < 9) {
    Serial.println(note);
    tone(buzzer, noteArray[note], 250);  // Send 1KHz sound signal...
  }
  delay(250);
  // noTone(noteArray[note]);
}

float microsecondsToCentimeters(long microseconds) {
  return microseconds * 0.034 / 2;
}