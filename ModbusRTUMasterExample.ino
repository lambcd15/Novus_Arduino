/*
  ModbusRTUMasterExample

  This example demonstrates how to setup and use the ModbusRTUMaster library.
  It is intended to be used with a second board running ModbusRTUSlaveExample from the ModbusRTUSlave library.

  Created: 2023-07-22
  By: C. M. Bulliner
  Modified: 2023-07-29
  By: C. M. Bulliner
  Modified: 2023-11-11
  By: C. M. Bulliner
  Modified: 2024-07-23
  By: lambcd15

*/

#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

// For the pinout ensure that the correct pins are selected for your software serial connection
const uint8_t rxPin = 10;
const uint8_t txPin = 11;
const uint8_t dePin = 3;

SoftwareSerial mySerial(rxPin, txPin);
ModbusRTUMaster modbus(mySerial, dePin); // serial port, driver enable pin for rs-485 


void processError() {
  if (modbus.getTimeoutFlag()) {
    Serial.println(F("Connection timed out"));
    modbus.clearTimeoutFlag();
  }
  else if (modbus.getExceptionResponse() != 0) {
    Serial.print(F("Received exception response: "));
    Serial.print(modbus.getExceptionResponse());
    switch (modbus.getExceptionResponse()) {
      case 1:
        Serial.println(F(" - Illegal function"));
        break;
      case 2:
        Serial.println(F(" - Illegal data address"));
        break;
      case 3:
        Serial.println(F(" - Illegal data value"));
        break;
      case 4:
        Serial.println(F(" - Server device failure"));
        break;
      default:
        Serial.println();
        break;
    }
    modbus.clearExceptionResponse();
  }
  else {
    Serial.println("An error occurred");
  }
}

void readSingleHoldingRegister(uint8_t id, uint16_t address) {
  uint16_t value = 0;
  if (modbus.readHoldingRegisters(id, address, &value, 1)) {
    Serial.print(F("Read value of "));
    Serial.print(value);
    Serial.print(F(" on slave/server device "));
    Serial.println(id);

  }
  else processError();
}

void writeSingleHoldingRegister(uint8_t id, uint16_t address, uint16_t value) {
  if (modbus.writeSingleHoldingRegister(id, address, value)) {
    Serial.print(F("Wrote value of "));
    Serial.print(value);
  }
  else processError();
}

void real_all_current(void){
  readSingleHoldingRegister(1, 0x0004);
  readSingleHoldingRegister(2, 0x0004);
  readSingleHoldingRegister(3, 0x0004);
}

void real_all_setpoint(void){
  readSingleHoldingRegister(1, 0x0000);
  readSingleHoldingRegister(2, 0x0000);
  readSingleHoldingRegister(3, 0x0000);
}

void write_all_setpoint(uint16_t value){
  writeSingleHoldingRegister(1, 0x0000, value);
  writeSingleHoldingRegister(2, 0x0000, value);
  writeSingleHoldingRegister(3, 0x0000, value);
}

uint8_t id = 1;
uint16_t address = 0x000;
uint16_t value = 0;

void setup() {

  Serial.begin(9600); // For debugging, you can use the hardware serial for Serial Monitor
  modbus.begin(9600, SERIAL_8N1); // baud rate, config (optional)
  write_all_setpoint(2000);// divide 10 as one decimal place
  delay(100);
  // command for writing the set point to a single register
  writeSingleHoldingRegister(3, 0x0000, 750);
}

void loop() {
  real_all_setpoint();
  delay(1000);
}
