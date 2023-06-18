#include <Arduino.h>

#include "PWR.h"

void enable_DCDC(void) {
  NRF_POWER->DCDCEN  = 1UL;
  NRF_POWER->DCDCEN0 = 1UL;
}