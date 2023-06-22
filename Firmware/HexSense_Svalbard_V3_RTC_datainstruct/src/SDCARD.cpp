#include "SDCARD.h"
#include "SYSTEM.h"

// A string to be stored
static String dataString  = "";
static String SD_Filename = "";

static uint32_t i = 0;

// power on the SD card
void SD_POWERON() {
  digitalWrite(SD_EN_PIN, HIGH);
}

// power off the SD card
void SD_POWEROFF() {
  digitalWrite(SD_EN_PIN, LOW);
}

// SD card needs to be init after every power on
void SD_init() {
  SD_POWERON();
  while (!SD.begin(SD_CSS_PIN)) delay(10);
  if (DEBUG_OUTPUT) Serial.println(F("card initialized."));

  // File dataFile = SD.open("HexSenseLog", FILE_WRITE);

  // if (DEBUG_OUTPUT) {
  //   if (dataFile) Serial.println(F("dataFile created."));
  //   else          Serial.println(F("--- dataFile not created ---"));
  // }
}

// void SD_open_file(const char *  filename) {
//   dataFile = SD.open(filename, FILE_WRITE);
//   if (DEBUG_OUTPUT) {
//     if (dataFile) DEBUG_info("dataFile is built");
//     else          DEBUG_info("dataFile not built !!!!!!!");
//   }
// }

// void SD_close_file(const char * filename) {
//   dataFile.close();
// }

void SD_write_file(File file, uint8_t * data, uint32_t data_len) {
  dataString = "";
  // read three sensors and append to the string:
  for (i = 0; i < data_len; i++) {
    dataString += String(data[i]);
    if (i < data_len - 1) {
      dataString += ",";
    }
  }
  file.println(dataString);

  if (DEBUG_OUTPUT) Serial.println(dataString);
}

