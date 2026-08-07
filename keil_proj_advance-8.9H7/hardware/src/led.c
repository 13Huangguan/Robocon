/**
 * @file    led.c
 * @brief   LED 驱动实现文件。
 */
#include "led.h"
static const uint8_t led_table[] =
{
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6
};
/* 点亮 LED1 */
void led_on(uint8_t id)
{  if(IS_VALID_LED(id))
    HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_SET);
else 
{
    return;
}
}

/* 熄灭 LED1 */
void led_off(uint8_t id)
{  if(IS_VALID_LED(id))
   HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_RESET);
   else 
   {
    return;
   }
}