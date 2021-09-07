/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

TaskHandle_t xTaskHandler2= NULL;
TaskHandle_t xTaskHandler3= NULL;
TaskHandle_t xTaskHandler4= NULL;
/* USER CODE END Variables */
/* Definitions for xTaskHandler1 */
osThreadId_t xTaskHandler1Handle;
const osThreadAttr_t xTaskHandler1_attributes = {
  .name = "xTaskHandler1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vTask2_CmdHandling( void *argument);
void vTask3_CmdProcessing( void *argument);
void vTask4_UartWrite( void *argument);
/* USER CODE END FunctionPrototypes */

void vTask1_DisplayMenu(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
	asm volatile ("wfi");
}
/* USER CODE END 2 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{

}
/* USER CODE END 5 */

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
  /* creation of xTaskHandler1 */
  xTaskHandler1Handle = osThreadNew(vTask1_DisplayMenu, NULL, &xTaskHandler1_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate(vTask2_CmdHandling,   "Task-2", 128u, NULL, 24u, &xTaskHandler2);
  xTaskCreate(vTask3_CmdProcessing, "Task-3", 128u, NULL, 24u, &xTaskHandler3);
  xTaskCreate(vTask4_UartWrite,     "Task-4", 128u, NULL, 24u, &xTaskHandler4);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_vTask1_DisplayMenu */
/**
  * @brief  Function implementing the xTaskHandler01 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_vTask1_DisplayMenu */
void vTask1_DisplayMenu(void *argument)
{
  /* USER CODE BEGIN vTask1_DisplayMenu */
  /* Infinite loop */
  for(;;)
  {
    osDelay(pdMS_TO_TICKS(1000u));
  }
  /* USER CODE END vTask1_DisplayMenu */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */


void vTask2_CmdHandling( void *argument){
	while(1){
		osDelay(pdMS_TO_TICKS(1000u));
	}
}

void vTask3_CmdProcessing( void *argument){
	while(1){
		osDelay(pdMS_TO_TICKS(1000u));
	}
}

void vTask4_UartWrite( void *argument){
	while(1){
		osDelay(pdMS_TO_TICKS(1000u));
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
