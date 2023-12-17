

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

const int ANALOG_READ_PIN = 33; // or A0

// CHANGE THIS TO ADD YOUR WIFI USERNAME/PASSWORD
const char * WIFI_SSID = "DESKTOP-DG38FOO 3848";
const char * WIFI_PASS = "770|A85k";

//Initialize the JSON data we send to our websocket server
const int capacity = JSON_OBJECT_SIZE(4);
StaticJsonDocument<capacity> doc;


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

void setup()
{
  //Set the baud rate
  Serial.begin(115200);
  Serial.printf("Begin websocket client program....");

  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);

  // WiFi.disconnect();
  Serial.printf("Connecting");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.printf(".");
    delay(100);
  }
  Serial.printf("Connected!");

  // server address, port and URL
  webSocket.begin("192.168.137.1", 8080, "/sendSensorData");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // use HTTP Basic Authorization this is optional remove if not needed
  // webSocket.setAuthorization("user", "Password");

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  // // Set the resolution values
  // analogReadResolution(RESOLUTION);
}

void readLDRValue()
{

  // Read and print the sensor pin value
  int tempSensorVal = analogRead(ANALOG_READ_PIN);

  Serial.println(tempSensorVal);

    //send JSON message in this format {"value": 100}
    doc["value"] = tempSensorVal;

    // Declare a buffer to hold the result
    char output[50];

    serializeJson(doc, output);

    // send message to server when Connected
    webSocket.sendTXT(output);
  

  // sleep for some time before next read
  delay(100);
}

// This will go into loop
void loop()
{
  readLDRValue();
  webSocket.loop();
}