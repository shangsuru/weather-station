#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "Helm";
const char* password = "gmdihelm";
char path[] = "/";
char* host = "192.168.0.103";  
const int espport= 3000;

WebSocketClient webSocketClient;
WiFiClient client;

String data= "";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.connect(host, espport);
  webSocketClient.path = path;
  webSocketClient.host = host;
  webSocketClient.handshake(client);
}

void loop() {

  if (client.connected()) { 
    digitalWrite(LED_BUILTIN, LOW);
    webSocketClient.getData(data);    
    if (data.length() > 0) { 
      dht.begin();
      delay(5000);

      float h = dht.readHumidity();
      float t = dht.readTemperature();

      data= (String) h + "|" + (String) t; 
      webSocketClient.sendData(data);
    }
  }
}