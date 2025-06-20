// I2C test program for the MCP23017's on the train track
// Uses low level I2C commands (not an MCP23017 class) See
// https://developer.mbed.org/handbook/I2C
// Note that the 7-bit I2C addresses must be shifted 1 place to the right because
// MBED uses 8-bit addresses
//
// Originally written by Niels Althuisius / Elektronica Beta VU
// Ported to Arduino by Chloe Kahlman
// Adapted by Geoffrey Frankhuizen
// Using code from Jeroen Tas to assign alternative i2c pins

// Wire connections:
// D6 -> SDA
// D5 -> SCL
// GND -> GND (on the right)

#include <MCP23017.h>
#include "Arduino.h"
#include "wiring_private.h"

#define I2C_2_SDA_PIN 6
#define I2C_2_SCL_PIN 5

TwoWire secondWire(&sercom0, I2C_2_SDA_PIN, I2C_2_SCL_PIN);
MCP23017 mcp = MCP23017(0x27, secondWire);

void setup() {
  pinPeripheral(I2C_2_SDA_PIN, PIO_SERCOM_ALT);  //Assign SDA function
  pinPeripheral(I2C_2_SCL_PIN, PIO_SERCOM_ALT);  //Assign SCL function
  secondWire.begin();
  
  mcp.init();
  mcp.writeRegister(MCP23017Register::IODIR_A, (unsigned char)0x00);  // set IO direction to output
  mcp.writeRegister(MCP23017Register::IODIR_B, (unsigned char)0x00);
  mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
  mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
}

/*
cycle through all signal lights
*/
void loop() {
  uint16_t idx;
  uint16_t signals;
  for (idx = 0; idx < 16; idx++) {
    switch (idx) {
      case 0:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111110);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 1:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111101);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 2:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111011);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 3:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11110111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 4:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11101111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 5:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11011111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 6:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b10111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 7:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b01111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
        break;
      case 8:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111110);
        break;
      case 9:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111101);
        break;
      case 10:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111011);
        break;
      case 11:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11110111);
        break;
      case 12:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11101111);
        break;
      case 13:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11011111);
        break;
      case 14:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b10111111);
        break;
      case 15:
        mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
        mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b01111111);
        break;
      default:
        break;
    }
    delay(250);
  }
  mcp.writeRegister(MCP23017Register::OLAT_A, (unsigned char)0b11111111);
  mcp.writeRegister(MCP23017Register::OLAT_B, (unsigned char)0b11111111);
}
