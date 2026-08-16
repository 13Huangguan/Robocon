/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LEDTASK */
osThreadId_t LEDTASKHandle;
const osThreadAttr_t LEDTASK_attributes = {
  .name = "LEDTASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UARTTask */
osThreadId_t UARTTaskHandle;
const osThreadAttr_t UARTTask_attributes = {
  .name = "UARTTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for FLOATTASK */
osThreadId_t FLOATTASKHandle;
const osThreadAttr_t FLOATTASK_attributes = {
  .name = "FLOATTASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for BEERTASK */
osThreadId_t BEERTASKHandle;
const osThreadAttr_t BEERTASK_attributes = {
  .name = "BEERTASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for NoiseTASK */
osThreadId_t NoiseTASKHandle;
const osThreadAttr_t NoiseTASK_attributes = {
  .name = "NoiseTASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Breath_LED(void *argument);
void Data_update(void *argument);
void Receivefloat(void *argument);
void Beep(void *argument);
void Noise(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of LEDTASK */
  LEDTASKHandle = osThreadNew(Breath_LED, NULL, &LEDTASK_attributes);

  /* creation of UARTTask */
  UARTTaskHandle = osThreadNew(Data_update, NULL, &UARTTask_attributes);

  /* creation of FLOATTASK */
  FLOATTASKHandle = osThreadNew(Receivefloat, NULL, &FLOATTASK_attributes);

  /* creation of BEERTASK */
  BEERTASKHandle = osThreadNew(Beep, NULL, &BEERTASK_attributes);

  /* creation of NoiseTASK */
  NoiseTASKHandle = osThreadNew(Noise, NULL, &NoiseTASK_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Breath_LED */
/**
* @brief Function implementing the LEDTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Breath_LED */
__weak void Breath_LED(void *argument)
{
  /* USER CODE BEGIN Breath_LED */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Breath_LED */
}

/* USER CODE BEGIN Header_Data_update */
/**
* @brief Function implementing the UARTTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Data_update */
__weak void Data_update(void *argument)
{
  /* USER CODE BEGIN Data_update */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Data_update */
}

/* USER CODE BEGIN Header_Receivefloat */
/**
* @brief Function implementing the FLOATTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Receivefloat */
__weak void Receivefloat(void *argument)
{
  /* USER CODE BEGIN Receivefloat */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Receivefloat */
}

/* USER CODE BEGIN Header_Beep */
/**
* @brief Function implementing the BEERTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Beep */
__weak void Beep(void *argument)
{
  /* USER CODE BEGIN Beep */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Beep */
}

/* USER CODE BEGIN Header_Noise */
/**
* @brief Function implementing the NoiseTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Noise */
__weak void Noise(void *argument)
{
  /* USER CODE BEGIN Noise */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Noise */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

