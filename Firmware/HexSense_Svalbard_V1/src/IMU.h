#pragma once

#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

extern Adafruit_MPU6050 mpu;

extern void IMU_init(void);
extern void Get_IMU_data(void);
extern void Get_Orientation(void);
extern void IMU_standby(void);
extern void IMU_start(void);
extern void IMU_sleep(void);
extern void IMU_wake(void);

extern float accx;
extern float accy;
extern float accz;
extern float gyrox;
extern float gyroy;
extern float gyroz;

extern float _orientation;

// #ifdef __cplusplus
// }
// #endif