#include "SIDE.h"
#include "SYSTEM.h"

TCA9548 MP(0x70);

void CONN_init(void){
  MP.begin();
}

void CONN_shutdown(void){
  MP.disableAllChannels();
}

SIDE::SIDE(int ch_num) {
  // this -> veml6030_lux = 0;
  this -> channel_num = ch_num;
  this -> sht4_temp   = 0.0;
  this -> sht4_humd   = 0.0;
}

bool SIDE::SIDE_select(void) {
  return MP.selectChannel(this -> channel_num);
}

void SIDE::SIDE_init() {
  this -> as7341.begin();
  this -> as7341.setATIME(99);
  this -> as7341.setASTEP(999);
  this -> as7341.setGain(AS7341_GAIN_2X);
  // this -> veml6030.set_address(0x40);
  // this -> veml6030.begin();
  this -> sht4.begin();
  this -> sht4.setPrecision(SHT4X_MED_PRECISION);
  this -> sht4.setHeater(SHT4X_NO_HEATER);
}

uint16_t* SIDE::SIDE_get_as7341_result(void) {
  this -> as7341.readAllChannels();
  as7341_result[0] = this -> as7341.getChannel(AS7341_CHANNEL_415nm_F1);
  as7341_result[1] = this -> as7341.getChannel(AS7341_CHANNEL_445nm_F2);
  as7341_result[2] = this -> as7341.getChannel(AS7341_CHANNEL_480nm_F3);
  as7341_result[3] = this -> as7341.getChannel(AS7341_CHANNEL_515nm_F4);
  as7341_result[4] = this -> as7341.getChannel(AS7341_CHANNEL_555nm_F5);
  as7341_result[5] = this -> as7341.getChannel(AS7341_CHANNEL_590nm_F6);
  as7341_result[6] = this -> as7341.getChannel(AS7341_CHANNEL_630nm_F7);
  as7341_result[7] = this -> as7341.getChannel(AS7341_CHANNEL_680nm_F8);
  as7341_result[8] = this -> as7341.getChannel(AS7341_CHANNEL_CLEAR);
  as7341_result[9] = this -> as7341.getChannel(AS7341_CHANNEL_NIR);

  return as7341_result;
}

void SIDE::SIDE_get_sht40_temp_humd(void) {
  this -> sht4.getEvent(&(this -> humidity_event), &(this -> temp_event));
  this -> sht4_temp = this -> temp_event.temperature;
  this -> sht4_humd = this -> humidity_event.relative_humidity;
}

// int SIDE::SIDE_get_veml6030_lux(void){
//   return veml6030_lux;
// }
SIDE hexsense_side[SIDE_cnt] = {SIDE(0), SIDE(3), SIDE(2), SIDE(5), SIDE(4), SIDE(7)};
// SIDE hexsense_side[SIDE_cnt] = {SIDE(0), SIDE(2), SIDE(3)};
