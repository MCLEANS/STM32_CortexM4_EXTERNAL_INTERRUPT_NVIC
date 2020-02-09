/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
			

int main(void)
{

	//Enable the system configuration RCC
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	//Point the SYSCFG to the correct PIN
	//Set to PE_3
	SYSCFG->EXTICR |= SYSCFG_EXTICR1_EXTI3_PE;
	//Enable the PIN interrupt
	EXTI->IMR |= EXTI_IMR_MR3;
	//Set whether on rising or falling edge
	EXTI->FTSR |= EXTI_FTSR_TR3;

	//set NVIC interrupt priority
	NVIC_SetPriority(EXTI3_IRQn,0x03);
	//enable NVIC interrupt
	NVIC_EnableIRQ(EXTI3_IRQn);

	//enable GPIOA RCC


	while(1){


	}
}
