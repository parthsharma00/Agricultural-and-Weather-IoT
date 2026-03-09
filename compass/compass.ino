#include <QMC5883LCompass.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

QMC5883LCompass compass;
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte needle[8] = {0b00100,0b01110,0b11111,0b00100,0b00100,0b00100,0b00100,0b00100};

// The sliding horizon tape
char tape[] = "---W---NW---N---NE---E---SE---S---SW---W---NW---N---NE---E---";

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, needle);
  compass.init();
}

void loop() {
  compass.read();
  int azimuth = compass.getAzimuth();

  // Normalize to 0-359
  while (azimuth < 0) azimuth += 360;
  while (azimuth >= 360) azimuth -= 360;

  // --- THE FINAL ALIGNMENT ---
  // Changed 12 to 19 to pull 'N' into the center
  int tapePos = map(azimuth, 0, 359, 5, 43); 
  
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    lcd.print(tape[tapePos + i]);
  }

  // --- ROW 1: DATA & NEEDLE ---
  lcd.setCursor(0, 1);
  if(azimuth < 100) lcd.print("0");
  if(azimuth < 10) lcd.print("0");
  lcd.print(azimuth);
  lcd.print((char)223);

  lcd.setCursor(7, 1); // This puts the needle at column 8
  lcd.write(0); 

  lcd.setCursor(12, 1);
  if (azimuth > 337 || azimuth <= 22)      lcd.print(" N  ");
  else if (azimuth > 22 && azimuth <= 67)  lcd.print(" NE ");
  else if (azimuth > 67 && azimuth <= 112) lcd.print(" E  ");
  else if (azimuth > 112 && azimuth <= 157)lcd.print(" SE ");
  else if (azimuth > 157 && azimuth <= 202)lcd.print(" S  ");
  else if (azimuth > 202 && azimuth <= 247)lcd.print(" SW ");
  else if (azimuth > 247 && azimuth <= 292)lcd.print(" W  ");
  else if (azimuth > 292 && azimuth <= 337)lcd.print(" NW ");

  delay(100); 
}