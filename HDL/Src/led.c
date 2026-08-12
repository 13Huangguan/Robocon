#include "stm32f4xx_hal.h"
#include "led.h"
#include "timer.h"
#include "main.h"


void led_on(uint8_t led_num)
{
    switch (led_num)
    {
        case 1:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED4_PIN, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}

void led_off(uint8_t led_num)
{
    switch (led_num)
    {
        case 1:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_PIN, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED4_PIN, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

static timer_struct flow_timer;
static uint8_t flow_led_on = 1; 

void flowing_led_init(void)//流水灯初始化
{
    led_on(1);led_off(2);
    flow_led_on = 1;
    timer_get_time(&flow_timer, led_flow_period);
}

void flowing_led(void)//流水灯函数
{
    if (timer_inquery(&flow_timer))
    {
        if (flow_led_on)
        {
            led_off(1);led_on(2);
        }
        else
        {
            led_on(1);led_off(2);
        }
        flow_led_on = !flow_led_on;
        timer_get_time(&flow_timer, led_flow_period);
    }
}


timer_struct breathing_timer;
static uint32_t bright_time = 0;//每段时间片内led亮的时间
static BREATH_STATE breath_state = BREATH_READY_ON;

void breathing_led_init(void)//呼吸灯初始化
{
    led_off(3);
    led_off(4);
    bright_time = 0;
    breath_state = BREATH_READY_ON;
    timer_get_time(&breathing_timer, led_breathing_delay);
}

void breathing_led(void)//这一段逻辑跟按键的差不多，只是多了个READY_ON模式前判断是否灭完灯的if
{
    switch(breath_state)
    {
        case BREATH_READY_ON:
        {
            if(timer_inquery(&breathing_timer))
            {
                breath_state=BREATH_ON;
                led_on(3);led_on(4);
                timer_get_time(&breathing_timer,bright_time);
            }
        }break;     
        case BREATH_ON:
        {
            if(timer_inquery(&breathing_timer))
            {
                led_off(3);led_off(4);
                breath_state=BREATH_READY_ON;
                bright_time++;
                timer_get_time(&breathing_timer,led_breathing_delay-bright_time);
            }
            if(bright_time==20)
            {
                breath_state=BREATH_READY_OFF;
            }
        }break;
        case BREATH_READY_OFF:
        {
            if(timer_inquery(&breathing_timer))
            {
                breath_state=BREATH_OFF;
                led_on(3);led_on(4);
                timer_get_time(&breathing_timer,bright_time);
            }
        }break;
        case BREATH_OFF:
        {
            if(timer_inquery(&breathing_timer))
            {
                led_off(3);led_off(4);
                breath_state=BREATH_READY_OFF;
                bright_time--;
                timer_get_time(&breathing_timer,led_breathing_delay-bright_time);
            }
            if(bright_time==0)
            {
                breath_state=BREATH_READY_ON;
            }
        }break;
    }
}