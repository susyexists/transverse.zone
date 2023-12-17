#define ENCODER_CLK 2
#define ENCODER_DT  4
#define ENCODER_SW  5

int counter = 0;

void setup() {
  // Initialize encoder pins
  Serial.begin(115200);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
}

void readEncoder() {
  int dtValue = digitalRead(ENCODER_DT);
  if (dtValue == HIGH) {
    counter++; // Clockwise
  }
  if (dtValue == LOW) {
    counter--; // Counterclockwise
  }
}

// Get the counter value, disabling interrupts.
// This make sure readEncoder() doesn't change the value
// while we're reading it.
int getCounter() {
  int result;
  noInterrupts();
  result = counter;
  interrupts();
  return result;
}

void resetCounter() {
  noInterrupts();
  counter = 0;
  interrupts();
}

void loop() {
  Serial.println("Counter:");
  Serial.println(getCounter());
  if (digitalRead(ENCODER_SW) == LOW) {
    resetCounter();
  }
  delay(100);
}