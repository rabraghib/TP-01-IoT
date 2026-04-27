#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* pwd = "";
const char* broker = "broker.hivemq.com";
const char* topic = "IOT-G9/led";
const int ledPin = D4;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* t, byte* payload, unsigned int len) {
  String msg = "";
  for (int i = 0; i < len; i++) {
    msg += (char)payload[i];
  }
  if (msg == "on") digitalWrite(ledPin, HIGH);
  if (msg == "off") digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) delay(50);
  
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    if (client.connect("ESP32_Wokwi")) {
      client.subscribe(topic);
    }
    delay(500);
  } else {
    client.loop();
  }
}