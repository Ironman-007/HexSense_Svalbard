#include "FRAM.h"
#include "DATA.h"

Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS_pin);

uint16_t FRAM_r_P = 0;
uint16_t FRAM_w_P = 0;

void fram_setup(void) {
  fram.begin();

  FRAM_r_P = 0;
  FRAM_w_P = 0;
}

void write_a_hexsense_packet_to_fram(uint16_t w_pointer, uint8_t * pkg, int pkg_len) {
  fram.write(w_pointer, pkg, pkg_len);
}

void read_a_hexsense_packet_from_FRAM(uint16_t r_pointer) {
  fram.read(r_pointer, HexSense_pkg_rd_from_FRAM, HexSense_frame_len);
}



