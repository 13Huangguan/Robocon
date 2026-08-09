/**
 * @file    led.c
 * @brief   LED 驱动实现文件。
 */
#include "led.h"

timer led_timer; 
LED_Mode cur_state=idle_mode;

static const uint8_t led_table[] =
{
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6
};
/* 点亮 LED1 */
static void led_on(uint8_t id)
{  if(IS_VALID_LED(id))
    HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_SET);
else 
{
    return;
}
}

/* 熄灭 LED1 */
static void led_off(uint8_t id)
{  if(IS_VALID_LED(id))
   HAL_GPIO_WritePin(LED_GPIO_PORT,led_table[id], GPIO_PIN_RESET);
   else 
   {
    return;
   }
}
void blink(led_config led)
{
  led_on(led.id);
  HAL_Delay(led.on_ms);
  led_off(led.id);
  HAL_Delay(led.off_ms);
}
void blink2(led_config* led1,int c)
{
    led_on((*(led1+c)).id);
    led_on((*(led1+1+c)).id);
    HAL_Delay((*(led1+c)).on_ms);
    led_off((*(led1+c)).id);
    led_off((*(led1+1+c)).id);
    HAL_Delay((*(led1+c)).off_ms);

}
void blink3(led_config* led1)
{
    led_on((*led1).id);
    led_on((*(led1+1)).id);
    led_on((*(led1+2)).id);
    led_on((*(led1+3)).id);
    HAL_Delay((*led1).on_ms);
    led_off((*led1).id);
    led_off((*(led1+1)).id);
    led_off((*(led1+2)).id);
    led_off((*(led1+3)).id);
    HAL_Delay((*led1).off_ms);
}


static void led_alloff()
{
   HAL_GPIO_WritePin(LED_GPIO_PORT,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_RESET); 
}
static void led_allon()
{
   HAL_GPIO_WritePin(LED_GPIO_PORT,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_SET); 
}


 void timer_start(timer* timer1,uint32_t periodtime)
{
   timer1->start_time=HAL_GetTick();
   timer1->period_time=periodtime;
   timer1->run_state=1;
}
 uint8_t timer_check(timer* timer1)
{
    uint32_t run_time=HAL_GetTick()-timer1->start_time;
    if(timer1->run_state==0)
    {
        return 0;
    }
    if(run_time>timer1->period_time)
    {
         timer1->run_state=0;
         return 0;
    }
    return 1; 
}
void state_machine()
{  static uint8_t flag=0;
   LED_Mode new_state;
   switch(signal)
   {
        case 0: new_state =idle_mode;    break;
        case 1: new_state =follow_mode;   break;
        case 2: new_state = double_mode;   break;
        case 3: new_state =  together_mode;   break;
        default: new_state = idle_mode;   break;
   }
   if (new_state != cur_state)
    {
        cur_state = new_state;
        led_step = 0;          
        timer_start(&led_timer,500); 
    }
   switch(cur_state)
    {
        case idle_mode:
            led_alloff();
            break;

        case follow_mode: 
            if(timer_check(&led_timer)==0)
            {
                led_alloff();
                led_on(led_step);
                led_step = (led_step + 1) % 4;
                timer_start(&led_timer,500); 
            }
            break;

        case double_mode: 
            if(timer_check(&led_timer)==0)
            {
                
                led_alloff();
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN << led_step, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_GPIO_PORT, (LED1_PIN << (led_step+1)), GPIO_PIN_SET);
                led_step = (led_step+1)%4;
                timer_start(&led_timer,500);
            }
            break;

        case together_mode:
            if(timer_check(&led_timer)==0)
            {  if(flag==1)
                led_allon();
                else
                {
                    led_alloff();
                }
                flag=(flag+1)%2;
                timer_start(&led_timer,500);
            }
            break;

        default:
            cur_state =idle_mode ;
            led_alloff();
            break;
    }

}
