#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int powerPin = 7; 
const int signalPin = A0;

// 12 hours in milliseconds = 12 * 60 * 60 * 1000
const long interval = 43200000; 

void setup() {
  u8g2.begin();
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  
  // Take the first reading immediately on startup
  takeMeasurement();
}

void loop() {
  delay(interval); 
  takeMeasurement();
}

void takeMeasurement() {
  // 1. Power up and read
  digitalWrite(powerPin, HIGH);
  delay(200); // Longer delay for soil stabilization
  int rawValue = analogRead(signalPin);
  digitalWrite(powerPin, LOW);

  // 2. Update Display
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 15, "Soil Check:");
  
  u8g2.setCursor(0, 40);
  u8g2.setFont(u8g2_font_ncenB14_tr);
  
  // Calibration thresholds (You may need to tweak these!)
  if (rawValue < 100) {
    u8g2.print("Status: DRY");
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 60, ">> WATER NOW! <<");
  } else if (rawValue < 500) {
    u8g2.print("Status: OK");
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 60, "Soil is moist.");
  } else {
    u8g2.print("Status: WET");
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 60, "Don't water yet.");
  }
  
  u8g2.sendBuffer();
}