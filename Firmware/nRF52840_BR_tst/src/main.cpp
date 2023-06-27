#include <Arduino.h>

#include "BR.h"

char ch_read;

void setup() {
  Serial.begin(115200);
  while(!Serial) {
    delay(10);
  }

  Serial.println("BR_GPIO_init Start!");
  BR_GPIO_init();
  Serial.println("BR_GPIO_init Done!");
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    ch_read = Serial.read();

    switch(ch_read) {
      case '0':
        BR_TURN_OFF_ALL();
        BR_BURN_R(0);
        Serial.println("Turn on channel 0!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 0!");
        break;
      case '1':
        BR_TURN_OFF_ALL();
        BR_BURN_R(1);
        Serial.println("Turn on channel 1!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 1!");
        break;
      case '2':
        BR_TURN_OFF_ALL();
        BR_BURN_R(2);
        Serial.println("Turn on channel 2!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 2!");
        break;
      case '3':
        BR_TURN_OFF_ALL();
        BR_BURN_R(3);
        Serial.println("Turn on channel 3!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 3!");
        break;
      case '4':
        BR_TURN_OFF_ALL();
        BR_BURN_R(4);
        Serial.println("Turn on channel 4!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 4!");
        break; 
      case '5':
        BR_TURN_OFF_ALL();
        BR_BURN_R(5);
        Serial.println("Turn on channel 5!");
        delay(3000);
        BR_TURN_OFF_ALL();
        Serial.println("Turn off channel 5!");
        break;
      default:
        break;
    }
  }
}



