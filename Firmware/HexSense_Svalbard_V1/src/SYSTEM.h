#pragma once

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

extern uint32_t Time_stamp;

extern void Serial_Setup(void);

extern void Pins_init(void);
extern void Flash_LED(int LED_pin, int T_periode, int PWM_width, int times);
extern void Flash_LED_once(int LED_pin, int length);

extern void DEBUG_info(char * info);

#ifdef __cplusplus
}
#endif
