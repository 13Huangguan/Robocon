#include "buzzer.h"
#include "CAN_IQRhandler.h"
void BEEP_ON()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
}
void BEEP_OFF()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
}
void Beep(void *argument)
{
 TickType_t last = xTaskGetTickCount();
    (void)argument;
    for(;;)
    {
        uint8_t flag_snap;
        // 临界区快照，只复制，不在临界区内做业务
        __disable_irq();
        flag_snap = buzzer_flag;
        __enable_irq();

        if(flag_snap > 0)
        {
            if(flag_snap % 2 == 0)
            {
                BEEP_ON();
            }
            else
            {
                BEEP_OFF();
            }
            // 真正自减，要再次保护
            __disable_irq();
            if(buzzer_flag > 0)
            {
                buzzer_flag --;
            }
            __enable_irq();
        }
        vTaskDelayUntil(&last, pdMS_TO_TICKS(100));
    }
}
