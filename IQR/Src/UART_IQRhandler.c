#include "UART_IQRHandler.h"
#include "stdio.h"
#include "string.h"
#include "CAN_IQRhandler.h"
#include "buzzer.h"
uint8_t rx_buffer[5] = {0};
uint8_t tx_buffer[10] = {0};
uint8_t vofa_tail[4] = {0x00, 0x00, 0x80, 0x7f};
uint8_t startflag = 0;
uint16_t breathperiod = 0;
uint8_t rx_new_data_flag = 0;
uint8_t rx_new_data_flag1 = 0;
uint8_t tx_busy = 0;

void UART_Start_Receive()
{
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART1)
  {
    if (Size == 5) // 必须判断长度！
    {
      if (rx_buffer[0] == 0xA5 && rx_buffer[4] == 0x5A)
      {
        startflag = rx_buffer[1];
        breathperiod = ((uint16_t)rx_buffer[2] << 8) | rx_buffer[3];
        rx_new_data_flag = 1;
        rx_new_data_flag1 = 1; // 收到合法帧，打标记
      }
    }
  }
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
}
void Uart_Dma_Send(uint8_t *dat, uint16_t len)
{
  if (tx_busy == 0 && len > 0)
  {
    memcpy(tx_buffer, dat, len);
    tx_busy = 1;
    HAL_UART_Transmit_DMA(&huart1, tx_buffer, len);
  }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    tx_busy = 0;
  }
}
void Receivefloat(void *argument)
{
  TickType_t last = xTaskGetTickCount();
  (void)argument;
  uint8_t fb_snap;
  (void)argument;
  for (;;)
  {
    fb_snap = 0;
    // 临界区：同时快照+清标志，保证数据配对
    __disable_irq();
    if (feedback_flag == 1)
    {
      fb_snap = feedback;
      feedback_flag = 0;
    }
    __enable_irq();

    if (fb_snap != 0)
    {

      memcpy(&tx_buffer[0], &feedback, 4);
      memcpy(&tx_buffer[4], vofa_tail, 4);
      Uart_Dma_Send(tx_buffer, 8);
    }
    vTaskDelayUntil(&last, pdMS_TO_TICKS(10));
  }
}
