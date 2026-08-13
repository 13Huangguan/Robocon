#ifndef __CANN_H
#define __CANN_H
#include "EXTI_IQRhandler.h"
extern volatile uint8_t buzzer_count;
extern volatile uint8_t run_flag;
extern volatile uint8_t led_flag;
extern volatile uint8_t led_single_flag;
extern uint8_t TxData0[8];
extern uint8_t TxData1[8];
void CAN_Send_ExtMsg(CAN_HandleTypeDef *hcan, uint32_t ext_id, uint8_t *data, uint8_t len);
#endif