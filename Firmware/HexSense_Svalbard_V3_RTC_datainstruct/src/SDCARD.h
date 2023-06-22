#pragma once

#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#define SD_CSS_PIN   A1
#define SD_EN_PIN    A5

extern File dataFile;

extern void SD_POWERON(void);
extern void SD_POWEROFF(void);

extern void SD_init(void);

extern void SD_write_file(File filename, uint8_t * data, uint32_t data_len);

// extern void SD_open_file(const char *  filename);
// extern void SD_close_file(const char *  filename);

// extern void
