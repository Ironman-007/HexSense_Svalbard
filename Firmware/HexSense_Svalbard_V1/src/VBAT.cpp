#include <Arduino.h>

#include "VBAT.h"

float Vbat = 0.0;

int temp_reading = 0;

void get_battery_voltage(uint32_t ain) {
  temp_reading = analogRead(ain);
  Vbat = (temp_reading - R_VBAT_b)/R_VBAT_a;
}