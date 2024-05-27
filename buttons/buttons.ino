#define LEDS  9
#define SWITCH1 4
#define SWITCH2 5
#define SWITCH3 6
#define SWITCH4 7
#define POT A3
#define BUZ 8

void setup() {
  Serial.begin(9600);
  Serial.println("Start!");

  pinMode(LEDS, OUTPUT);
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);
  pinMode(SWITCH4, INPUT);
  pinMode(POT, INPUT);
  pinMode(BUZ, OUTPUT);
  digitalWrite(BUZ, LOW);
}

void loop() {
  if(digitalRead(SWITCH1) && digitalRead(SWITCH2) && !digitalRead(SWITCH3) && !digitalRead(SWITCH4)){
    digitalWrite(LEDS, HIGH);
  } else {
    digitalWrite(LEDS, LOW);
  }
  Serial.print("Potentiometer: ");
  Serial.println(analogRead(POT));
  digitalWrite(BUZ, HIGH);
  delay(1000);
}
