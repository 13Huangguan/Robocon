#include "led.h"
#include "main.h"
MODE mode= breath_mode;
void LED_ON(uint8_t i)
{
    switch(i)
    {
        case 1:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);break;
        case 2:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);break;
        case 3:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);break;
        case 4:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);break;
    }
}
void LED_OFF(uint8_t i)
{
    switch(i)
    {
        case 1:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);break;
        case 2:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);break;
        case 3:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);break;
        case 4:HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);break;
    }
}
void ledflow()
{
  static uint8_t i=1;
 
    LED_OFF(i);
	HAL_Delay(50);
    i=(i%2)+1;
    LED_ON(i);
	HAL_Delay(50);
}

void ledbreath(TIM_HandleTypeDef *htim)
{   static uint8_t flag=1;
    static uint32_t count=0;
    if(htim->Instance==TIM3)
    {
      if(flag==1)
      {
        count++;
      }
      else
      {
        count--;
      }
      if(count>999)
      {
        flag=0;
      }
      else if(count==1)
      {
        flag=1;
      }
      __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1,count);
       __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,count);
    }
}
void LED_MODE1and2()
{
    if(mode==stop_mode)
    {
        LED_OFF(1);
        LED_OFF(2);
        
    }
    if(mode==flow_mode)
    {
        ledflow();
    }
	
}
