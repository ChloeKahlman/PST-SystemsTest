// A short program compressing and decompressing both motors in turn
// Written by Geoffrey Frankhuizen

// Wire connections:
// D2 -> EN (MOTOR A)
// D3 -> STP (MOTOR A)
// D4 -> DIR (MOTOR A)
// D5 -> EN (MOTOR B)
// D6 -> STP (MOTOR B)
// D7 -> DIR (MOTOR B)
// GND -> M0 (MOTOR A)
// GND -> M1 (MOTOR A)
// GND -> M2 (MOTOR A)
// GND -> M0 (MOTOR B)
// GND -> M1 (MOTOR B)
// GND -> M2 (MOTOR B)
// 3.3V -> SLP

#define MOT_A_EN 2
#define MOT_A_STP 3
#define MOT_A_DIR 4
#define MOT_B_EN 5
#define MOT_B_STP 6
#define MOT_B_DIR 7

#define STEP_DELAY 1000
#define NUMBER_OF_STEPS 2500

#define MOTOR_A 0
#define MOTOR_B 1

#define COMPRESS 0
#define DECOMPRESS 1

void setup() {
}

void loop() {
  delay(5000);

  activate_motor(MOTOR_A, COMPRESS, NUMBER_OF_STEPS);
  delay(1000);
  activate_motor(MOTOR_A, DECOMPRESS, NUMBER_OF_STEPS);
  delay(1000);
  activate_motor(MOTOR_B, COMPRESS, NUMBER_OF_STEPS);
  delay(1000);
  activate_motor(MOTOR_B, DECOMPRESS, NUMBER_OF_STEPS);
}

void activate_motor(bool motorId, bool direction, int number_of_steps) {
  int enablePin = motorId ? MOT_B_EN : MOT_A_EN;
  int stepPin = motorId ? MOT_B_STP : MOT_A_STP;
  int directionPin = motorId ? MOT_B_DIR : MOT_A_DIR;

  // Enable motor
  digitalWrite(enablePin, LOW);

  // Begin with (de)compressing
  if (motorId) {
    digitalWrite(directionPin, !direction);
  } else {
    digitalWrite(directionPin, direction);
  }
  for (int i = 0; i < number_of_steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(STEP_DELAY);
  }

  // Disable motor
  digitalWrite(enablePin, HIGH);
}
