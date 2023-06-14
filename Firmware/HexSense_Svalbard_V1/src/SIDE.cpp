#include "SIDE.h"

SIDE::SIDE() {
  this -> side_num = side_num;
  this -> f_415nm  = 0;
  this -> f_445nm  = 0;
  this -> f_480nm  = 0;
  this -> f_515nm  = 0;
  this -> f_555nm  = 0;
  this -> f_590nm  = 0;
  this -> f_630nm  = 0;
  this -> f_680nm  = 0;
  this -> f_clear  = 0;
  this -> f_ir     = 0;

  this -> side_lux = 0;

  // this -> veml6030 = SparkFun_Ambient_Light(0x40);
}

void SIDE::SIDE_init() {
  this -> as7341.begin();
  this -> veml6030.set_address(0x40);
  this -> veml6030.begin();
}
