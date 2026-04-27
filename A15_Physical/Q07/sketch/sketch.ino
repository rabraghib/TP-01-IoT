#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "0xRN-SU";
const char* pwd = "";
const char* broker = "broker.hivemq.com";

const char* t_led   = "IOT-G9/led";
const char* t_water = "IOT-G9/water";

const int ledPin   = D4;
const int waterPin = A0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void callback(char* t, byte* payload, unsigned int len) {
  String msg = "";
  for (int i = 0; i < len; i++) {
    msg += (char)payload[i];
  }

  if (msg == "on") {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED turned ON");
  } else if (msg == "off") {
    digitalWrite(ledPin, LOW);
    Serial.println("LED turned OFF");
  }
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(waterPin, INPUT);
  
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

// --- Main Loop ---
void loop() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_Water_Level_Client")) {
      Serial.println("connected");
      client.subscribe(t_led);
    } else {
      delay(2000);
    }
  } else {
    client.loop();
    
    unsigned long now = millis();
    if (now - lastMsg > 5000) {
      lastMsg = now;

      int waterLevel = analogRead(waterPin);

      client.publish(t_water, String(waterLevel).c_str());

      Serial.print("Water Level Reading: "); 
      Serial.println(waterLevel);
    }
  }
}