#pragma once

#include <Arduino.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

// ===================== interrupt parameters =====================
#define HW_TIMER_INTERVAL_MS 1

#define TIMER_INTERVAL_1s    1000L
#define TIMER_INTERVAL_5s    5000L

extern bool volatile timer4Interrupt_1s;
extern bool volatile timer4Interrupt_5s;

// #ifdef __cplusplus
// }
// #endif