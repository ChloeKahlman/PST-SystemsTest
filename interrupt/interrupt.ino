// A short program that demonstrates how to read the state of the train sensors 
// through the MCP23017
// Originally written by Niels Althuisius
// Adapted by Geoffrey Frankhuizen
// Using code from Jeroen Tas to assign alternative i2c pins

// Wire connections:
// D2 -> INT0
// D3 -> INT1
// D6 -> SDA
// D5 -> SCL
// GND -> GND (on the right)

#include <MCP23017.h>
#include "Arduino.h"
#include "wiring_private.h"

#define INT0  2
#define INT1  3
#define I2C_2_SDA_PIN   6
#define I2C_2_SCL_PIN   5

TwoWire secondWire(&sercom0, I2C_2_SDA_PIN, I2C_2_SCL_PIN);
MCP23017 mcp = MCP23017(0x26,  secondWire); 

void setup() {
  pinMode(INT0, INPUT_PULLUP);
  pinMode(INT1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  pinPeripheral( I2C_2_SDA_PIN, PIO_SERCOM_ALT );   //Assign SDA function
  pinPeripheral( I2C_2_SCL_PIN, PIO_SERCOM_ALT );   //Assign SCL function

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
    secondWire.begin();
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
