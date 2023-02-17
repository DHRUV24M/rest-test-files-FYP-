#include <Arduino.h>
#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID 1925662
#define CHANNEL_API_KEY "DET43CM509E1YBC2"

WiFiClient client;
int counter = 0;

#define WIFI_NETWORK "ZTE-kJgaTt"
#define WIFI_PASSWORD "gstfbjr3"
#define WIFI_TIMEOUT_MS 20000

void connectTOWiFi()
{
  // mode of the wifi chip STA = existing wifi , AP = not existing wifi
  Serial.print("connecting to wifi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis(); // millis will return the uptime

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("FAILED TO CONNECT....");
  }
  else
  {
    Serial.print("CONNECTED!!  ");
    Serial.println(WiFi.localIP());
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectTOWiFi();

  ThingSpeak.begin(client);
}

void loop()
{
  // put your main code here, to run repeatedly:
  counter++;
  // for one field to update to cloud
  // ThingSpeak.writeField(CHANNEL_ID, 1, counter, CHANNEL_API_KEY);

  // for multiple fields to be updated to cloud
  ThingSpeak.setField(1, counter);
  ThingSpeak.setField(2, WiFi.RSSI());
  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  delay(15000); // thingspeak updates in every 15seconds
}