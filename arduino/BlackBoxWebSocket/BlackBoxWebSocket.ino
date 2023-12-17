//Power Transistor
const int transistorPin=2;

//////////////////Multiplexer Area////////////////////
//Multiplexer pins
int pin_Out_S0 = 26;
int pin_Out_S1 = 25;
int pin_Out_S2 = 33;
int pin_In_Mux = 32;
//Multiplexread array
int Mux_State[8] = {0};
//Number of mux inputs
const int muxNum=6;
int muxIn[muxNum] = {0,3,4,2,1,6};
/////////////////////////////////////////////////////

//////////////////Time Keeping///////////////////////
//Keep track of time
unsigned long now;
//Define screen print timing
long  lastMuxUpdate = 0;
long  muxCycle = 100;
////////////////////////////////////////////////////

//////////////////Rotor Area////////////////////////
#define CLK 13
#define DT 16
#define SW 15
int counter = 0;
int prevCounter=0;
int currentStateCLK;
int lastStateCLK;
int debounceVal=50;
unsigned long lastButtonPress = 0;
/////////////////////////////////////////////////////

////////////////Sonic Sensor Area//////////////////
const int pingPin = 23;  // Trigger Pin of Ultrasonic Sensor
const int echoPin = 18;  // Echo Pin of Ultrasonic Sensor
int prevMotor=0;
long duration, distance;
int motor;
long  lastSensorUpdate = 0;
long  sensorCycle = 1;
///////////////////////////////////////////////////

////////////////LED Lights//////////////////
const int numLed =  6;
int ledPin[numLed] = {12,27,4,22,19,17};
int activeLed[numLed]  = {0,0,0,0,0,0};
////////////////////////////////////////////

////////////////Mode Selection//////////////////
int mode = 0;
bool modeSelection=true;
////////////////////////////////////////////


#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>

WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


// CHANGE THIS TO ADD YOUR WIFI USERNAME/PASSWORD
const char * WIFI_SSID = "FUTURE_IS_NOW";
const char * WIFI_PASS = "12345678";

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[WSc] Disconnected!\n");
    break;
  case WStype_CONNECTED:
    Serial.printf("[WSc] Connected to url: %s\n", payload);
    break;
  case WStype_TEXT:
    Serial.printf("[WSc] get text: %s\n", payload);
    break;
  case WStype_BIN:
    Serial.printf("[WSc] get binary length: %u\n", length);
    break;
  case WStype_ERROR:
  case WStype_FRAGMENT_TEXT_START:
  case WStype_FRAGMENT_BIN_START:
  case WStype_FRAGMENT:
  case WStype_FRAGMENT_FIN:
  case WStype_PING:
  case WStype_PONG:
    break;
  }
}

void initWifi(){
WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);

  // WiFi.disconnect();
  Serial.printf("Connecting");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.printf(".");
    delay(100);
  }
  Serial.printf("Connected!");

}

void initWs(){
    // server address, port and URL
  webSocket.begin("transverse.local", 80,"/ws");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(1000);

}


void setup() {
  Serial.begin(115200);

    Serial.println("Begin websocket client program....");
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(100);
  }

  initWifi();
  initWs();
  initTransistor();
  initMux();
  initRotor();
  initSensor();
  initLed();
}

void loop() {
  now=millis();
  updateRotor();
  if(modeSelection){
    updateLed();
    }
  else{
    if(mode==0){
      updateMux();
      for(int i=0; i<numLed;i++){
        int muxVal = Mux_State[muxIn[i]];
        int pwmVal = map(muxVal,0,4095,0,255);
        analogWrite(ledPin[i], pwmVal);
        int motorVal = map(muxVal,0,4095,0,100);
        // String wsText = i+"s"+motorVal;
        // webSocket.sendTXT(wsText);
        char out[30];
        snprintf(out, 30, "%ds%d", i+1, motorVal);
        // Serial.println(out);
        webSocket.sendTXT(out);
        webSocket.loop();
        delay(200);
      }
    }
    if(mode==1){
      updateSensor();  
      updateLed();
      for(int i=0; i<numLed;i++){
        char out[30];
        snprintf(out, 30, "%ds%d", i+1, activeLed[i]*100);
        // Serial.println(out);
        webSocket.sendTXT(out);
        webSocket.loop();
        delay(50);
      }
    }
  }
   webSocket.loop();
}

void runMotor(){
    activeLed[prevMotor]=0;
    activeLed[motor]=1;
    char out[30];
    snprintf(out, 30, "%ds%d", prevMotor+1, 0);
    webSocket.sendTXT(out);
    delay(50);
    snprintf(out, 30, "%ds%d", motor+1, 100);
    webSocket.sendTXT(out);
    delay(50);
    lightLed();
    prevMotor=motor;
    
}

void initTransistor(){
  pinMode(transistorPin, OUTPUT );
  digitalWrite(transistorPin, HIGH );
}


void initLed(){
  for(int i=0; i<numLed;i++){
  pinMode(ledPin[i], OUTPUT);
  }
  analogWrite(ledPin[0], 255);
}

void lightLed(){
  for(int i=0; i<numLed;i++){
    analogWrite(ledPin[i], 255*activeLed[i]);
  }
}

void lightOne(int pin){
    analogWrite(ledPin[pin], 255);
}

void darkLed(){
  for(int i=0; i<numLed;i++){
     analogWrite(ledPin[i], 0);
    // digitalWrite(ledPin[i], 0);
  }
}

void updateLed(){
  if(prevCounter!=counter){
    activeLed[prevCounter]=0;
    activeLed[counter]=1;
    prevCounter=counter;
    lightLed();
  }
}

void initSensor(){
  pinMode(pingPin, OUTPUT);
}

void updateSensor(){
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);
  motor = int(distance / 6);
  if(abs(motor-prevMotor)>=2){
    motor=prevMotor;
  }
  else{
  prevMotor=motor;
  }
  counter=motor;
  delay(1);
  // Serial.print(distance);
  // Serial.print("cm - Motor:");
  // Serial.print(motor);
  // Serial.println("");
  
}

float microsecondsToCentimeters(long microseconds) {
  return microseconds * 0.034 / 2;
}



void initRotor(){
  pinMode(CLK,INPUT_PULLUP);
	pinMode(DT,INPUT_PULLUP);
	pinMode(SW, INPUT_PULLUP);
	lastStateCLK = digitalRead(CLK);
}

void updateRotor(){
currentStateCLK = digitalRead(CLK);
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
      counter %=6;
		} else {
			counter ++;
      counter %=6;
		}
    if(counter<0){
      counter+=6;
    }
		Serial.print(" Counter: ");
		Serial.println(counter);
	}
	// Remember last CLK state
	lastStateCLK = currentStateCLK;
	// Read the button state
	int btnState = digitalRead(SW);
	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
    if (now - lastButtonPress > debounceVal){
      if(modeSelection){
        mode=counter;
        modeSelection=false;
        Serial.println("Selected Mode: ");
        Serial.println(mode);
        darkLed();
      } 
     else{
		  	modeSelection=true;
        counter=mode;
        Serial.println("Entering mode selection");
        darkLed();
        lightOne(counter);
		  }
    }
    lastButtonPress = now;
	}
}




void initMux () {
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
}

void updateMux () { 
  if(now-lastMuxUpdate>muxCycle){
  for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    Mux_State[i] = analogRead(pin_In_Mux);
    }
    lastMuxUpdate=now;
    // printMux();
    }
  }

void printMux () {
  for(int i = 0; i < muxNum; i ++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(Mux_State[muxIn[i]]);
    Serial.print(" ; ");
  }
  Serial.println("");
}
