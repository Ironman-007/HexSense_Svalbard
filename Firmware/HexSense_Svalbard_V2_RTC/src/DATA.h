#pragma once

#include <Arduino.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

extern uint8_t seq_num;

#define FLOAT_SIZE           4
#define WORD_SIZE            2

#define PKG_LEN              202

#define TIME_STAMP_INDEX     0
#define TIME_STAMP_INDEX_LEN 4
#define SEQ_NUM_INDEX        4
#define SEQ_NUM_LEN          1
#define IMU_DATA_INDEX       5
#define TMP112_DATA_INDEX    29
#define AS7341_DATA_INDEX    33
#define SHT4x_DATA_INDEX     153

extern uint8_t HexSense_pkg[PKG_LEN];

extern void pack_a_hexsense_packet(void);
extern void pack_data_into_HexSense_pkg(byte * data, int index, int len);
extern void update(void);

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
  int AS7341_1_CH1;
  int AS7341_1_CH2;
  int AS7341_1_CH3;
  int AS7341_1_CH4;
  int AS7341_1_CH5;
  int AS7341_1_CH6;
  int AS7341_1_CH7;
  int AS7341_1_CH8;
  int AS7341_1_CH9;
  int AS7341_1_CH10;

  int AS7341_2_CH1;
  int AS7341_2_CH2;
  int AS7341_2_CH3;
  int AS7341_2_CH4;
  int AS7341_2_CH5;
  int AS7341_2_CH6;
  int AS7341_2_CH7;
  int AS7341_2_CH8;
  int AS7341_2_CH9;
  int AS7341_2_CH10;

  int AS7341_3_CH1;
  int AS7341_3_CH2;
  int AS7341_3_CH3;
  int AS7341_3_CH4;
  int AS7341_3_CH5;
  int AS7341_3_CH6;
  int AS7341_3_CH7;
  int AS7341_3_CH8;
  int AS7341_3_CH9;
  int AS7341_3_CH10;

  int AS7341_4_CH1;
  int AS7341_4_CH2;
  int AS7341_4_CH3;
  int AS7341_4_CH4;
  int AS7341_4_CH5;
  int AS7341_4_CH6;
  int AS7341_4_CH7;
  int AS7341_4_CH8;
  int AS7341_4_CH9;
  int AS7341_4_CH10;

  int AS7341_5_CH1;
  int AS7341_5_CH2;
  int AS7341_5_CH3;
  int AS7341_5_CH4;
  int AS7341_5_CH5;
  int AS7341_5_CH6;
  int AS7341_5_CH7;
  int AS7341_5_CH8;
  int AS7341_5_CH9;
  int AS7341_5_CH10;

  int AS7341_6_CH1;
  int AS7341_6_CH2;
  int AS7341_6_CH3;
  int AS7341_6_CH4;
  int AS7341_6_CH5;
  int AS7341_6_CH6;
  int AS7341_6_CH7;
  int AS7341_6_CH8;
  int AS7341_6_CH9;
  int AS7341_6_CH10;

  // SHT40 temperature data from each side
  float SHT40_temp_1;
  float SHT40_temp_2;
  float SHT40_temp_3;
  float SHT40_temp_4;
  float SHT40_temp_5;
  float SHT40_temp_6;

  // SHT40 humidity data from each side
  float SHT40_humd_1;
  float SHT40_humd_2;
  float SHT40_humd_3;
  float SHT40_humd_4;
  float SHT40_humd_5;
  float SHT40_humd_6;

  uint8_t CRC;
};

// #ifdef __cplusplus
// }
// #endif

