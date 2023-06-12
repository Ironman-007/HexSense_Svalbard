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

#include "INTERRUPT.h"
#include "NRF52TimerInterrupt.h"
#include "NRF52_ISR_Timer.h"

// ===================== interrupt parameter =====================
bool volatile timer4Interrupt_1s = false;
bool volatile timer4Interrupt_5s = false;

NRF52Timer ITimer(NRF_TIMER_1);
NRF52_ISR_Timer ISR_Timer;

// ===================== Interrupt functions =====================
void TimerHandler() {
  ISR_Timer.run();
}

void timer_handler_1s() {
  timer4Interrupt_1s = true;
}

void timer_handler_5s() {
  timer4Interrupt_5s = true;
}

void interrupt_setup() {
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  ISR_Timer.setInterval(TIMER_INTERVAL_1s, timer_handler_1s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5s, timer_handler_5s);
}

// ================== system parameters ==================
int _wait_time = 0;

void setup(void) {
  if (DEBUG_OUTPUT)
    Serial_Setup();

  Pins_init();
  IMU_init();
  TMP112_init();
  interrupt_setup();
  WD_setup(WDI_PIN);

  delay(100);

  // wait for 30s before the main function
  while (_wait_time < DELAY_TIME) {
    if (timer4Interrupt_1s == true) {
      timer4Interrupt_1s = false;
      _wait_time ++;
      Flash_LED_once(PIN_LED1, 50);
    }
  }

  // calculate current orientation and choose which resistor to burn;
  // start burning resistor for 10s, and check orientation;
  // If orientation is OK, keep going to loop;
}

void loop() {
  if (timer4Interrupt_5s == true) {
    timer4Interrupt_5s = false;
    update();
    Flash_LED_once(PIN_LED1, 50);
  }
}



