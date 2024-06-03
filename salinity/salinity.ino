// A short program that periodically writes the raw salinity readings to serial
// Written by Geoffrey Frankhuizen

// Wire connections:
// D17 -> B3
// GND -> GND (on the right)

#define SAL_SENSOR A3

void setup() {
}

void loop() {
  char strBuf[50];
  sprintf(strBuf, "Raw salinity: %d", analogRead(SAL_SENSOR));
  Serial.println(strBuf);
  delay(50);
}
