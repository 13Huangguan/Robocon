#include "UART_IQRhandler.h"
#include "CAN_IQRhandler.h"
#include "can.h"
uint8_t TxData[5] = {0}; // 要发送的数据
uint8_t RxData[10];
float feedback;
uint8_t feedback_flag=0;
uint8_t buzzer_flag=0;
void CAN_Send_StdMsg(CAN_HandleTypeDef *hcan, uint16_t std_id, uint8_t *data, uint8_t len)
   {
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;              // 用于记录这次发送用掉了哪个邮箱
    TxHeader.StdId =std_id;
    TxHeader.ExtId =0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = len;
    TxHeader.TransmitGlobalTime = DISABLE;
    HAL_CAN_AddTxMessage(hcan, &TxHeader, data, &TxMailbox);
   }
void Data_update(void *argument)
{
  TickType_t last = xTaskGetTickCount();
    (void)argument;
    for(;;)
    {  
        if(rx_new_data_flag1==1)
        {  TxData[0]=0xA5;
           TxData[1]=startflag;
           TxData[2]=breathperiod>>8;
           TxData[3]=(uint8_t)breathperiod&0xFF;
           TxData[4]=0x5A;
           CAN_Send_StdMsg(&hcan1,0x001,TxData,5);
           rx_new_data_flag1= 0;
        }
        vTaskDelayUntil(&last, pdMS_TO_TICKS(100));
    }
}

CAN_RxHeaderTypeDef RxHeader;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN1)
    {
       
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            if (RxHeader.IDE == CAN_ID_STD)
            {
                if (RxHeader.StdId == 0x002)
                {
                    feedback=RxData[0];
                    feedback_flag=1;
                }
                if(RxHeader.StdId == 0x010)
                {
                    buzzer_flag=2*RxData[0];
                }
                
            }
        }
    }
}
