#include "DATA.h"
#include "SYSTEM.h"
#include "IMU.h"
#include "FRAM.h"
#include "ONBOARD_TEMP.h"
#include "SIDE.h"
#include "SDCARD.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

struct HexSense_frame hexsense_frame;

byte * HexSense_byte_temp;

uint32_t Time_stamp = 0;
uint8_t  seq_num = 0;

uint8_t HexSense_pkg_rd_from_FRAM[PKG_LEN] = {0x00};

int side_num    = 0;
int side_ch_num = 0;

uint16_t Pkg_num    = 0;
uint16_t Pkg_rd_num = 0;

// File to store data
File dataFile;

// const char SD_File_name[] = "HexSenseLog.csv";

/*
// data: data to be put into the HexSense_pkg
// pos: position to insert the data
// len: length of the data
void pack_data_into_HexSense_pkg(byte * data, int index, int len) {
  memcpy(&HexSense_pkg[index], data, len);
}
*/

void pack_a_hexsense_packet(void) {
  // TMP112 data needs ~30ms to converge, so make it start the measurement earlier.
  TMP112_take_a_measurement();

  // Timestamp
  Time_stamp = millis();
  hexsense_frame.time_stamp = Time_stamp;
  if (DEBUG_OUTPUT) DEBUG_info("Time_stamp = ", Time_stamp);

  // Sequence number
  seq_num ++;
  hexsense_frame.Seq_num = seq_num;
  if (DEBUG_OUTPUT) DEBUG_info("seq_num = ", seq_num);

  // IMU data
  IMU_wake();
  Get_IMU_data();
  hexsense_frame.ACCX = accx;
  hexsense_frame.ACCY = accy;
  hexsense_frame.ACCZ = accz;

  if (DEBUG_OUTPUT) DEBUG_info("accx = ", accx);

  hexsense_frame.GYROX = gyrox;
  hexsense_frame.GYROY = gyroy;
  hexsense_frame.GYROZ = gyroz;
  IMU_sleep();

  // Internal temperature
  TMP112_get_data();
  hexsense_frame.Internal_Temp = board_temperature;
  if (DEBUG_OUTPUT) DEBUG_info("board_temperature = ", board_temperature);

  if (TST_WITHOUT_SIDE) {
    for (side_num = 0; side_num < SIDE_cnt; side_num ++) {
      for (side_ch_num = 0; side_ch_num < AS7341_ch_cnt; side_ch_num++) {
        hexsense_frame.AS7341_data[side_num][side_ch_num] = side_num + side_ch_num;
      }

      hexsense_frame.SHT40_temp[side_num] = side_num * 0.1;
      hexsense_frame.SHT40_humd[side_num] = side_num * 1.1;
    }
  }

  else {
    for (side_num = 0; side_num < SIDE_cnt; side_num ++) {
      hexsense_side[side_num].SIDE_select();
      hexsense_side[side_num].SIDE_get_as7341_result();
      for (side_ch_num = 0; side_ch_num < AS7341_ch_cnt; side_ch_num++) {
        hexsense_frame.AS7341_data[side_num][side_ch_num] = hexsense_side[side_num].as7341_result[side_ch_num];
      }

      hexsense_side[side_num].SIDE_get_sht40_temp_humd();
      hexsense_frame.SHT40_temp[side_num] = hexsense_side[side_num].sht4_temp;
      hexsense_frame.SHT40_humd[side_num] = hexsense_side[side_num].sht4_humd;
    }
  }

  CONN_shutdown(); // disable all channels to save power

  // TODO:
  // - Calculate CRC
  hexsense_frame.CRC = 0x19;
}

void update(void) {
  pack_a_hexsense_packet();

  write_a_hexsense_packet_to_fram(FRAM_w_P, (uint8_t *) (&hexsense_frame), HexSense_frame_len);
  FRAM_w_P += HexSense_frame_len;
  Pkg_num  ++;

  if (FRAM_w_P >= (FRAM_ADDR_TOP - HexSense_frame_len)) {

    dataFile = SD.open("hexsense.csv", FILE_WRITE);

    if (dataFile) {
      // Write all packages into the SD card
      for (Pkg_rd_num = 0; Pkg_rd_num < Pkg_num; Pkg_rd_num ++) {
        if (DEBUG_OUTPUT) {
          Serial.print(F("FRAM_r_P = ")); Serial.println(FRAM_r_P);
        }
        read_a_hexsense_packet_from_FRAM(FRAM_r_P);

        SD_write_file(dataFile, HexSense_pkg_rd_from_FRAM, HexSense_frame_len);
        FRAM_r_P += HexSense_frame_len;
      }
      dataFile.close();
    }
    else {
      // problem with opening the file:
      // https://forum.arduino.cc/t/sd-card-does-not-open-file/212389
      Serial.println(F("error opening hexsense.csv"));
    }

    FRAM_r_P = 0;
    FRAM_w_P = 0;
    Pkg_num = 0;
  }
}

// #ifdef __cplusplus
// }
// #endif)
