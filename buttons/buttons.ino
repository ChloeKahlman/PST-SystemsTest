#define SWITCH1 7
#define SWITCH2 8
#define SWITCH3 9
#define SWITCH4 10
#define LED1 11
#define LED2 12
#define LED3 13
#define LED4 14
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
