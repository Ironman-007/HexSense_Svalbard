#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "SparkFun_TCA9534.h"

#define BR_GPIO_CNT  6

extern TCA9534 BR_GPIO;

// pin_index: channels to be used
extern void BR_GPIO_init(void);

extern void BR_BURN_R(uint8_t pin_num);
extern void BR_TURN_OFF_ALL(void);
