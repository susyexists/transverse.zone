int pin_Out_S0 = 19;
int pin_Out_S1 = 22;
int pin_Out_S2 = 23;
int pin_In_Mux1 = 32;

const int numButtons = 3;
int buttons[numButtons] = {0,2,6};
int leds[numButtons] = {7,5,4};
int buttonVal[numButtons] ;
int ledState[numButtons] ;

void setup() {
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  updateMux1();
  for(int i = 0; i < numButtons; i ++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(buttonVal[i]);
    Serial.print(ledState[i]);
    Serial.print(" ; ");
  }
  Serial.println("");
  delay(100);
}

void updateMux1 () {
  for (int i = 0; i < numButtons; i++){
    digitalWrite(pin_Out_S0, HIGH && (buttons[i] & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (buttons[i] & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (buttons[i] & B00000100));
    buttonVal[i] = analogRead(pin_In_Mux1);
    }
  for (int i = 0; i < numButtons; i++){
    if(buttonVal[i]==4095)
    {
      int ledPin = leds[i];
      digitalWrite(pin_Out_S0, HIGH && (ledPin & B00000001));
      digitalWrite(pin_Out_S1, HIGH && (ledPin & B00000010));
      digitalWrite(pin_Out_S2, HIGH && (ledPin & B00000100));
      pinMode(pin_In_Mux1, OUTPUT);
      digitalWrite(pin_In_Mux1,1);
      ledState[i] = 1;
    }
  }
  }
