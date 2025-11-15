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
  {
/*     Serial.println("Receiving JSON data...");
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, Serial);

    if (error)
    {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    deserializeJson(doc, Serial); */
    Serial.print(Serial.read());
  };
}