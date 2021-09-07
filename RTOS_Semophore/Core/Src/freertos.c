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
#include "queue.h"
#include "semphr.h"
#include "stdlib.h"
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

/* state func */
BaseType_t xStatus= pdFAIL;

/* Task object */
TaskHandle_t xTask2Handler= NULL;
TaskHandle_t xTask3Handler= NULL;

/* Queue object */
QueueHandle_t xQueueUart= NULL;

/* Semaphore object */
SemaphoreHandle_t xSempUart= NULL;


/* USER CODE END Variables */
/* Definitions for xTask_1 */
osThreadId_t xTask_1Handle;
const osThreadAttr_t xTask_1_attributes = {
  .name = "xTask_1",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vTask2HandlerSemaphore( void *arg );
void vTask3HandlerSemaphore( void *arg );
void vDelay( uint32_t u32Time_ms);
/* USER CODE END FunctionPrototypes */

void vTaskHandler1(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
	while(1){
	
	}
}
/* USER CODE END 2 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
   while(1){
	 
	 }
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	HAL_UART_Transmit(&huart2, (uint8_t*)"\nStart program\n", 18u, 100u);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	vSemaphoreCreateBinary( xSempUart );
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	xQueueUart= xQueueCreate(1u, sizeof(unsigned int));
	
	/* check queue and semaphore create successful */
	if( (xQueueUart != NULL) && ( xSempUart != NULL ) ){
		
	
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of xTask_1 */
  xTask_1Handle = osThreadNew(vTaskHandler1, NULL, &xTask_1_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xStatus= xTaskCreate(vTask2HandlerSemaphore, "Task_2", 128u, NULL, /*osPriorityBelowNormal6*/osPriorityNormal, &xTask2Handler);
	xStatus= xTaskCreate(vTask3HandlerSemaphore, "Task_3", 128u, NULL, /*osPriorityBelowNormal6*/osPriorityNormal, &xTask3Handler);
	if( xStatus != pdPASS ){
		while(1){
			/* handling for failing */
		}
	}
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
	}
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_vTaskHandler1 */
/**
  * @brief  Function implementing the xTask_1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_vTaskHandler1 */
void vTaskHandler1(void *argument)
{
  /* USER CODE BEGIN vTaskHandler1 */
  /* Infinite loop */
	unsigned int u8Rand_number;
  //xSemaphoreGive( xSempUart );

  for(;;){
		/* create a random number */
    u8Rand_number= 50u;
		/* send to queue */
		if( xQueueSendToFront( xQueueUart, &u8Rand_number, portMAX_DELAY ) != pdPASS){
			/* func fail */
			while(1u);
		}
		else{
			/* func successful */
			xSemaphoreGive(xSempUart);
			//xSemaphoreTake( xSempUart, ( TickType_t ) 0);
			/* context switching */
			taskYIELD();
		}
  }
  /* USER CODE END vTaskHandler1 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vTask2HandlerSemaphore( void *arg ){
	unsigned int u8Uart_data= 56u;
	while(1){
		/* take semaphore first */
		/* ( TickType_t ) 0u: means when the semaphore is not available the task will wait for 0 tick. */
		if( xSemaphoreTake( xSempUart, ( TickType_t ) 0u) != pdPASS ){
			HAL_UART_Transmit(&huart2, (uint8_t*)"Wait\n", 6u,100u);
			vDelay(pdMS_TO_TICKS(1000u));
		}
		else{
		  if( xQueueReceive( xQueueUart,  &u8Uart_data, 0u) != pdFAIL ){
				HAL_UART_Transmit(&huart2, (uint8_t*)&u8Uart_data, 1u,100u);
				xSemaphoreGive( xSempUart );
				vDelay(pdMS_TO_TICKS(1000u));
				taskYIELD();
			}
		}
	}
}

void vTask3HandlerSemaphore( void *arg ){
	unsigned int u8Uart_data= 56u;
	while(1){
		/* take semaphore first */
		/* ( TickType_t ) 0u: means when the semaphore is not available the task will wait for 0 tick. */
		if( xSemaphoreTake( xSempUart, ( TickType_t ) 0u) != pdPASS ){
			HAL_UART_Transmit(&huart2, (uint8_t*)"Wait in Task 3\n", 16u,100u);
			vDelay(pdMS_TO_TICKS(1000u));
		}
		else{
		  if( xQueueReceive( xQueueUart,  &u8Uart_data, 0u) != pdFAIL ){
				HAL_UART_Transmit(&huart2, (uint8_t*)"Here in Task 3\n", 16u,100u);
				xSemaphoreGive( xSempUart );
				vDelay(pdMS_TO_TICKS(1000u));
				taskYIELD();
			}
		}
	}
}

void vDelay( uint32_t u32Time_ms){
	uint32_t u32Tick_set, u32Current_tick;
	/* convert ms to tick */
	u32Tick_set= pdMS_TO_TICKS(u32Time_ms);
	u32Current_tick= xTaskGetTickCount();
	/* block loop while */
	while( xTaskGetTickCount() < ( u32Current_tick + u32Tick_set ));
}


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
