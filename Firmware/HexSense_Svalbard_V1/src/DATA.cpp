#include <Arduino.h>

#include "DATA.h"
#include "SYSTEM.h"
#include "IMU.h"
#include "ONBOARD_TEMP.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

byte * HexSense_byte_temp;

uint32_t Time_stamp = 0;
uint8_t  seq_num = 0;

uint8_t HexSense_pkg[PKG_LEN] = {0x00};

// data: data to be put into the HexSense_pkg
// pos: position to insert the data
// len: length of the data
void pack_data_into_HexSense_pkg(byte * data, int index, int len) {
  memcpy(&HexSense_pkg[index], data, len);
}

void update(void) {
  // TMP112 data needs ~30ms to converge, so make it start the measurement earlier.
  TMP112_take_a_measurement();

  Time_stamp = millis();
  HexSense_byte_temp = (byte *) &Time_stamp;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, TIME_STAMP_INDEX, TIME_STAMP_INDEX_LEN);

  seq_num ++;
  HexSense_byte_temp = (byte *) &seq_num;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, SEQ_NUM_INDEX, SEQ_NUM_LEN);

  Get_IMU_data();
  HexSense_byte_temp = (byte *) &accx;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX, FLOAT_SIZE);
  HexSense_byte_temp = (byte *) &accy;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX + FLOAT_SIZE, FLOAT_SIZE);
  HexSense_byte_temp = (byte *) &accz;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX + 2 * FLOAT_SIZE, FLOAT_SIZE);
  HexSense_byte_temp = (byte *) &gyrox;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX + 3 * FLOAT_SIZE, FLOAT_SIZE);
  HexSense_byte_temp = (byte *) &gyroy;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX + 4 * FLOAT_SIZE, FLOAT_SIZE);
  HexSense_byte_temp = (byte *) &gyroz;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, IMU_DATA_INDEX + 5 * FLOAT_SIZE, FLOAT_SIZE);

  TMP112_get_data();
  HexSense_byte_temp = (byte *) &board_temperature;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, TMP112_DATA_INDEX, FLOAT_SIZE);

  

  /*
    TMP112_take_a_measurement();
    get data from each side;
    store in FRAM;
    check capacity of the FRAM, if close to full, store data in SD card
  */
}

#ifdef __cplusplus
}
#endif