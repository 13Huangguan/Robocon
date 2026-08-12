#include "stm32f4xx_hal.h"
#include "key.h"
#include "Timer.h"

timer_struct key_timer_Delay;//前消抖
timer_struct key_timer_Delay_After;//后消抖
timer_struct key_timer_waitlongp;

int Key_get_state(void)
{
    static uint32_t key_state_count=0;//定义变量统计在while循环中经历的次数
    KEY_STATE key_state = KEY_STATE_IDLE;//初始化按键状态为空闲
    static KEY_PROC_STATE key_proc_state = KEY_PROC_IDLE;//初始化按键处理状态为空闲
    static uint8_t key_long_state=0;//初始化长按键状态为0
    switch(key_proc_state)//根据处理模式选择对应处理
    {
        case KEY_PROC_IDLE://空闲处理状态
        {
            if(HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==1)//检测到按键口电平为高
            {
                key_proc_state =KEY_PROC_CHECK;//处理模式转换为检查（消抖、噪声）
                timer_get_time(&key_timer_Delay, KEY_DELAY_TIME);//初始化非阻塞延时结构体
            }
        }break;
        case KEY_PROC_CHECK:
        {
            if(timer_inquery(&key_timer_Delay))//查询是否到期,到期就进if
            {
                if(HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==1)//消抖后电平是否仍给高
                {
                    key_proc_state=KEY_PROC_HOLDING;//处理模式转换为按住
                    key_state_count=0;
                    timer_get_time(&key_timer_waitlongp, KEY_WAIT_LONG_PRESS_TIME);//初始化等待长按结构体
                }
                else{key_proc_state=KEY_PROC_IDLE;}//消抖时间段后电平不为高，说明是噪声，处理重新变为空闲
            }
        }break;
        case KEY_PROC_HOLDING:
        {
            if(timer_inquery(&key_timer_waitlongp))//查询是否到期
            {
                key_state_count++;/*到期则按键状态统计数加一*/  //10ms加一
                timer_get_time(&key_timer_waitlongp, KEY_WAIT_LONG_PRESS_TIME);//初始化等待长按结构体
            }
            if(!key_long_state)//如果当前“触发过长按”标志位为0/之前未触发长按
            {
                if((key_state_count>=KEY_LONG_PRESS_counter))//如果判断长按用的计数大于长按阈值
                {
                    key_proc_state=KEY_PROC_RELEASE;//转入释放处理模式
                    key_state=KEY_STATE_LONGP;//输出按键状态为长按
                    key_state_count=0;//清零计数
                    key_long_state=1;//置“触发过长按”标志位为1
                    timer_get_time(&key_timer_Delay_After, KEY_DELAY_TIME);//初始化非阻塞延时结构体
                }
                else if(HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==0)//如果按键电平为0
                {
                    key_proc_state=KEY_PROC_RELEASE;//装入释放处理模式
                    timer_get_time(&key_timer_Delay_After, KEY_DELAY_TIME);//初始化非阻塞延时结构体
                }
                else if(HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==1)//电平为高，且计数时间未到阈值，继续在长按模式等
                {
                    key_proc_state=KEY_PROC_HOLDING;
                }
            }
            
        }break;
        case KEY_PROC_RELEASE:
        {
            if(timer_inquery(&key_timer_Delay_After))//查询是否到期,到期就进if
            {
                if((HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==1)&&(key_long_state==0))//如果按键电平为高，同时已触发长按标志位不为1，则说明是抖动噪声
                {key_proc_state=KEY_PROC_HOLDING;}//回到按住处理模式
                else if((HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==0)&&(key_long_state==0)&&(key_state_count>=KEY_SHORT_PRESS_counter))
                {//如果消抖后电平为低，未触发过长按，同时阈值大于短按阈值，返回按键状态为短按
                    key_state=KEY_STATE_SHORTP;
                    key_state_count=0;
                    key_proc_state=KEY_PROC_IDLE;//返回空闲模式
                    key_long_state=0;
                }
                else if((HAL_GPIO_ReadPin(KEY_GPIO_PORT,KEY_PIN)==0)&&(key_long_state==0)&&(key_state_count<KEY_SHORT_PRESS_counter))
                {//松开了但按住时间不足短按阈值（快速点按/噪声）：清空回IDLE，不触发
                    key_state_count=0;
                    key_long_state=0;
                    key_proc_state=KEY_PROC_IDLE;
                    timer_get_time(&key_timer_Delay_After, KEY_DELAY_TIME);
                }
                else if(key_long_state==1)
                {
                    key_long_state=0;
                    timer_get_time(&key_timer_Delay_After, KEY_DELAY_TIME);
                }
                
            }
            
        }break;
    }
    return key_state;  
}