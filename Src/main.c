/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* Function processing DMA Rx data. Counts how many capital and small letters are in sentence.
 * Result is supposed to be stored in global variable of type "letter_count_" that is defined in "main.h"
 *
 * @param1 - received sign
 */
void proccesDmaData(uint8_t sign);

/* Space for your global variables. */

	// type your global variables here:
int start=0;
int poc_prijatych=0;
int poc_malych=0;
int poc_velkych=0;
//uint8_t tx_data[];
letter_count_ nazov;
uint8_t* compose(int capacity, int occupied);

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();

  USART2_RegisterCallback(proccesDmaData);

  /* Space for your local variables, callback registration ...*/

  	  //type your code here:
  	  	uint8_t tx1[] = "Buffer capacity: ";
  		uint8_t tx2[] = " bytes, occupied memory: ";
  		uint8_t tx3[] = " bytes, load [in %]: ";
  		uint8_t tx4[] = "  %\n \r";

  		while (1)
  {
	  /* Periodic transmission of information about DMA Rx buffer state.
	   * Transmission frequency - 5Hz.
	   * Message format - "Buffer capacity: %d bytes, occupied memory: %d bytes, load [in %]: %f%"
	   * Example message (what I wish to see in terminal) - Buffer capacity: 1000 bytes, occupied memory: 231 bytes, load [in %]: 23.1%
	   */

  	  	  	  //type your code here:

	  USART2_CheckDmaReception();

		int occupied = numOfOccupied();
		int capacity = sizeOfBuff();
		float occupied1 = occupied;
		float percentage = occupied1/capacity*100.0;
		uint8_t final[100];
		uint8_t pomoc1[10],pomoc2[10],pomoc3[10];
		memset(final,0,sizeof(final));
		itoa(capacity,pomoc1,10);
		strcpy(final,tx1);
		strcat(final, pomoc1);
		itoa(occupied,pomoc2,10);
		strcat(final,tx2);
		strcat(final, pomoc2);
		strcat(final,tx3);
		gcvt(percentage, 4, pomoc3);
		strcat(final,pomoc3);
		strcat(final,tx4);

	  USART2_PutBuffer(final, strlen(final));
	  LL_mDelay(1000);

  }
  /* USER CODE END 3 */
}

uint8_t* compose(int capacity, int occupied)
{
	uint8_t tx1[] = "Buffer capacity: ";
	uint8_t tx2[] = " bytes, occupied memory: ";
	uint8_t tx3[] = " bytes, load [in %]: ";
	uint8_t tx4[] = "%\n";

	uint8_t percentage = (occupied / capacity) * 100;
	uint8_t final[100];
	uint8_t pomoc1[10],pomoc2[10],pomoc3[10];
	itoa(capacity,pomoc1,10);
	strcpy(final,tx1);
	strcat(final, pomoc1);
	itoa(occupied,pomoc2,10);
	strcat(final,tx2);
	strcat(final, pomoc2);
	strcat(final,tx3);
	itoa(percentage,pomoc3,10);
	strcat(final,pomoc3);
	strcat(final,tx4);

	return final;
}

void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
}

/*
 * Implementation of function processing data received via USART.
 */
void proccesDmaData(uint8_t sign)
{
	/* Process received data */

		// type your algorithm here:


		if (start==0 && sign=='#'){				// zaciatok
					start=1;
		}

		if(start==1 && sign!=0)
		{
			poc_prijatych++;

			if(sign>='A' && sign<='Z'){
				poc_velkych++;
			}
			if(sign>='a' && sign<='z'){
				poc_malych++;
			}
		}

		if (poc_prijatych==35 && start == 1){
					start=0;
					poc_malych=0;
					poc_velkych=0;
					poc_prijatych=0;
		}

		if (start==1 && sign=='$'){				// konec

					start=0;

					nazov.capital_letter+=poc_velkych;
					nazov.small_letter+=poc_malych;

				}

}


void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(char *file, uint32_t line)
{ 

}

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
