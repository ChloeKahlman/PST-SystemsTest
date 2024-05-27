#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Hello world!");
}

void loop() {
  lcd.setBacklight(HIGH);
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}
