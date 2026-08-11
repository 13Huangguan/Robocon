#include "key.h"
#include "led.h"
uint8_t flag1 = 0; // 判断电平
uint8_t flag2 = 0; // beep标识
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint32_t last_int_tick = 0;  // 上一次中断时间戳
    static uint32_t press_tick = 0;     // 按键按下时刻
    uint32_t now_tick = HAL_GetTick();

    if (GPIO_Pin != INPUT_Pin)
        return;

    // ========== 消抖核心：间隔太短 = 抖动，直接退出 ==========
    if(now_tick - last_int_tick < KEY_DEBOUNCE_MS)
    {
        last_int_tick = now_tick;
        return;
    }
    last_int_tick = now_tick; // 更新有效中断时间

    // 读取当前按键电平
    GPIO_PinState key_level = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);

    if(key_level == GPIO_PIN_SET) // 上升沿：按键按下
    {
        press_tick = now_tick;  // 记录按下时间
        flag1 = 1;
    }
    else // 下降沿：按键松开
    {
        if(flag1 == 1) // 确认是正常按下后松开
        {
            uint32_t press_dur = now_tick - press_tick;
            if(press_dur > KEY_LONG_MS)
            {
                mode = breath_mode; // 长按
            }
            else
            {
                mode = flow_mode;   // 短按
            }
            flag2 = 1;  // 通知主循环按键事件完成
            flag1 = 0;
            press_tick = 0;
        }
    }
}
