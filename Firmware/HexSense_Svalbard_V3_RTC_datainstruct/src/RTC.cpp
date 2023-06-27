#include <Arduino.h>

#include "RTC.h"

bool RTC_flag = false;

void rtc_handler(void) {
  RTC_flag = true;
}

void lfclk_config(void) {
  // Set the LFCLK source
  NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_Xtal;
  // Start the LFCLKSTART task
  NRF_CLOCK->TASKS_LFCLKSTART = LFCLK_START_TASK;
}

void rtc_config() {
  NRF_RTC0->PRESCALER   = 4095UL; // freq = 32768/4096 = 8Hz
  NRF_RTC0->CC[0]       = 80UL;   // T_peroid = 80/8 = 10s
  NRF_RTC0->EVTEN       = RTC_EVTEN_COMPARE0_Msk;
  NRF_RTC0->TASKS_START = 1UL;
}

void rtc_init() {
  // The LFCLK needs to be started before using RTC
  lfclk_config();
  rtc_config();
}

uint32_t RTC_COMPARE_triggered(void) {
  return NRF_RTC0->EVENTS_COMPARE[0];
}

void RTC_Clear(void) {
  RTC_flag = false;
  // Clear COMPARE task flag
  NRF_RTC0->EVENTS_COMPARE[0] = 0UL;
  // Clear RTC counter
  NRF_RTC0->TASKS_CLEAR       = 1UL;
}



