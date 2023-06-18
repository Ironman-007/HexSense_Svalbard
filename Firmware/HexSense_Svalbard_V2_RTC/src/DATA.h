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

// #ifdef __cplusplus
// }
// #endif

