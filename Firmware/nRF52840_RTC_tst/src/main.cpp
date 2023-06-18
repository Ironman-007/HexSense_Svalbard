#include <Arduino.h>

#include "RTC.h"

void rtc_handler(void) {
  digitalToggle(PIN_LED1);
}

static void lfclk_config(void) {
  // Set the LFCLK source
  NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_Xtal;
  // Start the LFCLKSTART task
  NRF_CLOCK->TASKS_LFCLKSTART = LFCLK_START_TASK;
}

/*
static void lfclk_stop(void) {
  // Start the LFCLKSTART task
  NRF_CLOCK->TASKS_LFCLKSTOP = LFCLK_STOP_TASK;
}
*/

void rtc_config() {
  NRF_RTC0->PRESCALER   = 4095UL;
  NRF_RTC0->CC[0]       = 16UL;
  NRF_RTC0->EVTEN       = RTC_EVTEN_COMPARE0_Msk;
  NRF_RTC0->TASKS_START = 1UL;
}

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10);

  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, LOW);

  // The LFCLK needs to be started before using RTC
  lfclk_config();
  rtc_config();
}

void loop() {
  if (NRF_RTC0->EVENTS_COMPARE[0] == 1UL) {
    NRF_RTC0->EVENTS_COMPARE[0] = 0UL;
    NRF_RTC0->TASKS_CLEAR       = 1UL;
    Serial.println("EVENTS_COMPARE 0");
    // Clear RTC counter
    rtc_handler();
  }
}



