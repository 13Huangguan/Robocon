#include "state.h"
#include "main.h"
 MODE state=STATE_RUN;

static void state_idle()
{
	led_off(LED1_PIN |LED2_PIN| LED3_PIN|LED4_PIN);
}
static void state_run()
{
	led_on(LED1_PIN);
	HAL_Delay(500);
	led_off(LED1_PIN);
		HAL_Delay(500);
	led_on(LED2_PIN);
	HAL_Delay(500);
	led_off(LED2_PIN);
		HAL_Delay(500);led_on(LED3_PIN);
	HAL_Delay(500);
	led_off(LED3_PIN);
		HAL_Delay(500);led_on(LED4_PIN);
	HAL_Delay(500);
	led_off(LED4_PIN);
		HAL_Delay(500);
}
static void state_alarm()
{
	led_on(LED1_PIN |LED2_PIN| LED3_PIN|LED4_PIN);
	HAL_Delay(50);
	led_off(LED1_PIN |LED2_PIN| LED3_PIN|LED4_PIN);
	HAL_Delay(50);
}
static const state_func state_table[] = {
    [STATE_IDLE]    = state_idle,
    [STATE_RUN] = state_run,
    [STATE_ALARM]   = state_alarm,
    [STATE_COUNT]   = NULL            // из╠Ь
};
void led_run()
{
   	if(state<STATE_COUNT&&state_table[state]!=NULL)
	{
		state_table[state]();
	}
}
	