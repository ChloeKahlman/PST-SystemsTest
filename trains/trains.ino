#define DATAPIN 16
#define ENABLEPIN 17

const unsigned int DCCaddress_train1 = 0x01;   //dark red train
const unsigned int DCCaddress_train2 = 0x02;   //light red train
const unsigned int DCCaddress_train3 = 0x03;   //new train

unsigned int trainInstruction(bool direction, bool light, int speed) {
  unsigned int result = 0x40;  //0100 0000
  if (direction) {
    result += 0x20;  //0010 0000
  }
  if (light) {
    result += 0x10;  //0001 0000
  }
  if (speed > 0 && speed < 15) {
    result += speed + 1;
  }
  return result;
}

void DCC_send_command(uint address, uint inst, uint repeat_count) {
  uint64_t command = 0x0000000000000000;
  uint64_t temp_command = 0x0000000000000000;
  uint64_t prefix = 0x3FFF;
  uint error = 0x00;
  error = address ^ inst;
  command = (prefix << 28) | (address << 19) | (inst << 10) | ((error) << 1) | 0x01;
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

void setup() {
  pinMode(DATAPIN, OUTPUT);
  digitalWrite(DATAPIN, LOW);
  pinMode(ENABLEPIN, OUTPUT);
  digitalWrite(ENABLEPIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  DCC_send_command(DCCaddress_train1, trainInstruction(true, true, 9), 100);
  delay(25);
  DCC_send_command(DCCaddress_train2, trainInstruction(true, true, 7), 100);
  delay(25);
  DCC_send_command(DCCaddress_train3, trainInstruction(true, true, 5), 100);
  delay(25);
}
