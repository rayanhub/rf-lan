/*
 * delay_dwt.h
 *
 *  Created on: Feb 29, 2020
 *      Author: run
 */

#ifndef DELAY_DWT_DELAY_DWT_H_
#define DELAY_DWT_DELAY_DWT_H_

#include "stm32f2xx_hal.h"


#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

void DWT_DelayUpdate(void);
void DWT_Init(void);
uint32_t DWT_GetTick(void);
void DWT_Delay_sec(uint32_t sec);
void DWT_Delay_ms(uint32_t ms);
void DWT_Delay_us(uint32_t us);
uint8_t DWT_Test_sec(uint32_t start, uint32_t time);
uint8_t DWT_Test_ms(uint32_t start, uint32_t time);
uint8_t DWT_Test_us(uint32_t start, uint32_t time);
uint32_t DWT_Time_sec(uint32_t start, uint32_t current);
uint32_t DWT_Time_ms(uint32_t start, uint32_t current);
uint32_t DWT_Time_us(uint32_t start, uint32_t current);

#endif /* DELAY_DWT_DELAY_DWT_H_ */
