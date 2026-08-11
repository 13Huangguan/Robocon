#ifndef __KEY_H
#define __KEY_H
#include "main.h"
#include "gpio.h"
void MODE_CHANGE();


extern uint8_t flag1, flag2, mode;

#define KEY_DEBOUNCE_MS  20    // 按键消抖时间 20ms
#define KEY_LONG_MS      1000  // 长按阈值1s

#endif
