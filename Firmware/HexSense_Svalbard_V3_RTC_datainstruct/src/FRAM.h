#pragma once

#include <Arduino.h>

#include "Adafruit_FRAM_SPI.h"

// #define FRAM_ADDR_TOP 260000 // 256KB
#define FRAM_ADDR_TOP 25000 // 256KB

#define FRAM_CS_pin   PIN_SERIAL1_RX // RXD is the CS

// FRAM write and read pointers
extern uint16_t FRAM_r_P;
extern uint16_t FRAM_w_P;

extern Adafruit_FRAM_SPI fram;

extern void fram_setup(void);
extern void write_a_hexsense_packet_to_fram(uint16_t w_pointer, uint8_t * pkg, int pkg_len);
extern void read_a_hexsense_packet_from_FRAM(uint16_t r_pointer);
