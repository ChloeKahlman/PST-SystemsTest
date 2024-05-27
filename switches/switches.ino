#define DATAPIN 16
#define ENABLEPIN 17

const unsigned int DCCaddress_decoder = 0x06;
const unsigned int DCCswitchidle = 0b10000000;
const unsigned int DCCswitch1 = 0b10000001;
const unsigned int DCCswitch2 = 0b10000010;
const unsigned int DCCswitch3 = 0b10000100;
const unsigned int DCCswitch4 = 0b10001000;

const int switchwait = 1500;

void changeSwitch1(bool inwards) {
  if (inwards) {
    DCC_send_command(DCCaddress_decoder, DCCswitch1, 1);
    DCC_send_command(DCCaddress_decoder, DCCswitchidle, 1);
    Serial.println("STATUS: Switch 1 changed inward");
  } else {
    DCC_send_command(DCCaddress_decoder, DCCswitch1, 1);
    Serial.println("STATUS: Switch 1 changed outward");
  }
}

void changeSwitch2(bool inwards) {
  if (inwards) {
    DCC_send_command(DCCaddress_decoder, DCCswitch2, 1);
    Serial.println("STATUS: Switch 2 changed inward");
  } else {
    DCC_send_command(DCCaddress_decoder, DCCswitch2, 1);
    DCC_send_command(DCCaddress_decoder, DCCswitchidle, 1);
    Serial.println("STATUS: Switch 2 changed outward");
  }
}

void changeSwitch3(bool inwards) {
  if (inwards) {
    DCC_send_command(DCCaddress_decoder, DCCswitch3, 1);
    DCC_send_command(DCCaddress_decoder, DCCswitchidle, 1);
    Serial.println("STATUS: Switch 3 changed inward");
  } else {
    DCC_send_command(DCCaddress_decoder, DCCswitch3, 1);
    Serial.println("STATUS: Switch 3 changed outward");
  }
}

void changeSwitch4(bool inwards) {
  if (inwards) {
    DCC_send_command(DCCaddress_decoder, DCCswitch4, 1);
    DCC_send_command(DCCaddress_decoder, DCCswitchidle, 1);
    Serial.println("STATUS: Switch 4 changed inward");
  } else {
    DCC_send_command(DCCaddress_decoder, DCCswitch4, 1);
    Serial.println("STATUS: Switch 4 changed outward");
  }
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
  delay(switchwait);
  changeSwitch1(true);
  delay(switchwait);
  changeSwitch2(true);
  delay(switchwait);
  changeSwitch3(true);
  delay(switchwait);
  changeSwitch4(true);
  delay(switchwait);
  changeSwitch1(false);
  delay(switchwait);
  changeSwitch2(false);
  delay(switchwait);
  changeSwitch3(false);
  delay(switchwait);
  changeSwitch4(false);
}
