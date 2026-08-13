#include "EXTI_IQRhandler.h"
#include "main.h"
#include "led.h"
#include "buzzer.h"
#include "key.h"
uint32_t keyTick=0;
uint8_t key_flag=0;
uint8_t buzzer_flag=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   
   Key_EXTI_Callback(GPIO_Pin);
	
}