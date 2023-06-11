#include <Arduino.h>

#include "ONBOARD_TEMP.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

TMP102 tmp112;

float board_temperature = 0.0;

void TMP112_init(void) {
  Wire.begin();
  tmp112.begin();
  tmp112.sleep();
}

void TMP112_take_a_measurement(void) {
  tmp112.oneShot(1);
}

void TMP112_get_data(void) {
  while(tmp112.oneShot() == 0);
  board_temperature = tmp112.readTempC();
  tmp112.sleep();
}

#ifdef __cplusplus
}
#endif