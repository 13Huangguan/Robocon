#ifndef __LED_H
#define __LED_H
#include "main.h"
#include "gpio.h"


void ledflow();
void ledbreath(TIM_HandleTypeDef *htim,uint16_t total_period_ms);
void LED_ON(uint8_t i);
void LED_OFF(uint8_t i);
typedef enum
{
    stop_mode=0,
    flow_mode,
    breath_mode

}MODE;

extern MODE mode;


#endif