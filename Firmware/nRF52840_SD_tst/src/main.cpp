#include <SPI.h>
#include <SD.h>

const int chipSelect = A1;
const int SD_en      = A5;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {;}

  pinMode(SD_en, OUTPUT);
  digitalWrite(SD_en, HIGH);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  uint8_t data[6] = {0x01, 0x06, 0x09, 0x0A, 0x45, 0x99};
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 6; analogPin++) {
    dataString += String(data[analogPin]);
    if (analogPin < 5) {
      dataString += ",";
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    // dataFile.write(data, 6);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
