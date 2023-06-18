#include <Arduino.h>

void rtc_handler(void) {
  digitalToggle(PIN_LED1);
}

static void lfclk_config(void) {
  // Set the LFCLK source
  NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_Xtal;
  // Start the LFCLKSTART task
  NRF_CLOCK->TASKS_LFCLKSTART = true;
}

static void lfclk_stop(void) {
  // Start the LFCLKSTART task
  NRF_CLOCK->TASKS_LFCLKSTOP = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, LOW);
}

void loop() {
  ;
}
