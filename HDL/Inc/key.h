#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx_hal.h"  //根据你的芯片自行修改f1/f0等

//参数配置
#define KEY_PIN        GPIO_PIN_3
#define KEY_PORT       GPIOA
#define DEBOUNCE_TICK  20U    //消抖20ms
#define LONG_PRESS_TICK 800U  //长按阈值800ms

//按键事件类型
typedef enum
{
    KEY_EVENT_NONE = 0,
    KEY_EVENT_SHORT,  //短按
    KEY_EVENT_LONG    //长按
}KeyEvent_t;

//对外接口
void Key_EXTI_Callback(uint16_t GPIO_Pin);
KeyEvent_t Key_Scan(void);

#endif