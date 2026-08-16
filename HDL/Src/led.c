#include "led.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "UART_IQRhandler.h"
#include "tim.h"

MODE mode = stop_mode;


void LED_ON(uint8_t i)
{
  switch (i)
  {
  case 1:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    break;
  case 4:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    break;
  }
}
void LED_OFF(uint8_t i)
{
  switch (i)
  {
  case 1:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET );
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    break;
  case 4:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    break;
  }
}
void ledflow()
{
  static uint16_t count = 0;
  static uint16_t led_step = 1;
  if (count > 500)
  {
    LED_OFF(led_step);
    led_step = led_step % 2 + 1;
    LED_ON(led_step);
    count = 0;
  }
  count++;
}

void ledbreath(TIM_HandleTypeDef *htim,uint16_t total_period_ms)
{
  static int16_t count = 0;
    static int16_t step = 1;

    // 只更新步进幅度，保留方向符号
    int16_t step_mag = (2000 * 10) / total_period_ms;
    if(step_mag < 1) step_mag = 1;
    if(step < 0) step = -step_mag;
    else step = step_mag;

    count += step;

    if(count >= 999)
    {
        count = 999;
        step = -step;
    }
    else if(count <= 0)
    {
        count = 0;
        step = -step;
    }

    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, count);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, count);
}

void Breath_LED(void *argument)
{
  TickType_t last = xTaskGetTickCount();
    (void)argument;
    for(;;)
    {   
        if (startflag)
        {   
            ledbreath(&htim3,breathperiod);
        }
        else
        {
            // 关闭呼吸直接灭灯
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		}
        // ✅固定100ms刷新亮度，永远不变
		vTaskDelayUntil(&last, pdMS_TO_TICKS(10));
	}
        
    
}