#include <Arduino.h>

#include "IMU.h"
#include "SYSTEM.h"

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
float magx  = 0.0;
float magy  = 0.0;
float magz  = 0.0;

float _orientation  = 0.0;

Adafruit_MPU6050 mpu;

void IMU_sleep(void) {
  mpu.enableSleep(true);
}

void IMU_wake(void) {
  mpu.enableSleep(false);
}

void IMU_start(void) {
  mpu.setGyroStandby(false, false, false);
  mpu.setAccelerometerStandby(false, false, false);
}

void IMU_standby(void) {
  mpu.setGyroStandby(true, true, true);
  mpu.setAccelerometerStandby(true, true, true);
  // mpu.setTemperatureStandby(true);
}

void IMU_init(void) {
  mpu.begin();

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  IMU_sleep();
}

void Get_IMU_data(void) {
  sensors_event_t a, g, temp;
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
