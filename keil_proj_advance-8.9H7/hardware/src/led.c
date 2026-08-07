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
static void led_on(uint8_t id)
{  if(IS_VALID_LED(id))
    HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_SET);
else 
{
    return;
}
}

/* 熄灭 LED1 */
static void led_off(uint8_t id)
{  if(IS_VALID_LED(id))
   HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_RESET);
   else 
   {
    return;
   }
}
void blink(led_config led)
{
  led_on(led.id);
  HAL_Delay(led.on_ms);
  led_off(led.id);
  HAL_Delay(led.off_ms);
}
void blink2(led_config* led1,int c)
{
    led_on((*(led1+c)).id);
    led_on((*(led1+1+c)).id);
    HAL_Delay((*(led1+c)).on_ms);
    led_off((*(led1+c)).id);
    led_off((*(led1+1+c)).id);
    HAL_Delay((*(led1+c)).off_ms);

}
void blink3(led_config* led1)
{
    led_on((*led1).id);
    led_on((*(led1+1)).id);
    led_on((*(led1+2)).id);
    led_on((*(led1+3)).id);
    HAL_Delay((*led1).on_ms);
    led_off((*led1).id);
    led_off((*(led1+1)).id);
    led_off((*(led1+2)).id);
    led_off((*(led1+3)).id);
    HAL_Delay((*led1).off_ms);

}
