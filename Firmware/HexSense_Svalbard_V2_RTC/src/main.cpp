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
#include "FLASH.h"
#include "SIDE.h"
#include "RTC.h"
#include "PWR.h"

// ================== system parameters ==================
int _wait_time = 0;
int _side_num  = 0;

void system_init(void) {
  if (DEBUG_OUTPUT) Serial_Setup();

  Pins_init();
  IMU_init();
  TMP112_init();
  fram_setup();
  // SD_init();
  CONN_init();

  for (_side_num = 0; _side_num < SIDE_cnt; _side_num ++) {
    hexsense_side[_side_num].SIDE_select();
    hexsense_side[_side_num].SIDE_init();
    delay(10);
  }

  delay(100);

  // wait for 30s before the main function
  while (_wait_time < DELAY_TIME) {
    _wait_time ++;
    Flash_LED_once(PIN_LED1, 50);
    delay(1000);
  }

  rtc_init();

  // calculate current orientation and choose which resistor to burn;
  // start burning resistor for 10s, and check orientation;
  // If orientation is OK, keep going to loop;
}

void setup(void) {
  if (DEBUG_OUTPUT) {
    system_init();
  }
  else {
    // If VBUS is conencetd, means it's being chared and should not start working.
    while (VBUS_connected()) {
      delay(10);
      digitalWrite(PIN_LED1, HIGH);
    }

    // when the +5V is removed, start working
    digitalWrite(PIN_LED1, LOW);
    system_init();
  }
}

void loop() {
  enable_DCDC();

  __SEV();
  __WFE();
  __WFE();

  if (RTC_COMPARE_triggered()) {
    RTC_Clear();
    update();
    // Store data in Flash
    // if Flash is about to be full, move all data to SD card
    Flash_LED_once(PIN_LED1, 50);
  }
}







