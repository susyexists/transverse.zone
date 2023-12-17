#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include <ESPmDNS.h>

// Replace with your network credentials
//const char* ssid = "DESKTOP-DG38FOO 3848";
//const char* password = "770|A85k";
const char* ssid     = "FUTURE_IS_NOW";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create a WebSocket object

AsyncWebSocket ws("/ws");
// Set LED GPIO
const int ledPin1 = 17;
//const int ledPin2 = 18;
const int ledPin2 = 32;
const int ledPin3 = 19;
const int ledPin4 = 22;
const int ledPin5 = 23;
const int ledPin6 = 16;


String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";
String sliderValue3 = "0";
String sliderValue4 = "0";
String sliderValue5 = "0";
String sliderValue6 = "0";

int dutyCycle1;
int dutyCycle2;
int dutyCycle3;
int dutyCycle4;
int dutyCycle5;
int dutyCycle6;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;
const int ledChannel5 = 4;
const int ledChannel6 = 5;

const int resolution = 8;

//Json Variable to Hold Slider Values
JSONVar sliderValues;

//Get Slider Values
String getSliderValues() {
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);
  sliderValues["sliderValue4"] = String(sliderValue4);
  sliderValues["sliderValue5"] = String(sliderValue5);
  sliderValues["sliderValue6"] = String(sliderValue6);

  String jsonString = JSON.stringify(sliderValues);
  return jsonString;
}

// Initialize SPIFFS
void initFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else {
    Serial.println("SPIFFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  //  WiFi.mode(WIFI_STA);
  //  WiFi.begin(ssid, password);
  //  Serial.print("Connecting to WiFi ..");
  //  while (WiFi.status() != WL_CONNECTED) {
  //    Serial.print('.');
  //    delay(1000);
  //  }
  //  Serial.println(WiFi.localIP());
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  if (!MDNS.begin("transverse")) {
    Serial.println("Error starting mDNS");
    return;
  }
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle1);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle2);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle3);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      dutyCycle4 = map(sliderValue4.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle4);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("5s") >= 0) {
      sliderValue5 = message.substring(2);
      dutyCycle5 = map(sliderValue5.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle5);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("6s") >= 0) {
      sliderValue6 = message.substring(2);
      dutyCycle6 = map(sliderValue6.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle6);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (strcmp((char*)data, "getValues") == 0) {
      notifyClients(getSliderValues());
    }
  }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}


void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  initFS();
  initWiFi();

  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  ledcSetup(ledChannel5, freq, resolution);
  ledcSetup(ledChannel6, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);
  ledcAttachPin(ledPin3, ledChannel3);
  ledcAttachPin(ledPin4, ledChannel4);
  ledcAttachPin(ledPin5, ledChannel5);
  ledcAttachPin(ledPin6, ledChannel6);

  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");

  // Start server
  server.begin();

}

void loop() {
  ledcWrite(ledChannel1, dutyCycle1);
  ledcWrite(ledChannel2, dutyCycle2);
  ledcWrite(ledChannel3, dutyCycle3);
  ledcWrite(ledChannel4, dutyCycle4);
  ledcWrite(ledChannel5, dutyCycle5);
  ledcWrite(ledChannel6, dutyCycle6);


  ws.cleanupClients();
}
