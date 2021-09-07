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
#include "usart.h"
#include <stdio.h>
#include <string.h>

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
TaskHandle_t LedTask= NULL;
TaskHandle_t BtnTask= NULL;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void LedTaskHandler( void *argument);
void BtnTaskHandler( void *argument);
void rtosDelay( uint32_t u32DelayMs );
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

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

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate( LedTaskHandler, "LED-Task", 300u, NULL, (osPriority_t) osPriorityNormal, &LedTask);
  xTaskCreate( BtnTaskHandler, "Btn-Task", 300u, NULL,  (osPriority_t) osPriorityNormal, &BtnTask);
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
    osDelay(1000u);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void LedTaskHandler( void *argument){
	char message[30];
	uint32_t u32Count= 0;
	while(1){
		/* confirm receive notify */
		if( pdTRUE == xTaskNotifyWait(0, 0, &u32Count, portMAX_DELAY) ){
			sprintf(message, "The count is: %ld\n",u32Count);
			HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 10u);
		}
	}
}

void BtnTaskHandler( void *argument){
	while(1){
		if( 0u == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ){
			rtosDelay(200u);
			if( 0u == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ){
				rtosDelay(200u);
				xTaskNotify(LedTask, 0u, eIncrement);
				xTaskNotify(LedTask, 6u, eSetValueWithoutOverwrite);
				while( 0u == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) );
			}
		}
	}
}

void rtosDelay( uint32_t u32DelayMs ){
	/* convert second to tick */
	uint32_t u32CurrentTick = xTaskGetTickCount();
	uint32_t u32TickSet= u32DelayMs /1000 * configTICK_RATE_HZ;

	/* start to delay block */
	while( xTaskGetTickCount() < (u32CurrentTick + u32TickSet) );
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
