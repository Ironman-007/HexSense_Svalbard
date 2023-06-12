#include <Arduino.h>

#include "IMU.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

float accx  = 0.0;
float accy  = 0.0;
float accz  = 0.0;
float gyrox = 0.0;
float gyroy = 0.0;
float gyroz = 0.0;

float _orientation  = 0.0;

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

void IMU_init(void) {
  mpu.begin();

  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	// Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);
}

void Get_IMU_data(void) {
  mpu.getEvent(&a, &g, &temp);

  accx  = a.acceleration.x;
  accy  = a.acceleration.y;
  accz  = a.acceleration.z;
  gyrox = g.gyro.x;
  gyroy = g.gyro.y;
  gyroz = g.gyro.z;
}

void Get_Orientation(void) {
  Get_IMU_data();
  _orientation = 0;
}

// #ifdef __cplusplus
// }
// #endif
