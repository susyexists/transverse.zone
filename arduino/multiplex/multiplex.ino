int pin_Out_S0 = 8;
int pin_Out_S1 = 9;
int pin_Out_S2 = 10;
int pin_In_Mux1 = A1;
int Mux1_State[8] = {0};


void setup() {
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  updateMux1();
  for(int i = 0; i < 8; i ++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(Mux1_State[i]);
    Serial.print(" ; ");
  }
  Serial.println("");
  delay(300);
}

void updateMux1 () {
  for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    delay(1);
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    delay(1);
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    delay(1);
    Mux1_State[i] = analogRead(pin_In_Mux1);

    }
  }
