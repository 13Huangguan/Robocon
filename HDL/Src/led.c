#include "led.h"
#include "main.h"
#include "timer.h"

MODE mode=stop_mode;

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
  static uint16_t count=0;
  static uint16_t led_step=1;
  if(count>500)
  {
    LED_OFF(led_step);
    led_step=led_step%2+1;
    LED_ON(led_step);
    count=0;
  }
  count++;

}

void ledbreath(TIM_HandleTypeDef *htim)
{  
     static uint8_t flag=1;
    static uint32_t count=0;
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
