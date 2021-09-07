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
#include "timers.h"
#include "string.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_ON 								1
#define LED_OFF 							2
#define LED_TOOGLE 						3
#define LED_TOGGLE_OFF			  4
#define READ_LED_STATUS 			5
#define RTC_PRINT_DATETIME 		6
#define EXIT_APP							0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* Struct queue */
typedef struct{
	uint8_t COMMAND_NUM;
	uint8_t COMMAND_ARGS[10];
}APP_CMD_t;


/* Task handler */
TaskHandle_t xTaskHandler2= NULL;
TaskHandle_t xTaskHandler3= NULL;
TaskHandle_t xTaskHandler4= NULL;

/* Queue handler */
QueueHandle_t xCommand_queue= NULL;
QueueHandle_t xUart_write_queue= NULL;

/* timer object */
TimerHandle_t xLed_timer= NULL;

/* Buffer for uart2 */
volatile char 		c_buffer_receive;
volatile char 		c_command_buffer[20u];
volatile uint8_t 	u8Command_len= 0;

/* Menu display */

const char menu[]={"\
	\n\n\nLED_ON              --------> 1\
			\nLED_OFF             --------> 2\
			\nLED_TOOGLE          --------> 3\
			\nLED_TOGGLE_OFF      --------> 4\
			\nREAD_LED_STATUS     --------> 5\
			\nRTC_PRINT_DATETIME  --------> 6\
			\nEXIT_APP            --------> 0\
			\nType your option here:  "
};



/* USER CODE END Variables */
/* Definitions for Task_1 */
osThreadId_t Task_1Handle;
const osThreadAttr_t Task_1_attributes = {
  .name = "Task_1",
  .priority = (osPriority_t) osPriorityBelowNormal6,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vTask2_CmdHandling( void *arg );
void vTask3_CmdProcessing( void *arg );
void vTask4_CmdWrite( void *arg );

void vGetArguments( uint8_t *arg);

/* helper func */
void vTurn_led_on( void );
void vTurn_led_off( void );
void vLed_toggle( uint32_t u32Time_set );
void vLed_toggle_start( TimerHandle_t xTimer );
void vDelay( uint32_t u32Time_ms);
void vLed_toggle_off( void );
//void vState_led( void );
void vState_led( char *pData );
void vReport_error( char *pData );
void vReport_errors( void );
/* USER CODE END FunctionPrototypes */

void vTask1_DisplayMenu(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   //__asm volatile("wfi");
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
	//HAL_UART_Transmit(&huart2, (uint8_t *)menu, strlen(menu), 60u );
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&c_buffer_receive, 1u );
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
	xCommand_queue		= xQueueCreate(10u, sizeof(APP_CMD_t*)); // the queue consume about 40bytes
	xUart_write_queue	= xQueueCreate(10u, sizeof(char*));   // the queue consume about 40bytes
	if( (NULL != xCommand_queue)  && ( NULL != xUart_write_queue )  ){
		__disable_irq();
		HAL_UART_Transmit(&huart2, (uint8_t *)"\nQueue successful\n", 20u, 30u );
		__enable_irq();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_1 */
  Task_1Handle = osThreadNew(vTask1_DisplayMenu, NULL, &Task_1_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xTaskCreate(vTask2_CmdHandling, 	"Task2", 128u, NULL, osPriorityNormal, &xTaskHandler2);
	xTaskCreate(vTask3_CmdProcessing, "Task3", 128u, NULL, osPriorityNormal, &xTaskHandler3);
	xTaskCreate(vTask4_CmdWrite, 			"Task4", 128u, NULL, osPriorityNormal, &xTaskHandler4);
	}
	else{
		HAL_UART_Transmit(&huart2, (uint8_t *)"Queue failse\n", 8u, 30u );
		while(1){
		}
	}
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_vTask1_DisplayMenu */
/**
  * @brief  Function implementing the Task_1 thread.
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
		//HAL_UART_Transmit(&huart2, (uint8_t *)"Task 1\n", 8u, 30u );
    //osDelay(pdMS_TO_TICKS(1000u));
		char *pData = (char *)menu;
		xQueueSendToFront( xUart_write_queue, &pData, portMAX_DELAY);
		/* wait for .... */
		xTaskNotifyWait( 0u, 0u, NULL, portMAX_DELAY );
		
  }
  /* USER CODE END vTask1_DisplayMenu */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vTask2_CmdHandling( void *arg ){
	while(1){
		//HAL_UART_Transmit(&huart2, (uint8_t *)"Task 2\n", 8u, 30u );
		//osDelay(pdMS_TO_TICKS(1000u));
		
		/* local variables */
		uint8_t u8Command_code= 0u;
		APP_CMD_t *pNew_cmd;
		
		/* wait for receive notify */
		xTaskNotifyWait( 0u, 0u, NULL, portMAX_DELAY );
		/* get command */
		pNew_cmd= (APP_CMD_t*)pvPortMalloc(sizeof(APP_CMD_t));
		/* turn off interrupts to avoid race condition */
		taskENTER_CRITICAL();
		u8Command_code= (c_command_buffer[0] - 48u);
		pNew_cmd->COMMAND_NUM= u8Command_code;
		vGetArguments( pNew_cmd->COMMAND_ARGS );
		taskEXIT_CRITICAL();
		/* add into queue_command */
		xQueueSendToFront(xCommand_queue, &pNew_cmd, portMAX_DELAY)  ;
	}
}

void vTask3_CmdProcessing( void *arg ){
	while(1){
		APP_CMD_t *pCmd;
		char pData[50];
		/* Read command from the queue */
		xQueueReceive( xCommand_queue, (void *)&pCmd, portMAX_DELAY );
		/* handling command */
		if( pCmd->COMMAND_NUM == LED_ON ){
			vTurn_led_on();
		}			
		else if( pCmd->COMMAND_NUM == LED_OFF ){
			vTurn_led_off();
		}
		else if( pCmd->COMMAND_NUM == LED_TOOGLE ){
			vLed_toggle(pdMS_TO_TICKS(500u));
		}
		else if( pCmd->COMMAND_NUM == LED_TOGGLE_OFF ){
			vLed_toggle_off();
		}
		else if( pCmd->COMMAND_NUM == READ_LED_STATUS ){
			vState_led(pData);
		}
		else if( pCmd->COMMAND_NUM == RTC_PRINT_DATETIME){
			
		}
		else if( pCmd->COMMAND_NUM == EXIT_APP){
			
		}
		else{
			vReport_error(pData);
		}
	}
}

void vTask4_CmdWrite( void *arg ){
	while(1){
		//HAL_UART_Transmit(&huart2, (uint8_t *)"Task 4\n", 8u, 30u );
		//osDelay(pdMS_TO_TICKS(1000u));
		char *pData= NULL;
		xQueueReceive(xUart_write_queue, &pData, portMAX_DELAY );
		HAL_UART_Transmit( &huart2, (uint8_t*)pData, strlen(pData), 100u);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* get receive uart interrupts again */
	if( huart == &huart2){
		BaseType_t pxHigherPriorityTaskWoken= pdFALSE;
		c_command_buffer[u8Command_len]= c_buffer_receive;
		if( c_command_buffer[u8Command_len] == 'e' ){
			/* user end of the entry data */
			u8Command_len= 0u;
			/* send notify to cmd handling task */
			xTaskNotifyFromISR(xTaskHandler2, NULL, eNoAction, &pxHigherPriorityTaskWoken);
			xTaskNotifyFromISR(Task_1Handle, NULL, eNoAction, &pxHigherPriorityTaskWoken);
		}
		else{
			u8Command_len++;
		}
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&c_buffer_receive, 1u );
		if( pxHigherPriorityTaskWoken == pdTRUE ){
			taskYIELD();
		}
	}
}



void vGetArguments( uint8_t *arg){

}



void vTurn_led_on( void ){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void vTurn_led_off( void ){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void vLed_toggle( uint32_t u32Time_set ){
	/* create soft timer */
	if( NULL == xLed_timer ){
		xLed_timer= xTimerCreate("Led_timer", u32Time_set, pdTRUE, NULL, vLed_toggle_start);
	}
	/* start soft timer */
	xTimerStart(xLed_timer, portMAX_DELAY);
}

void vLed_toggle_start( TimerHandle_t xTimer ){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void vLed_toggle_off( void ){
		xTimerStop(xLed_timer, portMAX_DELAY);
}


void vDelay( uint32_t u32Time_ms){
	uint32_t u32Tick_set, u32Current_tick;
	/* convert ms to tick */
	u32Tick_set= pdMS_TO_TICKS(u32Time_ms);
	u32Current_tick= xTaskGetTickCount();
	/* block loop while */
	while( xTaskGetTickCount() < ( u32Current_tick + u32Tick_set ));
}

void vState_led( char *pData ){
	//char *pDatas;
	sprintf(pData, "\nThe State Led: %d\n", (uint8_t)HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_13));
	xQueueSendToFront(xUart_write_queue, &pData, portMAX_DELAY);
}

void vReport_error( char *pData ){
	//char *pData;
	sprintf(pData, "\nINVALID VALUE\n");
	xQueueSendToFront(xUart_write_queue, &pData, portMAX_DELAY);
}

void vReport_errors( void ){
	char *pData;
	sprintf(pData, "\nINVALID VALUE with the command is not true then you can see more information in my git\n");
	xQueueSendToFront(xUart_write_queue, &pData, portMAX_DELAY);
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
