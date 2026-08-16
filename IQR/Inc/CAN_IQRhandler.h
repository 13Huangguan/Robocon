#ifndef __CANN_H
#define __CANN_H


#include "UART_IQRhandler.h"
#include "main.h"
#include "stm32f4xx_hal.h"
void CAN_Send_StdMsg(CAN_HandleTypeDef *hcan, uint16_t std_id, uint8_t *data, uint8_t len);
extern float feedback;
extern uint8_t feedback_flag;
extern uint8_t buzzer_flag;
#endif
