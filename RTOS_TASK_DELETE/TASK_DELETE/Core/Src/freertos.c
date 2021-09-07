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
#include "usart.h"
#include <string.h>
#include <stdio.h>
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
TaskHandle_t xLed1Handler = NULL;
TaskHandle_t xLed2Handler = NULL;

volatile uint8_t u8Flag= 0u;

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
void vLed1Handler( void *argument);
void vLed2Handler( void *argument);
static void prvDelay( uint32_t u32TimeMs);
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
  xTaskCreate(vLed1Handler, "LED-1", 256u, NULL, 20u, &xLed1Handler);
  xTaskCreate(vLed2Handler, "LED-2", 256u, NULL, 10u, &xLed2Handler);
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
    vTaskDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vLed1Handler( void *argument ){
	UBaseType_t xLed1TaskPriority, xLed2TaskPriority;
	uint8_t msg[100];

	while(1){
		/* get priority value of each task  */
		xLed1TaskPriority = uxTaskPriorityGet(xLed1Handler);
		xLed2TaskPriority = uxTaskPriorityGet(xLed2Handler);
		sprintf((char*)msg, "The priority of Task 1 and Task 2: %d - %d \n", (int)xLed1TaskPriority, (int)xLed2TaskPriority);
		HAL_UART_Transmit(&huart2, msg, strlen((char*)msg), 30u);
		HAL_UART_Transmit(&huart2, (uint8_t*)"Task 1 handle\n", 15u, 30u);
		prvDelay(1000u);
		vTaskDelay(1000);
		if(0U == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) ){
			vTaskDelete(NULL);
		}
		if( u8Flag == 1u ){
			/* clear flag */
			__disable_irq();
			u8Flag = 0u;
			/* set priority of eack task */
			vTaskPrioritySet(xLed2Handler, xLed1TaskPriority);
			vTaskPrioritySet(xLed1Handler, xLed2TaskPriority);
			__enable_irq();
		}
	}
}

void vLed2Handler( void *argument ){
	UBaseType_t xLed1TaskPriority, xLed2TaskPriority;
	uint8_t msg[100];
	while(1){
		/* get priority value of each task  */
		xLed1TaskPriority = uxTaskPriorityGet(xLed1Handler);
		xLed2TaskPriority = uxTaskPriorityGet(xLed2Handler);
		sprintf((char*)msg, "The priority of Task 1 and Task 2: %d - %d \n", (int)xLed1TaskPriority, (int)xLed2TaskPriority);
		HAL_UART_Transmit(&huart2, msg, strlen((char*)msg), 30u);
		HAL_UART_Transmit(&huart2, (uint8_t*)"Task 2 handle\n", 15u, 30u);
		prvDelay(1000u);

		if( u8Flag == 1u ){
			__disable_irq();
			/* clear flag */
			u8Flag = 0u;
			/* set priority of eack task */
			vTaskPrioritySet(xLed1Handler, xLed2TaskPriority);
			vTaskPrioritySet(xLed2Handler, xLed1TaskPriority);
			__enable_irq();
		}
	}
}


static void prvDelay( uint32_t u32TimeMs){
	uint32_t u32TickSet, u32TickCurrent;
	/* convert ms to tick */
	u32TickSet= u32TimeMs/1000*configTICK_RATE_HZ;
	u32TickCurrent= xTaskGetTickCount();
	/* block delay */
	while( xTaskGetTickCount() < (u32TickCurrent + u32TickSet));
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  if( GPIO_Pin == GPIO_PIN_7 ){
	  u8Flag= 1u;
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
