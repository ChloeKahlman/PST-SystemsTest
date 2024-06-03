// A short program that periodically writes the raw temperature sensor readings to serial
// Written by Geoffrey Frankhuizen

// Wire connections:
// D20 -> A
// GND -> GND (on the right)

#define TEMP_SENSOR A6

void setup() {
}

void loop() {
  char strBuf[50];
  sprintf(strBuf, "Raw temperature: %d", analogRead(TEMP_SENSOR));
  Serial.println(strBuf);
  delay(50);
}
