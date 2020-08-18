/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "si4463.h"
#include "delay_dwt.h"
#include "stdio.h"
#include "string.h"
#include "adc.h"
#include "lan.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

RNG_HandleTypeDef hrng;
si4463_t si4463;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

void udp_packet(eth_frame_t *frame, uint16_t len)
{
	uint8_t dataUDP[len];
	memset(dataUDP, 0x00, len);
    ip_packet_t *ip = (void*)(frame->data);
    udp_packet_t *udp = (void*)(ip->data);

    if(udp->to_port == htons(8077))
    {
    	 if(len)
    	 {
    		memcpy(dataUDP,udp->data, len);
    		flagModemCmd = cmdTxHop;
    		if(flagModemCmd != cmdTxHop)
    		{
    		//	SI4463_Transmit(&si4463, (uint8_t)HAL_RNG_GetRandomNumber(&hrng)%10, (uint8_t*)&dataUDP,60);
    		}
    		else
    		{
    			SI4463_Transmit(&si4463, 0x00, (uint8_t*)(&dataUDP),sizeof(dataUDP));
    		}
    	 }

    }
}

uint32_t udp_receive(void *data, uint16_t len)
{
	data_t *d = data;
	uint32_t temp;
	if(len >= sizeof(data_t))
	{
		temp = d->one;
		return temp;
	}

	return 0;
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t outgoingBuffer[RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH];

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId Task_UdpTxHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Task_UdpTx */
  osThreadDef(Task_UdpTx, StartTask02, osPriorityNormal, 0, 128);
  Task_UdpTxHandle = osThreadCreate(osThread(Task_UdpTx), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);

    HAL_GPIO_WritePin(LED_TX_GPIO_Port,LED_TX_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_RX_GPIO_Port,LED_RX_Pin,GPIO_PIN_RESET);

    lan_poll();
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Task_UdpTx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {

	  outgoingBuffer[0] = 'h';
	  outgoingBuffer[1] = 'e';
	  outgoingBuffer[2] = 'l';
	  outgoingBuffer[3] = 'o';
	  outgoingBuffer[4] = 'o';
	  outgoingBuffer[5] = ' ';
	  outgoingBuffer[6] = 'p';
	  outgoingBuffer[7] = 'e';
	  outgoingBuffer[8] = 'o';
	  outgoingBuffer[9] = 'p';
	  outgoingBuffer[10] = 'l';
	  outgoingBuffer[11] = 'e';
	  outgoingBuffer[12] = ' ';
	  outgoingBuffer[13] = 'p';
	  outgoingBuffer[14] = 'r';
	  outgoingBuffer[15] = 'u';
	  outgoingBuffer[16] = 'v';
	  outgoingBuffer[17] = 'i';
	  outgoingBuffer[18] = 't';
	  outgoingBuffer[19] = ' ';
	  outgoingBuffer[20] = 'U';
	  outgoingBuffer[21] = 'K';
	  outgoingBuffer[22] = 'R';
	  outgoingBuffer[23] = 'A';
	  outgoingBuffer[24] = 'I';
	  outgoingBuffer[25] = 'N';
	  outgoingBuffer[26] = 'E';
	  outgoingBuffer[27] = ' ';
	  outgoingBuffer[28] = 'L';
	  outgoingBuffer[29] = 'O';
	  outgoingBuffer[31] = 'L';

	  outgoingBuffer[32] = '1';
	  outgoingBuffer[33] = '2';
	  outgoingBuffer[34] = '3';
	  outgoingBuffer[35] = '4';
	  outgoingBuffer[36] = '5';
	  outgoingBuffer[37] = '6';
	  outgoingBuffer[38] = '7';
	  outgoingBuffer[39] = '8';
	  outgoingBuffer[40] = '9';
	  outgoingBuffer[41] = '10';
	  outgoingBuffer[42] = '11';
	  outgoingBuffer[43] = '12';
	  outgoingBuffer[44] = '13';
	  outgoingBuffer[45] = '14';
	  outgoingBuffer[46] = '15';
	  outgoingBuffer[47] = '16';
	  outgoingBuffer[48] = '17';
	  outgoingBuffer[49] = '18';
	  outgoingBuffer[50] = '19';
	  outgoingBuffer[51] = '20';
	  outgoingBuffer[52] = '21';
	  outgoingBuffer[53] = '22';
	  outgoingBuffer[54] = '23';
	  outgoingBuffer[55] = '24';
	  outgoingBuffer[56] = '25';
	  outgoingBuffer[57] = '26';
	  outgoingBuffer[58] = '27';
	  outgoingBuffer[59] = '28';
	  outgoingBuffer[60] = '29';
	  outgoingBuffer[61] = 'O';
	  outgoingBuffer[62] = 'L';
	  outgoingBuffer[63] = ' ';

	  //SI4463_Transmit(&si4463, 0x00, (uint8_t*)outgoingBuffer, 64);

	  Check_CMD();
	  osDelay(100);
  }
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
