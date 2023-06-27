#include <Arduino.h>
#include <math.h>

#include "SYSTEM.h"
#include "SDCARD.h"
#include "IMU.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

static int i = 0;

static float orien_accx = 0.0;
static float orien_accy = 0.0;

float Body_Orientation = 0.0; // in degrees

// define pins to use
#define PINS2USE_CNT 5

// When SD card is powered off, it will mess up the SPI lines.
int     PINS2USE[PINS2USE_CNT]            = {PIN_LED1, WDI_PIN, PIN_BUTTON1, SD_EN_PIN, LED_indicator};
uint8_t PINS2USE_MODE[PINS2USE_CNT]       = {OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT};
uint8_t PINS2USE_INIT_VALUE[PINS2USE_CNT] = {LOW, LOW, LOW, HIGH, LOW};

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

void WDI_output(int wdi_pin) {
  digitalToggle(wdi_pin);
}

// DEBUG_info templates
void DEBUG_info(const char * info) {
  Serial.println(F(info));
}

void DEBUG_info(const char * info, int data) {
  Serial.print(F(info));
  Serial.println(data);
}

void DEBUG_info(const char * info, uint32_t data) {
  Serial.print(F(info));
  Serial.println(data);
}

void DEBUG_info(const char * info, float data) {
  Serial.print(F(info));
  Serial.println(data);
}

uint32_t VBUS_connected(void) {
  return NRF_POWER->USBREGSTATUS;
}

void calculate_orientation(void) {
  IMU_wake();
  Get_IMU_data();
  orien_accx = accx;
  orien_accy = accy;
  IMU_sleep();
  Body_Orientation = atan2(accy, accx)*180/MATHPI;

  if (DEBUG_OUTPUT) {
    Serial.print("Body_Orientation = ");
    Serial.println(Body_Orientation);
  }
}

void Burn_resistor(float orientation) {
  // TODO: modify the side to be chose
  if      (Body_Orientation >= 30  && Body_Orientation < 90)   Burn_resistor(0);
  else if (Body_Orientation >= 90  && Body_Orientation < 150)  Burn_resistor(0);
  else if (Body_Orientation >= 150 && Body_Orientation < 210)  Burn_resistor(0);
  else if (Body_Orientation >= 210 && Body_Orientation < 270)  Burn_resistor(0);
  else if (Body_Orientation >= 270 && Body_Orientation < 330)  Burn_resistor(0);
  else if (Body_Orientation <  30  || Body_Orientation >= 330) Burn_resistor(0);
  else                                                         Burn_resistor(0);
}

// #ifdef __cplusplus
// }
// #endif

