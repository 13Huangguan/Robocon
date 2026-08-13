#include "UART_IQRHandler.h"
#include "stdio.h"
uint8_t rx_buffer[100]={0};
uint8_t tx_buffer[20]={0};
uint8_t beep_trigger=0;
uint8_t tx_busy=0;
void UART_Start_Receive()
{
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1,rx_buffer,sizeof(rx_buffer));
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if(huart->Instance==USART1)
  {
    if(rx_buffer[0]==0xff)
    {
        for(uint8_t i=0;i<Size;i++)
        {
            if(rx_buffer[i]==1)
            {
                 beep_trigger=1;
            }
        }
    }
  }
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1,rx_buffer,sizeof(rx_buffer));
}
void Uart_Dma_Send(uint8_t *dat,uint16_t len)
{
   if(tx_busy==0&&len>0)
   {
    memcpy(tx_buffer,dat,len);
    tx_busy=1;
    HAL_UART_Transmit_DMA(&huart1,tx_buffer,len);
   }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART1)
  {
    tx_busy=0;
  }
}