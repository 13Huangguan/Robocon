#include "stm32f4xx_hal.h"
#include "key.h"
#include "timer.h"
#include "EXTI_IQRhandler.h"
//内部私有状态
static uint8_t key_trig_flag = 0;
static uint32_t press_start_tick = 0;

//外部中断回调，放在stm32xx_it.c里调用，或者直接写进HAL_GPIO_EXTI_Callback
void Key_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY_PIN)
    {
        key_trig_flag = 1;
        press_start_tick = HAL_GetTick();
    }
}

//放在main while(1)循环里循环调用，返回按键事件
KeyEvent_t Key_Scan(void)
{
    KeyEvent_t event = KEY_EVENT_NONE;
    if(key_trig_flag == 1)
    {
        uint32_t now = HAL_GetTick();
        //消抖等待
        if((now - press_start_tick) >= DEBOUNCE_TICK)
        {
            //确认按键真实按下
            if(HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_RESET)
            {    buzzer_flag=1;
                //持续检测松手/长按
                while(1)
                {
                    now = HAL_GetTick();
                    //松手判定短按
                    if(HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_SET)
                    {
                        if((now - press_start_tick) < LONG_PRESS_TICK)
                        {
                            event = KEY_EVENT_SHORT;
                        }
                        break;
                    }
                    //按住超时判定长按
                    if((now - press_start_tick) >= LONG_PRESS_TICK)
                    {
                        event = KEY_EVENT_LONG;
                        //等待松手避免重复触发
                        while(HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_RESET);
                        break;
                    }
                }
            }
            key_trig_flag = 0;
        }
    }
    return event;
}