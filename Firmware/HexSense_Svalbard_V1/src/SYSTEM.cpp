#include <Arduino.h>

#include "SYSTEM.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

int i = 0;

// define pins to use
#define PINS2USE_CNT 1

int     PINS2USE[PINS2USE_CNT]            = {PIN_LED1};
uint8_t PINS2USE_MODE[PINS2USE_CNT]       = {OUTPUT};
uint8_t PINS2USE_INIT_VALUE[PINS2USE_CNT] = {LOW};

void Serial_Setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);
}

void Pins_init(void) {
  for (i = 0; i < PINS2USE_CNT; i++) {
    pinMode(PINS2USE[i], PINS2USE_MODE[i]);
    if (PINS2USE_MODE[i]) digitalWrite(PINS2USE[i], PINS2USE_INIT_VALUE[i]);
  }
}

void Flash_LED(int LED_pin, int T_periode, int PWM_width, int times) {
  for (i = 0; i < times; i++) {
    digitalWrite(LED_pin, HIGH);
    delay(PWM_width);
    digitalWrite(LED_pin, LOW);
    delay(T_periode - PWM_width);
  }
}

void Flash_LED_once(int LED_pin, int length) {
  digitalWrite(LED_pin, HIGH);
  delay(length);
  digitalWrite(LED_pin, LOW);
}


void DEBUG_info(char * info) {
  Serial.println(info);
}

#ifdef __cplusplus
}
#endif