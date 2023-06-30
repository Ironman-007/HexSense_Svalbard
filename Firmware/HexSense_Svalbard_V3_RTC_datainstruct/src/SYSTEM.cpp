#include <Arduino.h>
#include <math.h>

#include "SYSTEM.h"
#include "SDCARD.h"
#include "IMU.h"
#include "BR.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

static int i = 0;

static float orien_accx = 0.0;
static float orien_accy = 0.0;
static volatile float orien_accz = 0.0;

volatile bool burn_resistor_check = false;

float Body_Orientation = 0.0; // in degrees

// define pins to use
#define PINS2USE_CNT 5

#define FIRST_BURN_L  4000
#define SECOND_BURN_L 6000
#define STANDING_UP_TRESHOLD 9

// When SD card is powered off, it will mess up the SPI lines.
int     PINS2USE[PINS2USE_CNT]            = {PIN_LED1, WDI_PIN, PIN_BUTTON1, SD_EN_PIN, LED_indicator};
uint8_t PINS2USE_MODE[PINS2USE_CNT]       = {OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT};
uint8_t PINS2USE_INIT_VALUE[PINS2USE_CNT] = {LOW, LOW, LOW, HIGH, LOW};

void Serial_Setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);
}

void Pins_init(void) {
  for (i = 0; i < PINS2USE_CNT; i++) {
    pinMode(PINS2USE[i], PINS2USE_MODE[i]);
    if (PINS2USE_MODE[i]) digitalWrite(PINS2USE[i], PINS2USE_INIT_VALUE[i]);
  }
}

void Flash_LED(int LED_pin, int T_periode, int PWM_width, int times) {
  for (i = 0; i < times; i++) {
    digitalWrite(LED_pin, HIGH);
    delay(PWM_width);
    digitalWrite(LED_pin, LOW);
    delay(T_periode - PWM_width);
  }
}

void Flash_LED_once(int LED_pin, int length) {
  digitalWrite(LED_pin, HIGH);
  delay(length);
  digitalWrite(LED_pin, LOW);
}

void WD_setup(int wdi_pin) {
  analogWrite(wdi_pin, 128);
}

void WDI_output(int wdi_pin) {
  digitalToggle(wdi_pin);
}

// DEBUG_info templates
void DEBUG_info(const char * info) {
  Serial.println(F(info));
}

void DEBUG_info(const char * info, int data) {
  Serial.print(F(info));
  Serial.println(data);
}

void DEBUG_info(const char * info, uint32_t data) {
  Serial.print(F(info));
  Serial.println(data);
}

void DEBUG_info(const char * info, float data) {
  Serial.print(F(info));
  Serial.println(data);
}

uint32_t VBUS_connected(void) {
  return NRF_POWER->USBREGSTATUS;
}

void calculate_orientation(void) {
  IMU_wake();
  Get_IMU_data();

  orien_accx = accx;
  orien_accy = accy;
  orien_accz = accz;

  if (orien_accz < 9) {
    burn_resistor_check = true;
    if (DEBUG_OUTPUT) {
      Serial.println("burn_resistor_check = true");
    }
  }
  else {
    if (DEBUG_OUTPUT) {
      Serial.println("burn_resistor_check = false");
    }
    burn_resistor_check = false;
  }
  // IMU_sleep();

  Body_Orientation = atan2(accy, accx)*180/MATHPI;

  // Negative angle plus 2pi
  if (Body_Orientation < 0) Body_Orientation += 360;

  if (DEBUG_OUTPUT) {
    Serial.print("accz = ");
    Serial.println(accz);
    Serial.print("accy = ");
    Serial.println(accy);
    Serial.print("accx = ");
    Serial.println(accx);
    Serial.print("Body_Orientation = ");
    Serial.println(Body_Orientation);
  }
}

static float get_Z_orientation() {
  IMU_wake();
  Get_IMU_data();
  orien_accz = accz;
  IMU_sleep();

  return orien_accz;
}

static void try2burn_R(uint8_t CH_num, int first_try, int second_try) {
  digitalWrite(LED_indicator, HIGH);
  BR_TURN_OFF_ALL();
  BR_BURN_R(CH_num);
  delay(first_try);
  BR_TURN_OFF_ALL();

  if (DEBUG_OUTPUT) {
    Serial.print("AccZ = ");
    Serial.println(get_Z_orientation());
  }

  // 2s for the node to ba stable before checking if the second burn is necessary
  delay(2000);

  // check the orientation
  // if didn't stand up, reburn
  if (get_Z_orientation() < STANDING_UP_TRESHOLD) {
    if (DEBUG_OUTPUT) {
      Serial.println("Try to burn again");
    }
    BR_BURN_R(CH_num);
    delay(second_try);
    BR_TURN_OFF_ALL();
  }

 digitalWrite(LED_indicator, LOW);
}

void Burn_resistor(float orientation) {
  // if (DEBUG_OUTPUT) {
  //   Serial.print("get_Z_orientation() = ");
  //   Serial.println(get_Z_orientation());
  // }

  // Burn resistor only when the node is lying on the ground;
  // This needs to be changed for future missions;
  // For Svalbard, the node will be turned off/on multiple times so should not
  // reburn the resistor when turned back on.
  if (burn_resistor_check) {
    if (DEBUG_OUTPUT) {
      Serial.println("Start burning resistor");
      delay(3000);
    }
    // Side 5 on the ground, burn side 2, CH #1
    if (Body_Orientation >= 0  && Body_Orientation < 60) {
      try2burn_R(1, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
        Serial.println("Side 5 on the ground, burn side 2, CH #1");
      }
    }
    // Side 6 on the ground, burn side 3, CH #0
    else if (Body_Orientation >= 60  && Body_Orientation < 120) {
      try2burn_R(0, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
        Serial.println("Side 6 on the ground, burn side 3, CH #0");
      }
    }
    // Side 1 on the ground, burn side 4, CH #5
    else if (Body_Orientation >= 120 && Body_Orientation < 180) {
      try2burn_R(5, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
          Serial.println("Side 1 on the ground, burn side 4, CH #5");
        }
    }
    // Side 2 on the ground, burn side 5, CH #4
    else if (Body_Orientation >= 180 && Body_Orientation < 240) {
      try2burn_R(4, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
          Serial.println("Side 2 on the ground, burn side 5, CH #4");
        }
    }
    // Side 3 on the ground, burn side 6, CH #3
    else if (Body_Orientation >= 240 && Body_Orientation < 300) {
      try2burn_R(3, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
          Serial.println("Side 3 on the ground, burn side 6, CH #3");
        }
    }
    // Side 4 on the ground, burn side 1, CH #2
    else if (Body_Orientation >= 300 && Body_Orientation <= 360) {
      try2burn_R(2, FIRST_BURN_L, SECOND_BURN_L);
      if (DEBUG_OUTPUT) {
          Serial.println("Side 4 on the ground, burn side 1, CH #2");
        }
    }
  }
}

// #ifdef __cplusplus
// }
// #endif

