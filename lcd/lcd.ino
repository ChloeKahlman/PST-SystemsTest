// A short program that displays "Hello world!" on the top line of the lcd screen
// and "Hi back!" on the lower line
// Written by ?
// Adjusted by Geoffrey Frankhuizen,
// Uses code from Jeroen Tas to use alternative pins for I2C

// Wire connections:
//
// Default
// LCD connector to board connector
//
// Alternative
// D5 -> yellow (LCD connector)
// D6 -> green (LCD connector)
// 3.3v -> red (LCD connector)
// GND -> black (LCD connector)

// Uncomment to use alternative pins for the LCD
// #define ALTERNATIVE_PINS

#include "Adafruit_LiquidCrystal.h"

#ifdef ALTERNATIVE_PINS

#include "Arduino.h"
#include "wiring_private.h"

#define I2C_2_SDA_PIN 6
#define I2C_2_SCL_PIN 5

TwoWire secondWire(&sercom0, I2C_2_SDA_PIN, I2C_2_SCL_PIN);
Adafruit_LiquidCrystal lcd(0, &secondWire);

#else

Adafruit_LiquidCrystal lcd(0);

#endif

void setup() {
#ifdef ALTERNATIVE_PINS
  pinPeripheral(I2C_2_SDA_PIN, PIO_SERCOM_ALT);  //Assign SDA function
  pinPeripheral(I2C_2_SCL_PIN, PIO_SERCOM_ALT);  //Assign SCL function
#endif
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
