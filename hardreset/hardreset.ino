// This code reprograms the dark red train for digital mode. It does so by performing a hard reset.
// The original mbed code was written by Jim Hamblen.
// Alterations were made to perform the emergency stop by Marijn Vollaard.
// It has been altered again and ported to Arduino by Geoffrey Frankhuizen.

#define DATAPIN 16
#define ENABLEPIN 17

void setup() {
  pinMode(DATAPIN, OUTPUT); // Digital output bit used to drive track power via H-bridge
}

void loop() {
  DCC_send_command(0x01, 100);
  delay(250);
}

void DCC_send_command(uint address, uint inst, uint repeat_count) {
  uint64_t command = 0x3FFF00803FC03FD;
  uint64_t temp_command = 0x0000000000000000;
  int i = 0;
  while (i < repeat_count) {
    temp_command = command;
    for (int j = 0; j < 64; j++) {
      if ((temp_command & 0x8000000000000000) == 0) { 
        digitalWrite(DATAPIN, LOW);
        delayMicroseconds(100);
        digitalWrite(DATAPIN, HIGH);
        delayMicroseconds(100);
      } else {
        digitalWrite(DATAPIN, LOW);
        delayMicroseconds(58);
        digitalWrite(DATAPIN, HIGH);
        delayMicroseconds(58);
      }
      temp_command = temp_command << 1;
    }
    i++;
  }
}
