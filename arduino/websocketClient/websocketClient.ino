#include <Arduino.h>
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

void setup()
{
  //Set the baud rate
  Serial.begin(115200);
  Serial.println("Begin websocket client program....");
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(100);
  }
}
// This will go into loop
void loop()
{
  webSocket.sendTXT("1s100");
  delay(500);
  webSocket.sendTXT("1s0");
  delay(500);
  webSocket.loop();
}