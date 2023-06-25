#include "BR.h"

TCA9534 BR_GPIO;

uint8_t TCA9534_addr = 0x20;

static int iii = 0;

uint8_t PIN_INDEX[BR_GPIO_CNT]      = {0, 1, 2, 3, 4, 5};
bool    PIN_MODES[BR_GPIO_CNT]      = {GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT};
bool    PIN_INIT_VALUE[BR_GPIO_CNT] = {LOW, LOW, LOW, LOW, LOW, LOW};

void BR_GPIO_init(void) {
  Wire.begin();

  if (!BR_GPIO.begin(Wire, TCA9534_addr)) delay(10);

  for (iii = 0; iii < BR_GPIO_CNT; iii ++) {
    BR_GPIO.pinMode(PIN_INDEX[iii], GPIO_OUT);
    BR_GPIO.digitalWrite(PIN_INDEX[iii], LOW);
  }
}

void BR_TURN_OFF_ALL(void) {
  for (iii = 0; iii < BR_GPIO_CNT; iii ++) {
    BR_GPIO.digitalWrite(PIN_INDEX[iii], LOW);
  }
}

void BR_BURN_R(uint8_t pin_num) {
  BR_GPIO.digitalWrite(pin_num, HIGH);
}



