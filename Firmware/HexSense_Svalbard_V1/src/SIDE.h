#pragma once

#include <Arduino.h>
#include <Adafruit_AS7341.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

class SIDE
{
private:
  Adafruit_AS7341 as7341;
  SparkFun_Ambient_Light veml6030;

  int side_num;
  int f_415nm;
  int f_445nm;
  int f_480nm;
  int f_515nm;
  int f_555nm;
  int f_590nm;
  int f_630nm;
  int f_680nm;
  int f_clear;
  int f_ir;

  int side_lux;

public:
  SIDE();
  void SIDE_init();
};



