/**
 * @file    buzzer.c
 * @brief   蜂鸣器驱动实现文件。
 *          非阻塞短鸣：buzzer_beep() 立即响并启动计时，
 *          buzzer_task() 由主循环周期调用，计时到期自动关。
 */
#include "beep.h"
#include "Timer.h"

static timer_struct buzzer_timer;
static uint8_t buzzer_active = 0;


void buzzer_init(void)
{
    buzzer_off();
    buzzer_active = 0;
}

/* 打开蜂鸣器：把 PA8 输出高电平 */
void buzzer_on(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

/* 关闭蜂鸣器：把 PA8 输出低电平 */
void buzzer_off(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

/* 开始一次短鸣：立即响，由 buzzer_task() 在 beep_ms 后自动关 */
void buzzer_beep(uint32_t beep_ms)
{
    buzzer_on();
    buzzer_active = 1;
    timer_get_time(&buzzer_timer, beep_ms);
}

/* 主循环周期调用：短鸣计时到期后自动关闭蜂鸣器 */
void buzzer_task(void)
{
    if (buzzer_active && timer_inquery(&buzzer_timer))
    {
        buzzer_off();
        buzzer_active = 0;
    }
}