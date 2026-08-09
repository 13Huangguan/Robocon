/**
 * @file    buzzer.c
 * @brief   蜂鸣器驱动实现文件。
 */
#include "buzzer.h"
#include "led.h"

// 蜂鸣器独立计时器，与led_timer互不冲突
timer buzzer_timer;

/* 初始化：蜂鸣器默认关闭 */
void buzzer_init(void)
{
    buzzer_off();
}

/* 蜂鸣器开启 PB0高电平 */
void buzzer_on(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

/* 蜂鸣器关闭 PB0低电平 */
void buzzer_off(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

// 节拍参数：{响时长, 停时长}
static const buzzer_cfg Buzzer_state[] =
{
    {200, 800},   // double_mode：响200ms 停800ms
    {50, 100}     // together_mode：响50ms 停100ms
};

void buzzer_confunction(void)
{
    // 静态变量，函数调用间保存状态
    static uint8_t flag = 0;
    LED_Mode new_state;

    // 根据全局signal匹配模式
    switch(signal)
    {
        case 0:  new_state = idle_mode;      break;
        case 1:  new_state = follow_mode;    break;
        case 2:  new_state = double_mode;     break;
        case 3:  new_state = together_mode;   break;
        default: new_state = idle_mode;       break;
    }

    // 模式发生切换：重置状态、初始化节拍
    if (new_state != cur_state)
    {
        cur_state = new_state;
        flag = 0;          // 复位标记，默认先鸣叫
        buzzer_off();

        // 依据模式启动首个计时
        switch (cur_state)
        {
            case double_mode:
                timer_start(&buzzer_timer, Buzzer_state[0].on_ms);
                buzzer_on();
                break;
            case together_mode:
                timer_start(&buzzer_timer, Buzzer_state[1].on_ms);
                buzzer_on();
                break;
            default:
                // 空闲、流水模式直接静音
                break;
        }
    }

    // 各模式运行逻辑
    switch(cur_state)
    {
        // 空闲：蜂鸣器关闭
        case idle_mode:
            buzzer_off();
            break;

        // 单灯流水：蜂鸣器静音
        case follow_mode:
            buzzer_off();
            break;

        // 双灯模式：200ms响 + 800ms停 循环
        case double_mode:
            if(timer_check(&buzzer_timer) == 0)
            {
                flag = !flag;
                if(flag == 0)
                {
                    buzzer_on();
                    timer_start(&buzzer_timer, Buzzer_state[0].on_ms);
                }
                else
                {
                    buzzer_off();
                    timer_start(&buzzer_timer, Buzzer_state[0].off_ms);
                }
            }
            break;

        // 全灯闪烁：短促滴滴 50ms响 + 100ms停
        case together_mode:
            if(timer_check(&buzzer_timer) == 0)
            {
                flag = !flag;
                if(flag == 0)
                {
                    buzzer_on();
                    timer_start(&buzzer_timer, Buzzer_state[1].on_ms);
                }
                else
                {
                    buzzer_off();
                    timer_start(&buzzer_timer, Buzzer_state[1].off_ms);
                }
            }
            break;

        default:
            cur_state = idle_mode;
            buzzer_off();
            break;
    }
}