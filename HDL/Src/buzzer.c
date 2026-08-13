#include "buzzer.h"
#include "key.h"
void BEEP_ON()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
}
void BEEP_OFF()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
}
void beep()
{ 
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();
    
}