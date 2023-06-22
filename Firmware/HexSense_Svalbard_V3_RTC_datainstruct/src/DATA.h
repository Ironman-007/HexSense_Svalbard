#pragma once

#include <Arduino.h>

#include "SIDE.h"
#include "DATA.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

// Careful about the Data structure alignment
// extra padding bytes will be added and make the struct larger
// That's why we use sizeof(HexSense_frame) to define length
struct HexSense_frame {
  // Frame header
  uint32_t time_stamp;
  uint8_t  Seq_num;

  // IMU data
  float    ACCX;
  float    ACCY;
  float    ACCZ;
  float    GYROX;
  float    GYROY;
  float    GYROZ;

  // TMP112 data
  float    Internal_Temp;

  // Sensor data from the side PCBs
  int AS7341_data[SIDE_cnt][AS7341_ch_cnt];

  // SHT40 temperature data from each side
  float SHT40_temp[SIDE_cnt];

  // SHT40 humidity data from each side
  float SHT40_humd[SIDE_cnt];

  uint8_t CRC;
};

#define HexSense_frame_len sizeof(HexSense_frame)

#define PKG_LEN   HexSense_frame_len
extern uint8_t    HexSense_pkg_rd_from_FRAM[PKG_LEN];

extern void pack_a_hexsense_packet(void);
extern void update(void);

extern uint16_t Pkg_num;
extern uint16_t Pkg_rd_num;

// extern void pack_data_into_HexSense_pkg(byte * data, int index, int len);

// #ifdef __cplusplus
// }
// #endif

