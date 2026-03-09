const int ldrPin = 2; 
// List all your LED pins in an array
const int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3};
const int numLeds = 11; // Total number of LEDs

void setup() {
  pinMode(ldrPin, INPUT);
  
  // This loop sets all 11 pins as OUTPUT automatically
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  Serial.begin(9600);
}

void loop() {
  int isDark = digitalRead(ldrPin);

  if (isDark == HIGH) {
    // Turn all LEDs ON
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    Serial.println("It's Dark - Lights ON");
  } else {
    // Turn all LEDs OFF
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    Serial.println("It's Light - Lights OFF");
  }
  
  delay(100);
}