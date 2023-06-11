#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>

#include "SYSTEM.h"
#include "IMU.h"
#include "ONBOARD_TEMP.h"
#include "BR.h"
#include "DATA.h"
#include "FRAM.h"

void setup(void) {
  Serial_Setup();
  Pins_init();
  IMU_init();
  TMP112_init();
  // delay for 20s, flash LED during waiting;
  // calculate current orientation and choose which resistor to burn;
  // start burning resistor for 10s, and check orientation;
  // If orientation is OK, keep going to loop;
}

void loop() {
  /*
    if (flag2interrupt_5s == true) {
      flag2interrupt_5s = false;
      update();
      Flash_LED_once(PIN_LED1, 10);
    }
  */
}



