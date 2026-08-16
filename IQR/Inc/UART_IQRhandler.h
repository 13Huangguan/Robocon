#ifndef __UART_H
#define __UART_H
#include "main.h"
#include "usart.h"
extern uint8_t tx_buffer[10];
extern uint8_t startflag;
extern uint16_t breathperiod;
extern uint8_t rx_new_data_flag;
extern uint8_t rx_new_data_flag1;
extern uint8_t tx_busy;
void UART_Start_Receive();
void Uart_Dma_Send(uint8_t *dat,uint16_t len);
#endif
