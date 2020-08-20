/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "rng.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
#include "stdio.h"

#include "si4463.h"
#include "enc28j60.h"
#include "lan.h"
#include "delay_dwt.h"
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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* si4463 */
uint8_t incomingBuffer[RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH];
uint8_t outgoingBuffer[RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH];

int16_t curr_rssi = 0x00;
uint8_t check_module_flag = 0;

uint16_t length_packet = 0;

float c_temp = 0.0, v_bat = 0.0;

/* enc28j60 */
uint8_t send_buf[512];
uint8_t send_buf2[512];

uint16_t ADC_Val[2] = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  DWT_Init();

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_RNG_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */

  /* Assign functions */
  si4463.IsClearToSend = SI4463_IsCTS;
  si4463.WriteRead = SI4463_WriteRead;
  si4463.SPIRead = SI4463_SPIRead;
  si4463.SPITransmit = SI4463_SPITransmit;
  si4463.Select = SI4463_Select;
  si4463.Deselect = SI4463_Deselect;
  si4463.SetShutdown = SI4463_SetShutdown;
  si4463.ClearShutdown = SI4463_ClearShutdown;
  si4463.DelayMs = DWT_Delay_ms;
  si4463.DelayUs = DWT_Delay_us;

  /* Disable interrupt pin for init Si4463 */
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);

  /* Check Device */
  SI4463_CheckModule();
  /* Init Si4463 with structure */
  SI4463_Init(&si4463);
  //SI4463_IrCal_Manual(&si4463, 1, 2);
  SI4463_SetTxPower(&si4463,PaPwr100mW);
  /* Clear RX FIFO before starting RX packets */
  SI4463_ClearRxFifo(&si4463);
  /* Start RX mode */
  SI4463_StartRx(&si4463, 0, false, false, false);
  /* Clear interrupts after enabling interrupt pin.
   * Without it may be situation when interrupt is asserted but pin not cleared.*/
  SI4463_ClearInterrupts(&si4463);
  /* Enable interrupt pin and */
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
  /* Initialize LAN */
  lan_init();

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init(); 
  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  if(GPIO_Pin== GPIO_PIN_1)
  {

	  /* Clear incoming buffer */
	  memset(incomingBuffer, 0x00, RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH);

	  /* Get interrupts and work with it */
	  SI4463_GetInterrupts(&si4463);

	  /* Handling PH interrupts */
	  if (si4463.interrupts.filterMatch)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.filterMatch = false;
	  }
	  if (si4463.interrupts.filterMiss)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.filterMiss = false;
	  }
	  if (si4463.interrupts.packetSent)
	  {
		  /* Handling this interrupt here */
		  /* Clear TX FIFO */
		  SI4463_ClearTxFifo(&si4463);

		  /* Re-arm StartRX */
		  SI4463_StartRx(&si4463, 0, false, false,false);

		  /*Toggle led for indication*/
		  HAL_GPIO_WritePin(LED_TX_GPIO_Port,LED_TX_Pin,GPIO_PIN_SET);

		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.packetSent = false;
	  }
	  if (si4463.interrupts.packetRx)
	  {
		 /* Handling this interrupt here */
		 /* Get FIFO data */
		 SI4463_ReadRxFifo(&si4463, incomingBuffer, RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH);

		 length_packet = SI4463_GetPacketInfo(&si4463,PKT_FIELD_2_LENGTH,63,0);
		 //SI4463_Get_PH_Status(&si4463, NOTHING);
		 send_to_udp(incomingBuffer,RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH,IP_ADDR_DEST);
		 /* Clear RX FIFO */
		 SI4463_ClearRxFifo(&si4463);
		 /* Start RX again.
		 * It need because after successful receive a packet the chip change
		 * state to READY.
		 * There is re-armed mode for StartRx but it not correctly working */
		 SI4463_StartRx(&si4463, 0, false, false, false);

		 HAL_GPIO_WritePin(LED_RX_GPIO_Port, LED_RX_Pin,GPIO_PIN_SET);

		 si4463.interrupts.packetRx = false;
	  }
	  if (si4463.interrupts.crcError)
	  {
		  /* Handling this interrupt here */

		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.crcError = false;
	  }
	  if (si4463.interrupts.txFifoAlmostEmpty)
	  {
		  /* Handling this interrupt here */

		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.txFifoAlmostEmpty = false;
	  }
	  if (si4463.interrupts.rxFifoAlmostFull)
	  {
		  /* Handling this interrupt here */

		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.rxFifoAlmostFull = false;
	  }

	  /* Handling Modem interrupts */
	  if (si4463.interrupts.postambleDetect)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.postambleDetect = false;
	  }
	  if (si4463.interrupts.rssiJump)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.rssiJump = false;
	  }
	  if (si4463.interrupts.rssi)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.rssi = false;
	  }
	  if (si4463.interrupts.invalidPreamble)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.invalidPreamble = false;
	  }
	  if (si4463.interrupts.preambleDetect)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.preambleDetect = false;
	  }
	  if (si4463.interrupts.syncDetect)
	  {
		  /* Handling this interrupt here */
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.syncDetect = false;
	  }

	  if (si4463.interrupts.chipReady)
	  {
		  /* Handling this interrupt here */
		  SI4463_GetChipStatus(&si4463);
		  /* Following instruction only for add breakpoints. May be deleted */
		  si4463.interrupts.chipReady = false;
	  }
	  /* Clear All interrupts before exit */
	  SI4463_ClearAllInterrupts(&si4463);
  }

}

uint8_t SI4463_IsCTS(void)
{
	if((CTS_GPIO_Port->IDR & CTS_Pin) != (uint32_t)GPIO_PIN_RESET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void SI4463_WriteRead(const uint8_t * pTxData, uint8_t * pRxData, const uint16_t sizeTxData)
{
	HAL_SPI_TransmitReceive(&hspi1,(uint8_t*) pTxData, pRxData, sizeTxData, 100);
}

void SI4463_SPIRead(const uint8_t * pRxData, const uint16_t sizeRxData)
{
	HAL_SPI_Receive(&hspi1, (uint8_t*) pRxData, sizeRxData, 100);
}

void SI4463_SPITransmit(const uint8_t * pTxData, const uint16_t sizeTxData)
{
	HAL_SPI_Transmit(&hspi1, (uint8_t*) pTxData, sizeTxData, 100);
}

void SI4463_SetShutdown(void)
{
	HAL_GPIO_WritePin(SDN_GPIO_Port, SDN_Pin, GPIO_PIN_SET);
}

void SI4463_ClearShutdown(void)
{
	HAL_GPIO_WritePin(SDN_GPIO_Port, SDN_Pin, GPIO_PIN_RESET);
}

void SI4463_Select(void)
{
	SPI1_NSS_GPIO_Port->BSRR = (uint32_t)SPI1_NSS_Pin << 16U;
	DWT_Delay_us(10);
}

void SI4463_Deselect(void)
{
	SPI1_NSS_GPIO_Port->BSRR = SPI1_NSS_Pin;
	DWT_Delay_us(10);
}

uint16_t SI4463_CheckModule(void)
{
	uint8_t i;
	if(ADC_Get_Vbat() > 700) // if low battery
	{
		if(SI4463_CheckDevice(&si4463) == SI4463_OK)
		{
			for(i=0; i<6; i++)
			{
				HAL_GPIO_TogglePin(LED_TX_GPIO_Port,LED_TX_Pin);
				HAL_GPIO_TogglePin(LED_RX_GPIO_Port,LED_RX_Pin);
				DWT_Delay_ms(100);
			}
		}
		else
		{
			for(i=0; i<6; i++)
			{
				HAL_GPIO_TogglePin(LED_RX_GPIO_Port,LED_RX_Pin);
				DWT_Delay_ms(100);
			}
			return 0;
		}
	}
	else
	{
		check_module_flag |= (1<<7);
		for(i=0; i<60; i++)
		{
			if(0 != (check_module_flag & (1<<7)) )
			{
				HAL_GPIO_WritePin(LED_TX_GPIO_Port,LED_TX_Pin,GPIO_PIN_RESET);
				break;
			}
		HAL_GPIO_TogglePin(LED_TX_GPIO_Port,LED_TX_Pin);
		DWT_Delay_ms(500);
		}
		return 0;
	}
	return 1;
}

uint8_t Check_CMD(void)
{


	uint16_t U3v3 = 0;
	uint16_t c_temp = 0;
	uint16_t Ubat = 0;

	uint8_t ret = clearFlag;

	char str[10];

	switch (flagModemCmd)
	{

		case cmdGetRemoteTemp :

			c_temp = ((2194*SI4463_GetTempAdc(&si4463)) / 1000) - 2930;
			sprintf(str, "%d\n", c_temp / 10);
			//SI4463_Transmit(&si4463,(uint8_t*)(&str), strlen(str));

			SI4463_GetChipStatus(&si4463);
			SI4463_GetInterrupts(&si4463);

			ret = flagModemCmd;
			flagModemCmd = clearFlag;

			break;

		case cmdGetRemote3v3 :
			for(uint8_t i=0; i<10; i++)
			{
				U3v3 += (30*SI4463_GetBatAdc(&si4463))/128;
			}
			U3v3 = U3v3/10;
			sprintf(str, "%d.%.2d\n", U3v3 / 100, U3v3 % 100);
			//SI4463_Transmit(&si4463, (uint8_t*)(&str), strlen(str));

			SI4463_GetChipStatus(&si4463);
			SI4463_GetInterrupts(&si4463);

			ret = flagModemCmd;
			flagModemCmd = clearFlag;
			break;

		case cmdGetRemoteBat :

			Ubat = ADC_Get_Vbat();
			sprintf(str, "%d.%d\n", Ubat / 100, Ubat % 100);
			//SI4463_Transmit(&si4463, (uint8_t*)(&str), strlen(str));

			SI4463_GetChipStatus(&si4463);
			SI4463_GetInterrupts(&si4463);

			ret = flagModemCmd;
			flagModemCmd = clearFlag;
			break;

		case cmdTurnRight :
			break;

		case cmdTurnleft :
			break;

		case cmdGOForward :
			break;

		case cmdGoBack :
			break;

		case cmdSetTxPower :

			SI4463_SetTxPower(&si4463,incomingBuffer[TxPWR]);
			flagModemCmd = clearFlag;
			break;

		default :
			break;
	}
	return ret;
}

uint8_t send_to_udp(uint8_t *packet, uint8_t len, uint32_t dest_ip)
{
    eth_frame_t *frame = (void*)net_buf;
    ip_packet_t *ip = (void*)(frame->data);
    udp_packet_t *udp = (void*)(ip->data);

    ip->to_addr = dest_ip;
    udp->to_port = DEST_PORT;
    udp->from_port = LOCAL_PORT;
    memset(udp->data, 0, len);
    memcpy(udp->data,packet, len);
    udp_send(frame, len);
    return 1;
}

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
