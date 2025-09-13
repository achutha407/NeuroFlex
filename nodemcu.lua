#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "JACK";
const char* password = "mwge6520";

unsigned long channelID = 3073213;
const char* writeAPIKey = "4JMZW6W8EXG39ST6";

WiFiClient client;

void setup() {
  Serial.begin(9600); // NodeMCU Serial for Arduino
  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED) { delay(500); Serial.print("."); }
  ThingSpeak.begin(client);
}

void loop() {
  if(Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    if(data.startsWith("EMG:")) {
      int emgVal = data.substring(4).toInt();
      ThingSpeak.writeField(channelID,1,emgVal,writeAPIKey);
      delay(16000); // ThingSpeak free limit
    }
  }
}
