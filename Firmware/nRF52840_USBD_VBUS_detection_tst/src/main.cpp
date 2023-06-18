#include <Arduino.h>

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, LOW);
}

void loop() {
  if (NRF_POWER->USBREGSTATUS)
    digitalWrite(PIN_LED1, LOW);
  else
    digitalWrite(PIN_LED1, HIGH);
}



