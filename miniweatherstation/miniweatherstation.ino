#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for I2C LCD
#include <Adafruit_BMP280.h>

// Set the LCD address to 0x27 for a 20 chars and 4 line display
// If 0x27 doesn't work, try 0x3F
LiquidCrystal_I2C lcd(0x27, 20, 4); 
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    lcd.setCursor(0,0);
    lcd.print("Sensor Error!");
    while (1);
  }

  lcd.setCursor(0, 0);
  lcd.print("WEATHER STATION");
}

void loop() {
  // Read all possible data points
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Convert Pa to hPa
  float altitude = bmp.readAltitude(1013.25);  // Adjusted for standard sea level

  // Line 1: Temperature
  lcd.setCursor(0, 1);
  lcd.print("Temp:     ");
  lcd.print(temp, 1);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Line 2: Pressure
  lcd.setCursor(0, 2);
  lcd.print("Pres:     ");
  lcd.print(pressure, 1);
  lcd.print(" hPa");

  // Line 3: Altitude
  lcd.setCursor(0, 3);
  lcd.print("Alt :     ");
  lcd.print(altitude, 0);
  lcd.print(" m");

  delay(2000);
}