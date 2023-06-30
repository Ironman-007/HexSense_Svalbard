#pragma once

#include <Arduino.h>
#include <Adafruit_AS7341.h>
// #include "SparkFun_VEML6030_Ambient_Light_Sensor.h"
#include "TCA9548.h"
#include "Adafruit_SHT4x.h"

#define AS7341_ch_cnt 10
#define SIDE_cnt      6

class SIDE
{
private:
  Adafruit_AS7341 as7341;
  // SparkFun_Ambient_Light veml6030;
  Adafruit_SHT4x sht4;

  // int veml6030_lux;
  uint8_t channel_num;

  sensors_event_t humidity_event;
  sensors_event_t temp_event;

public:
  SIDE(int ch_num);
  bool SIDE_select(void);
  void SIDE_init(void);
  uint16_t* SIDE_get_as7341_result(void);
  // int   SIDE_get_veml6030_lux(void);
  void SIDE_get_sht40_temp_humd(void);

  // result in 415nm, 445nm, 480nm, 515nm, 555nm, 590nm, 630nm, 680nm, clear, IR
  uint16_t as7341_result[AS7341_ch_cnt] = {};

  float sht4_temp;
  float sht4_humd;
};

// Total 6 sides on the HexSense
extern SIDE hexsense_side[SIDE_cnt];

extern TCA9548 MP;
extern void CONN_init(void);
extern void CONN_shutdown(void);
