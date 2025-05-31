// A short program that allows the user to test the buttons, LEDs, potentiometer and buzzer
//
// Written by Chloe Kahlman
// Adapted by Geoffrey Frankhuizen

// Wire connections:
// D8 -> LD1
// D9 -> LD2
// D10 -> LD3
// D11 -> LD4
// D12 -> SW1
// D13 -> SW2
// D14 -> SW3
// D15 -> SW4
// D20 -> POT
// D21 -> BUZ

#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define SWITCH1 12
#define SWITCH2 13
#define SWITCH3 14
#define SWITCH4 15
#define POT A6
#define BUZ 21

void setup() {
  Serial.begin(9600);
  Serial.println("Start!");

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);
  pinMode(SWITCH4, INPUT);
  pinMode(POT, INPUT);
  pinMode(BUZ, OUTPUT);
  digitalWrite(BUZ, LOW);
}

void loop() {
  if (digitalRead(SWITCH1)) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (digitalRead(SWITCH2)) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }

  if (!digitalRead(SWITCH3)) {
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }

  if (!digitalRead(SWITCH4)) {
    digitalWrite(LED4, HIGH);
  } else {
    digitalWrite(LED4, LOW);
  }

  Serial.print("Potentiometer: ");
  Serial.println(analogRead(POT));

  if (analogRead(POT) > 500) {
    digitalWrite(BUZ, HIGH);
  } else {
    digitalWrite(BUZ, LOW);
  }
  delay(100);
}
