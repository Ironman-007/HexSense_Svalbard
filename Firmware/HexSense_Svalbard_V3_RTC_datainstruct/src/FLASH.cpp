// #include "FLASH.h"

// Adafruit_SPIFlash flash(&flashTransport);

// // file system object from SdFat
// FatVolume fatfs;
// File32 myFile;

// void FLAHS_init(void) {
//   // Init external flash
//   flash.begin();

//   // Open file system on the flash
//   fatfs.begin(&flash);
// }

// void Write2FLASH() {
//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   myFile = fatfs.open("test.txt", FILE_WRITE);

//   // if the file opened okay, write to it:
//   if (myFile) {
//     Serial.print("Writing to test.txt...");
//     myFile.println("testing 1, 2, 3.");
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }

//   // re-open the file for reading:
//   myFile = fatfs.open("test.txt");
//   if (myFile) {
//     Serial.println("test.txt:");

//     // read from the file until there's nothing else in it:
//     while (myFile.available()) {
//       Serial.write(myFile.read());
//     }
//     // close the file:
//     myFile.close();
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
// }
