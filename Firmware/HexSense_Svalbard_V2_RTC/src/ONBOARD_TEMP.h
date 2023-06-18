#pragma once

#include <Wire.h> // Used to establied serial communication on the I2C bus
#include <SparkFunTMP102.h> // Used to send and recieve specific information from our sensor

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

extern float board_temperature;

// Connections
// VCC = 3.3V
// GND = GND
// SDA = A4
// SCL = A5

extern TMP102 tmp112;
// Sensor address can be changed with an external jumper to:
// ADD0 - Address
//  VCC - 0x49
//  SDA - 0x4A
//  SCL - 0x4B

extern void TMP112_init(void);
extern void TMP112_take_a_measurement(void);
extern void TMP112_get_data(void);

#ifdef __cplusplus
}
#endif