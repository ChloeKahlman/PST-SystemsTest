// A short program that displays "Hello world!" on the top line of the lcd screen
// and "Hi back!" on the lower line
// Written by ?
// Adjusted by Geoffrey Frankhuizen

// Wire connections:
//
// LCD connector to board connector

#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello world!");
  lcd.setCursor(0, 1);
  lcd.print("Hi back!");
}

void loop() {
  lcd.setBacklight(HIGH);
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}
