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
#include "semphr.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
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
/* for the task */
TaskHandle_t xTaskHandler2= NULL;
/* for the mutex */
SemaphoreHandle_t xMutex_uart= NULL;
/* USER CODE END Variables */
/* Definitions for xTask1 */
osThreadId_t xTask1Handle;
const osThreadAttr_t xTask1_attributes = {
  .name = "xTask1",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void vTaskHandler1(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   while(1);
}
/* USER CODE END 2 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
  while(1);
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
	xMutex_uart= xSemaphoreCreateMutex();
	if( xMutex_uart != pdFAIL ){
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
		/* creation of xTask1 */
		xTask1Handle = osThreadNew(vTaskHandler1, "Task 1--------------------", &xTask1_attributes);

		/* USER CODE BEGIN RTOS_THREADS */
		/* add threads, ... */
		xTaskCreate(vTaskHandler1,"Task_2", 128u, "Task 2====================", osPriorityBelowNormal6, &xTaskHandler2);
		/* USER CODE END RTOS_THREADS */

		/* USER CODE BEGIN RTOS_EVENTS */
		/* add events, ... */
	}
		/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_vTaskHandler1 */
/**
  * @brief  Function implementing the xTask1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_vTaskHandler1 */
void vTaskHandler1(void *argument)
{
  /* USER CODE BEGIN vTaskHandler1 */
	char cUart_data[33u];
  /* Infinite loop */
  for(;;)
  {
	  if( pdFAIL != xSemaphoreTake(xMutex_uart, portMAX_DELAY) ){
			sprintf(cUart_data, "%s\n", (char*)argument);
			HAL_UART_Transmit(&huart2, (uint8_t*)cUart_data, strlen(cUart_data), 100u);
			xSemaphoreGive(xMutex_uart);
		}
		osDelay(pdMS_TO_TICKS(1000u));
  }
  /* USER CODE END vTaskHandler1 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
