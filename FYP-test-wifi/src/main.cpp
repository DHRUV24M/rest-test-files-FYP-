#include <Arduino.h>
#include "WiFi.h"

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
}

void loop()
{
  // put your main code here, to run repeatedly:
}