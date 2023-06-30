#pragma once

#include <Arduino.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

#define LED_indicator PIN_SERIAL1_TX
#define MATHPI        3.1415  // pi
#define G_earth       9.807
#define WDI_PIN       2       // watchdog feeding pin

#define DELAY_TIME    30 // 30s
extern int _wait_time;

#define BAT_A_PIN        A2

#define DEBUG_OUTPUT     false
#define TST_WITHOUT_SIDE false

extern float Body_Orientation; // in degrees

extern uint32_t Time_stamp;

extern volatile bool burn_resistor_check;

extern void Serial_Setup(void);

extern void Pins_init(void);
extern void Flash_LED(int LED_pin, int T_periode, int PWM_width, int times);
extern void Flash_LED_once(int LED_pin, int length);

extern void WD_setup(int wdi_pin);

extern void WDI_output(int wdi_pin);

extern void DEBUG_info(const char * info);
extern void DEBUG_info(const char * info, int data);
extern void DEBUG_info(const char * info, uint32_t data);
extern void DEBUG_info(const char * info, float data);

extern uint32_t VBUS_connected(void);

extern void calculate_orientation(void);
extern void Burn_resistor(float orientation);

// #ifdef __cplusplus
// }
// #endif








