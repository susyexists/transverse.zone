int pin_Out_S0 = 25;
int pin_Out_S1 = 26;
int pin_Out_S2 = 27;
int pin_In_Mux1 = 16;
int Mux1_State[8] = {0};


void setup() {
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  pinMode(pin_In_Mux1, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  updateMux1();
}

void updateMux1 () {
  for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    digitalWrite(pin_In_Mux1,HIGH);
    delay(200);
    digitalWrite(pin_In_Mux1,LOW);
    }
  }
