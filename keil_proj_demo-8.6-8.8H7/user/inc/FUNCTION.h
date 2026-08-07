#ifndef __FUNCTION_H
#define __FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"

#define LED_COUNT 4



void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms);
void beep(uint32_t beep_ms);
void alarm_sys_func(int mode);

#ifdef __cplusplus
}
#endif

#endif /* __FUNCTION_H */

