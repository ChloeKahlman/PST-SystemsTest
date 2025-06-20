// A short program that shows how to poll sensors D2, D21 and D22

// Wire connections:
// D11 -> M0 (MOTOR A)
// D12 -> M1 (MOTOR A)
// D13 -> M2 (MOTOR A)
// GND -> GND (on the left)

#define M0pin 11
#define M1pin 12
#define M2pin 13

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");

  pinMode(M0pin, INPUT);
  pinMode(M1pin, INPUT);
  pinMode(M2pin, INPUT);
}

void loop() {
  Serial.print("M0: ");
  Serial.print(digitalRead(M0pin));
  Serial.print("  M1: ");
  Serial.print(digitalRead(M1pin));
  Serial.print("  M2: ");
  Serial.println(digitalRead(M2pin));
  delay(1000);
}
