#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial ss(4, 3); // GPS TX to 4, RX to 3
TinyGPSPlus gps;

void setup() {
  ss.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GPS Initializing");
  delay(2000);
  lcd.clear();
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      displayInfo();
    }
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    // Line 1: Latitude
    lcd.setCursor(0, 0);
    lcd.print("Lat: ");
    lcd.print(gps.location.lat(), 5); 
    
    // Line 2: Longitude
    lcd.setCursor(0, 1);
    lcd.print("Lng: ");
    lcd.print(gps.location.lng(), 5);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Searching...    ");
    lcd.setCursor(0, 1);
    lcd.print("Sats: ");
    lcd.print(gps.satellites.value());
  }
}