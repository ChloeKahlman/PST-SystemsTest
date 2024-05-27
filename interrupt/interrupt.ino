#include <MCP23017.h>

#define INT0  2
#define INT1  3

MCP23017 mcp = MCP23017(0x26); 

void setup() {
  pinMode(INT0, INPUT_PULLUP);
  pinMode(INT1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  init_mcp();
  init_interrupts();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}


void init_mcp() {
    Wire.begin();
    mcp.init();
    mcp.writeRegister(MCP23017Register::IODIR_A, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::IODIR_B, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::IPOL_A, (unsigned char )0x00);
    mcp.writeRegister(MCP23017Register::IPOL_B, (unsigned char )0x00);
    mcp.writeRegister(MCP23017Register::DEFVAL_A, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::DEFVAL_B, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::INTCON_A, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::INTCON_B, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::IOCON, (unsigned char )0x2);
    mcp.writeRegister(MCP23017Register::GPPU_A, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::GPPU_B, (unsigned char )0xff);
}

void init_interrupts() {
    mcp.readRegister(MCP23017Register::GPIO_A);
    mcp.readRegister(MCP23017Register::GPIO_B);
    attachInterrupt(digitalPinToInterrupt(INT0), on_int0_change, FALLING);
    attachInterrupt(digitalPinToInterrupt(INT1), on_int1_change, FALLING);
    mcp.writeRegister(MCP23017Register::GPINTEN_A, (unsigned char )0xff);
    mcp.writeRegister(MCP23017Register::GPINTEN_B, (unsigned char )0xff);
}

void on_int0_change() {
    delayMicroseconds(2000); 
    int sensor_data = mcp.readRegister(MCP23017Register::INTCAP_A);
    Serial.println("int0:");
    Serial.print(sensor_data, BIN);
    Serial.println();
}

void on_int1_change() {
    delayMicroseconds(2000); 
    int sensor_data = mcp.readRegister(MCP23017Register::INTCAP_B);
    Serial.println("int1:");
    Serial.print(sensor_data, BIN);
    Serial.println();
}