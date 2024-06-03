// A short program that turns the heater on when switch 1 is on and off otherwise
// Written by Geoffrey Frankhuizen

// Wire connections:
// D2 -> HTR
// D5 -> SW1
// GND -> GND (on the right)

#define HEATER 2
#define SWITCH 5

void setup() {
  pinMode(HEATER, OUTPUT);
  pinMode(SWITCH, INPUT);
}

void loop() {
  if(digitalRead(SWITCH)){
  digitalWrite(HEATER, HIGH);
  } else {
  digitalWrite(HEATER, LOW);
  }
  
  delay(50);
}
