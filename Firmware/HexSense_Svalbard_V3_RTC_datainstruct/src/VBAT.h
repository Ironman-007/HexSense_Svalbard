#pragma once

#include <Arduino.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

#define R_VBAT_a    10
#define R_VBAT_b    10

#define Vbat_PIN    A2

extern float Vbat; // battery voltage = (AD_reading - R_VBAT_b)/R_VBAT_a

extern void get_battery_voltage(uint32_t ain);

// #ifdef __cplusplus
// }
// #endif