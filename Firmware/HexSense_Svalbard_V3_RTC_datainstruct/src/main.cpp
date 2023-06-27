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
#include "SDCARD.h"

// ================== system parameters ==================
int _wait_time = 0;
int _side_num  = 0;

void system_init(void) {
  if (DEBUG_OUTPUT) Serial_Setup();

  Pins_init();
  IMU_init();
  TMP112_init();
  fram_setup();
  SD_init();
  CONN_init();
  BR_GPIO_init();

  WDI_output(WDI_PIN);

  for (_side_num = 0; _side_num < SIDE_cnt; _side_num ++) {
    hexsense_side[_side_num].SIDE_select();
    hexsense_side[_side_num].SIDE_init();
    delay(10);
  }

  WDI_output(WDI_PIN);

  delay(100);

  // wait for 30s before the main function
  while (_wait_time < DELAY_TIME) {
    _wait_time ++;
    // Flash_LED_once(PIN_LED1, 50);
    Flash_LED_once(LED_indicator, 50);
    delay(1000);

    WDI_output(WDI_PIN);
  }

  calculate_orientation();
  // Burn_resistor(Body_Orientation);

  rtc_init();

  WDI_output(WDI_PIN);

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
      delay(100);
      // digitalWrite(PIN_LED1, HIGH);
      digitalWrite(LED_indicator, HIGH);
    }
    // when the +5V is removed, start working
    // digitalWrite(PIN_LED1, LOW);
    digitalWrite(LED_indicator, LOW);
    system_init();
  }

  // File creation can only work in loop ..., which is very interesting
  // dataFile = SD.open("hexsense.csv", FILE_WRITE);
  // dataFile.close();
}

void loop() {
  enable_DCDC();

  __SEV();
  __WFE();
  __WFE();

  if (RTC_COMPARE_triggered()) {
    RTC_Clear();
    update();
    // Flash_LED_once(PIN_LED1, 50);
    Flash_LED_once(LED_indicator, 50);

    WDI_output(WDI_PIN);
  }
}







