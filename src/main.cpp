#include <Arduino.h>
#include <ArduinoJson.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");
}

void loop()
{
  if (Serial.available())
  {};
}

String IPAddressToString(IPAddress ip)
{
  String out = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  return out;
}