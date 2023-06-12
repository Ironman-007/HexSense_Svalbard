#include <Arduino.h>

#include "SYSTEM.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

int i = 0;

// define pins to use
#define PINS2USE_CNT 2

int     PINS2USE[PINS2USE_CNT]            = {PIN_LED1, WDI_PIN};
uint8_t PINS2USE_MODE[PINS2USE_CNT]       = {OUTPUT, OUTPUT};
uint8_t PINS2USE_INIT_VALUE[PINS2USE_CNT] = {LOW, LOW};

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

void WD_setup(int wdi_pin) {
  analogWrite(wdi_pin, 128);
}

// DEBUG_info templates
void DEBUG_info(const char * info) {
  Serial.println(info);
}

void DEBUG_info(const char * info, int data) {
  Serial.print(info);
  Serial.println(data);
}

void DEBUG_info(const char * info, uint32_t data) {
  Serial.print(info);
  Serial.println(data);
}

void DEBUG_info(const char * info, float data) {
  Serial.print(info);
  Serial.println(data);
}

// #ifdef __cplusplus
// }
// #endif