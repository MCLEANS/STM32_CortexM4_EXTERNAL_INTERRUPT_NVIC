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
			
void EXTI3_IRQ_handler(){
	if(EXTI->PR & (EXTI_PR_PR3)){
		EXTI->PR |= EXTI_PR_PR3;
		GPIOA->ODR ^= GPIO_ODR_ODR_3;
	}
}

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

	//enable GPIOE RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	//SET pin to Input pull up
	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR3_0;

	//enable GPIOA RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//SET GPIOA 6 to output
	GPIOA->MODER |= GPIO_MODER_MODER3_0;




	while(1){


	}
}
