#ifndef __UART_H
#define __UART_H
#include "main.h"
#include "usart.h"
 extern uint8_t beep_trigger;
 extern uint8_t tx_buffer[20];
void UART_Start_Receive();
void Uart_Dma_Send(uint8_t *dat,uint16_t len);
#endif