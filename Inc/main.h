/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
enum cmd_receive_status_e
{
	clearFlag = 0,
	cmdGetLocalTemp = 100,
	cmdGetLocal3v3,
	cmdGetLocalBat,
	cmdGetRemote3v3,
	cmdGetRemoteBat,
	cmdGetRemoteTemp,
	cmdGetRemoteTelemetry,
	cmdTurnRight,
	cmdTurnleft,
	cmdGOForward,
	cmdGoBack,
	cmdSetTxPower,
	cmdStartTestMode,
	cmdStopTestMode,
	cmdTxHop
};

enum IncomingBufPosition_e
{
	Command_Number = 0,
	TransmittedValue,
	ReturnValue,
	Button,
	ReceiveCMD,
	TxPWR,
	MotionControl,
	Speed
};

typedef struct
{
	uint8_t  	packetType;
	uint8_t  	_pad_byte1;
	uint8_t 	packedId;
	uint8_t  	flags;
	uint8_t   	velocity;
	uint8_t   	steering;
}  PlatformPacket_t; // __attribute__ ((__packed__))

typedef struct data {
	uint8_t one;
	uint8_t two;
	uint8_t three;
	uint8_t four;
	uint8_t five;
	uint8_t six;
	uint8_t seven;
	uint8_t eight;
	uint8_t nine;
	uint8_t ten;
	uint8_t eleven;
	uint8_t twelve;
	uint8_t thirteen;
	uint8_t fourteen;
	uint8_t fiveteen;
	uint8_t sixteen;
	uint8_t seventeen;
	uint8_t eighteen;
	uint8_t nineteen;
	uint8_t twenty;
	uint8_t twentyone;
	uint8_t twentytwo;
	uint8_t twentythree;
	uint8_t twentyfour;
	uint8_t twentyfive;
	uint8_t twentysix;
	uint8_t twentyseven;
	uint8_t twentyeight;
	uint8_t twentynine;
	uint8_t thirty;
	uint8_t thirtyone;
	uint8_t thirtytwo;
} data_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
enum cmd_receive_status_e	flagModemCmd;
enum IncomingBufPosition_e	BuffPos;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
uint8_t SI4463_IsCTS(void);
void SI4463_WriteRead(const uint8_t * pTxData, uint8_t * pRxData, const uint16_t sizeTxData);
void SI4463_SPIRead(const uint8_t * pRxData, const uint16_t sizeRxData);
void SI4463_SPITransmit(const uint8_t * pTxData, const uint16_t sizeTxData);
void SI4463_SetShutdown(void);
void SI4463_ClearShutdown(void);
void SI4463_Select(void);
void SI4463_Deselect(void);
uint8_t Check_CMD(void);
uint8_t send_to_udp(uint8_t *packet, uint8_t len, uint32_t dest_ip);


uint32_t udp_receive(void *data, uint16_t len);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Ubat_Pin GPIO_PIN_0
#define Ubat_GPIO_Port GPIOC
#define SDN_Pin GPIO_PIN_1
#define SDN_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define CTS_Pin GPIO_PIN_5
#define CTS_GPIO_Port GPIOC
#define nIRQ_Pin GPIO_PIN_1
#define nIRQ_GPIO_Port GPIOB
#define nIRQ_EXTI_IRQn EXTI1_IRQn
#define SPI3_NSS_Pin GPIO_PIN_7
#define SPI3_NSS_GPIO_Port GPIOC
#define INT_Pin GPIO_PIN_2
#define INT_GPIO_Port GPIOD
#define LED_RX_Pin GPIO_PIN_6
#define LED_RX_GPIO_Port GPIOB
#define LED_TX_Pin GPIO_PIN_7
#define LED_TX_GPIO_Port GPIOB
#define PWR_ON_Pin GPIO_PIN_8
#define PWR_ON_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
