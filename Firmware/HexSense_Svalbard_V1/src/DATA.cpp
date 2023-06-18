#include "DATA.h"
#include "SYSTEM.h"
#include "IMU.h"
#include "FRAM.h"
#include "ONBOARD_TEMP.h"
#include "SIDE.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

byte * HexSense_byte_temp;

uint32_t Time_stamp = 0;
uint8_t  seq_num = 0;

uint8_t HexSense_pkg[PKG_LEN] = {0x00};

int side_num    = 0;
int side_ch_num = 0;

// data: data to be put into the HexSense_pkg
// pos: position to insert the data
// len: length of the data
void pack_data_into_HexSense_pkg(byte * data, int index, int len) {
  memcpy(&HexSense_pkg[index], data, len);
}

void pack_a_hexsense_packet(void) {
  // TMP112 data needs ~30ms to converge, so make it start the measurement earlier.
  TMP112_take_a_measurement();

  // Timestamp
  Time_stamp = millis();
  if (DEBUG_OUTPUT) DEBUG_info("Time_stamp = ", Time_stamp);
  HexSense_byte_temp = (byte *) &Time_stamp;
  pack_data_into_HexSense_pkg(HexSense_byte_temp, TIME_STAMP_INDEX, TIME_STAMP_INDEX_LEN);

  // Sequence number
  seq_num ++;
  HexSense_byte_temp = (byte *) &seq_num;
  if (DEBUG_OUTPUT) DEBUG_info("seq_num = ", seq_num);
  pack_data_into_HexSense_pkg(HexSense_byte_temp, SEQ_NUM_INDEX, SEQ_NUM_LEN);

  // IMU data
  IMU_wake();
  Get_IMU_data();
  HexSense_byte_temp = (byte *) &accx;
  if (DEBUG_OUTPUT) DEBUG_info("accx = ", accx);
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
  IMU_sleep();

  // Internal temperature
  TMP112_get_data();
  HexSense_byte_temp = (byte *) &board_temperature;
  if (DEBUG_OUTPUT) DEBUG_info("board_temperature = ", board_temperature);
  pack_data_into_HexSense_pkg(HexSense_byte_temp, TMP112_DATA_INDEX, FLOAT_SIZE);

  for (side_num = 0; side_num < SIDE_cnt; side_num ++) {
    hexsense_side[side_num].SIDE_select();
    hexsense_side[side_num].SIDE_get_as7341_result();
    for (side_ch_num = 0; side_ch_num < AS7341_ch_cnt; side_ch_num++) {
      HexSense_byte_temp = (byte *) &(hexsense_side[side_num].as7341_result[side_ch_num]);
      if (DEBUG_OUTPUT) DEBUG_info("as7341 = ", hexsense_side[side_num].as7341_result[side_ch_num]);
      pack_data_into_HexSense_pkg(HexSense_byte_temp, AS7341_DATA_INDEX + side_ch_num * WORD_SIZE + side_num * AS7341_ch_cnt * WORD_SIZE, WORD_SIZE);
    }

    hexsense_side[side_num].SIDE_get_sht40_temp_humd();
    HexSense_byte_temp = (byte *) &(hexsense_side[side_num].sht4_temp);
    if (DEBUG_OUTPUT) DEBUG_info("SHT40 TEMP = ", hexsense_side[side_num].sht4_temp);
    pack_data_into_HexSense_pkg(HexSense_byte_temp, SHT4x_DATA_INDEX + side_num * 2 * FLOAT_SIZE, FLOAT_SIZE);

    HexSense_byte_temp = (byte *) &(hexsense_side[side_num].sht4_humd);
    if (DEBUG_OUTPUT) DEBUG_info("SHT40 HUMD = ", hexsense_side[side_num].sht4_humd);
    pack_data_into_HexSense_pkg(HexSense_byte_temp, SHT4x_DATA_INDEX + side_num * 2 * FLOAT_SIZE + FLOAT_SIZE, FLOAT_SIZE);
  }

  CONN_shutdown(); // disable all channels to save power

  // CRC
}

void update(void) {
  pack_a_hexsense_packet();

  /*
  write_a_hexsense_packet_to_fram(FRAM_w_P, HexSense_pkg, PKG_LEN);
  FRAM_w_P += PKG_LEN;

  if (FRAM_w_P >= FRAM_ADDR_TOP) {
    // move data to SD card;
    FRAM_w_P = 0;
  }
  */
}

// #ifdef __cplusplus
// }
// #endif