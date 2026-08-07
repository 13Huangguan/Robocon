/**
 * @file    led.h
 * @brief   LED 驱动头文件。
 *          头文件放声明和宏，具体实现放在 led.c。
 */
#ifndef LED_H
#define LED_H

#include "stm32h7xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif

/* 宏定义：给 LED 使用的端口和引脚起名字 */
#define LED_GPIO_PORT GPIOB
#define LED1_PIN      GPIO_PIN_3
#define LED2_PIN      GPIO_PIN_4
#define LED3_PIN      GPIO_PIN_5
#define LED4_PIN      GPIO_PIN_6

#define IS_VALID_LED(id) ((id) < 4&&(id)>=0)//题目1增加

/* 种子工程先提供无参数版本，只操作 LED1；题目 1 将其扩展为带编号参数版本 */

typedef struct
{
    uint8_t id;
    int on_ms;
    int off_ms; 
}led_config;
void blink(led_config led);
#ifdef __cplusplus
}
#endif

#endif /* LED_H */
