#include "CAN_IQRhandler.h"
#include "can.h"
#include "led.h"

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
uint8_t TxData0[8] = {'O', 'K'}; // 要发送的数据
uint8_t TxData1[8] = {'O', 'K'}; // 要发送的数据

volatile uint8_t run_flag = 0;
volatile uint8_t buzzer_count = 0;
volatile uint8_t led_flag = 0;
volatile uint8_t led_single_flag = 0;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance == CAN1)
    {
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {    if(RxHeader.StdId == 0x201)
            {
                buzzer_count=1;
            }
            if (RxHeader.ExtId == 0x01020101)
            { // led_flag=0;
                if (RxHeader.IDE == CAN_ID_EXT)
                {
                    buzzer_count = RxData[0];
                    run_flag = 1;
                }
            }
            else if (RxHeader.ExtId == 0x01020201)
            { // run_flag=0;
                if (RxHeader.IDE == CAN_ID_EXT)
                {
                    led_single_flag = 1;
                    if (RxData[0] == 1)
                    {
                        led_flag = 1;
                        TxData1[2] = '1';
                    }
                    else
                    {
                        led_flag = 0;
                        TxData1[2] = '0';
                    }
                }
            }
        }
    }
}
void CAN_Send_ExtMsg(CAN_HandleTypeDef *hcan, uint32_t ext_id, uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;              // 用于记录这次发送用掉了哪个邮箱
    TxHeader.StdId = 0;
    TxHeader.ExtId = ext_id;
    TxHeader.IDE = CAN_ID_EXT;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = len;
    TxHeader.TransmitGlobalTime = DISABLE;

    // 等待邮箱空闲，防止丢包
    while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0)
    {
    }
    HAL_CAN_AddTxMessage(hcan, &TxHeader, data, &TxMailbox);
}