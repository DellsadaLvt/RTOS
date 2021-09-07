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
#include "queue.h"
#include "string.h"
#include "stdio.h"
#include "gpio.h"
#include "timers.h"
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
/* use for uart receive */
volatile unsigned char g_u8Uart_receive= NULL;
/* using for task */
/* using for queue */
QueueHandle_t xQueue_uart_receive= NULL;
QueueHandle_t xQueue_uart_transmit= NULL;

/* using for display mode */
const unsigned char menu[]={"\
\n\nTURN_LED_ON        -------------> 1\
	\nTURN_LED_OFF       -------------> 2\
	\nTOGGLE_ON          -------------> 3\
	\nTOGGLE_OFF         -------------> 4\
	\nSTATE_LED          -------------> 5\
	\nPlease select mode here: "
};

/* using for soft timer */
TimerHandle_t xSoftTimer;
/* USER CODE END Variables */
/* Definitions for Task1 */
osThreadId_t Task1Handle;
const osThreadAttr_t Task1_attributes = {
  .name = "Task1",
  .priority = (osPriority_t) osPriorityBelowNormal6,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vGetCommand( void *arg );
void vControlLed( uint8_t u8Mode, char *strTemp  );
void vTimerCallBack( TimerHandle_t xTimer );
void vSendCommand( void *arg );
/* USER CODE END FunctionPrototypes */

void Task1Display(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
	// use for get the sleep mode
	__asm volatile( "wfi" );
}
/* USER CODE END 2 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
	taskDISABLE_INTERRUPTS();
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	HAL_UART_Receive_IT(&huart2, (uint8_t*)&g_u8Uart_receive, 1u);
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
	xQueue_uart_receive= xQueueCreate (1u, sizeof(unsigned char)); 					// consumed 1byte
	xQueue_uart_transmit= xQueueCreate(1u, sizeof(unsigned char * ));       // consumed 4bytes
	if( (NULL == xQueue_uart_receive) || (NULL == xQueue_uart_transmit)) 
		taskDISABLE_INTERRUPTS();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task1 */
  Task1Handle = osThreadNew(Task1Display, NULL, &Task1_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xTaskCreate(vGetCommand, "Task_2", 128u, NULL, osPriorityNormal, NULL  );
	xTaskCreate(vSendCommand,"Task_2", 128u, NULL, osPriorityNormal, NULL  );
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task1Display */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task1Display */
void Task1Display(void *argument)
{
  /* USER CODE BEGIN Task1Display */
	char *pData= (char *)menu;
  /* Infinite loop */
  for(;;)
  {
		/* wait until receive notify from the isr  */
		xTaskNotifyWait(0u, 0u, NULL, portMAX_DELAY);
		/* send the mode menu data to the queue */
		xQueueSend(xQueue_uart_transmit, &pData, portMAX_DELAY);
	}
  /* USER CODE END Task1Display */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vGetCommand( void *arg ){
	/* local variables */
	uint8_t u8Buffer= NULL;
	char strMsg[20u];
	while(1){
		/* get the data from queue */
		xQueueReceive(xQueue_uart_receive, &u8Buffer, portMAX_DELAY);
		/* control led */
		vControlLed( (u8Buffer-48u),  strMsg);
	}
}

void vControlLed( uint8_t u8Mode, char *strTemp ){
	/* test ==> it no effect */
//	char strMsg[30u];
//	char *pData;
	/* init a temp */
	if( 1u == u8Mode ){
		/* 1: turn on led 13 */
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	else if( 2u == u8Mode ){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else if( 3u == u8Mode ){
		if( NULL == xSoftTimer ){
			/* create a soft timer to get the toggle func */
				xSoftTimer= xTimerCreate("SoftTimer", pdMS_TO_TICKS(1000u), pdTRUE, NULL, &vTimerCallBack);
			}
		/* Start timer */
		xTimerStart(xSoftTimer, portMAX_DELAY);
	}
	else if( 4u == u8Mode ){
		/* STOP soft timer  */
		xTimerStop( xSoftTimer, portMAX_DELAY );
	}
	else if( 5u == u8Mode ){
		/* read state of pin */
		sprintf(strTemp, "\n---The state of led: %d---\n", HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
		xQueueSend(xQueue_uart_transmit, &strTemp, portMAX_DELAY);
	}
	else{
		/* send message invalid value */
		sprintf(strTemp,"\n-----INVALID VALUE-----\n");
		xQueueSend(xQueue_uart_transmit, &strTemp, portMAX_DELAY);
	}
}

/* timer call back func */
void vTimerCallBack( TimerHandle_t xTimer ){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}


void vSendCommand( void *arg ){
	/* initial a buffer */
	char *pData= NULL;
	while(1){
		/* receive the data of the queue */
		xQueueReceive(xQueue_uart_transmit, &pData, portMAX_DELAY);
		/* send data throught uart */
		HAL_UART_Transmit(&huart2, (uint8_t*)pData, strlen(pData), 100u);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
	if( huart == &huart2 ){
		/* varibles */
		uint8_t u8Buffer= NULL;
		BaseType_t pxHigherPriorityTaskWoken= pdFAIL;
		/* Get data */
		u8Buffer= g_u8Uart_receive;
		/* send data to the queue */
		xQueueSendToFrontFromISR( xQueue_uart_receive, &u8Buffer, &pxHigherPriorityTaskWoken);
		/* notify to the menu task */
		xTaskNotifyFromISR(Task1Handle, 0u, eNoAction, &pxHigherPriorityTaskWoken);
		/* enable receive uart interrupts again */
		HAL_UART_Receive_IT(&huart2, (uint8_t*)&g_u8Uart_receive, 1u);
		/* manual contex switching */
		if( pdPASS == pxHigherPriorityTaskWoken ){
			/* manual contex switching */
			taskYIELD();
		}
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
