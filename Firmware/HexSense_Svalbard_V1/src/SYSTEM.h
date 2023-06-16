#pragma once

#include <Arduino.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

#define LED_indicator PIN_SERIAL1_TX

#define WDI_PIN       2  // watchdog feeding pin

#define DELAY_TIME    10 // 30s
extern int _wait_time;

#define DEBUG_OUTPUT  true

extern uint32_t Time_stamp;

extern void Serial_Setup(void);

extern void Pins_init(void);
extern void Flash_LED(int LED_pin, int T_periode, int PWM_width, int times);
extern void Flash_LED_once(int LED_pin, int length);

extern void WD_setup(int wdi_pin);

extern void DEBUG_info(const char * info);
extern void DEBUG_info(const char * info, int data);
extern void DEBUG_info(const char * info, uint32_t data);
extern void DEBUG_info(const char * info, float data);

// #ifdef __cplusplus
// }
// #endif
