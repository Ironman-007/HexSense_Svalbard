#pragma once

#include <Arduino.h>

#define LFCLK_START_TASK (1UL)
#define LFCLK_STOP_TASK  (1UL)

extern bool RTC_flag;

extern void rtc_handler(void);
extern void lfclk_config(void);
extern void rtc_config(void);

extern void rtc_init(void);

extern uint32_t RTC_COMPARE_triggered(void);
extern void RTC_Clear(void);
