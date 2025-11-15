#include <Arduino.h>
#include <ArduinoJson.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Fonts/FreeSans9pt7b.h>
#include <SPI.h>

#define TFT_CS 6
#define TFT_RST 4 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 5

#define TFT_SCLK 10
#define TFT_MOSI 9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

/*
FreeMono12pt7b
FreeMono18pt7b
FreeMono24pt7b
FreeMono9pt7b
FreeMonoBold12pt7b
FreeMonoBold18pt7b
FreeMonoBold24pt7b
FreeMonoBold9pt7b
FreeMonoBoldOblique12pt7b
FreeMonoBoldOblique18pt7b
FreeMonoBoldOblique24pt7b
FreeMonoBoldOblique9pt7b
FreeMonoOblique12pt7b
FreeMonoOblique18pt7b
FreeMonoOblique24pt7b
FreeMonoOblique9pt7b
FreeSans12pt7b
FreeSans18pt7b
FreeSans24pt7b
FreeSans9pt7b
FreeSansBold12pt7b
FreeSansBold18pt7b
FreeSansBold24pt7b
FreeSansBold9pt7b
FreeSansBoldOblique12pt7b
FreeSansBoldOblique18pt7b
FreeSansBoldOblique24pt7b
FreeSansBoldOblique9pt7b
FreeSansOblique12pt7b
FreeSansOblique18pt7b
FreeSansOblique24pt7b
FreeSansOblique9pt7b
FreeSerif12pt7b
FreeSerif18pt7b
FreeSerif24pt7b
FreeSerif9pt7b
FreeSerifBold12pt7b
FreeSerifBold18pt7b
FreeSerifBold24pt7b
FreeSerifBold9pt7b
FreeSerifBoldItalic12pt7b
FreeSerifBoldItalic18pt7b
FreeSerifBoldItalic24pt7b
FreeSerifBoldItalic9pt7b
FreeSerifItalic12pt7b
FreeSerifItalic18pt7b
FreeSerifItalic24pt7b
FreeSerifItalic9pt7b
Org_01
Picopixel
Tiny3x3a2pt7b
TomThumb
*/

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");

  SPI.setFrequency(80000000); // 80MHz

  tft.init(76, 284);
  tft.invertDisplay(false);
  tft.setRotation(1);

  Serial.println("ST7789 Initialized");
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 12);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.print("No data received yet");
  tft.setTextColor(ST77XX_WHITE);
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