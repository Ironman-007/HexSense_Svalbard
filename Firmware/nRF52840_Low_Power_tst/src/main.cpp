#include <Arduino.h>

#include <Wire.h> // Used to establied serial communication on the I2C bus
#include <SparkFunTMP102.h> // Used to send and recieve specific information from our sensor

#include "NRF52TimerInterrupt.h"
#include "NRF52_ISR_Timer.h"

bool volatile timer4Interrupt_5s = false;

NRF52Timer ITimer(NRF_TIMER_1);
NRF52_ISR_Timer ISR_Timer;

// ===================== Interrupt functions =====================
void TimerHandler() {
  ISR_Timer.run();
}

void timer_handler_5s() {
  timer4Interrupt_5s = true;
  digitalToggle(2);
}

void interrupt_setup() {
  ITimer.attachInterruptInterval(1000, TimerHandler);
  ISR_Timer.setInterval(5000, timer_handler_5s);
}

TMP102 tmp112;

void TMP112_init(void) {
  Wire.begin();
  tmp112.begin();
  tmp112.sleep();
}

void setup() {
  pinMode(PIN_LED1, OUTPUT); digitalWrite(PIN_LED1, LOW);
  pinMode(2, OUTPUT); digitalWrite(2, LOW);
  pinMode(PIN_BUTTON1, OUTPUT); digitalWrite(PIN_BUTTON1, LOW);

  TMP112_init();

  interrupt_setup();

  // analogWrite(2, 128);

  // sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
}

void Flash_LED_once(int LED_pin, int length) {
  digitalWrite(LED_pin, HIGH);
  delay(length);
  digitalWrite(LED_pin, LOW);
}

void loop() {
  __WFI();
  NRF_POWER->DCDCEN  = 1;
  NRF_POWER->DCDCEN0 = 1;

  if (timer4Interrupt_5s == true) {
    timer4Interrupt_5s = false;
    Flash_LED_once(PIN_LED1, 50);
  }
}
