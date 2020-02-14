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

int toggle = 0;




//void EXTI3_IRQHandler(void){
///	if(EXTI->PR & (EXTI_PR_PR3)){
//		EXTI->PR |= EXTI_PR_PR3;
///		toggle = 1;
//	}
//}






int main(void)
{

	//---------Configure PLL 168MHz as clock source-------------
	//SET FLASH MEMORY LATENCY AND ENABLE PREFETCH
		FLASH->ACR &= ~FLASH_ACR_LATENCY;
		FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
		FLASH->ACR |= FLASH_ACR_PRFTEN;

		//Enable HSI
		RCC->CR |= RCC_CR_HSION;
		//check if HSI is ready
		while(!(RCC->CR & (1<<1))){}
		//set PLL SOURCE to HSI
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
		//set Division factor for the main PLL division clock to 8
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
		//set main PLL multiplication factor to 168
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_5;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
		//set PLL division factor for main system clock to 2
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;

		//Set APB1 clock frequency to 42MHz(prescaler of 4)
		RCC->CFGR &= ~RCC_CFGR_PPRE1;
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
		//Set APB2 clock frequency to 84MHz(prescaler of 2)
		RCC->CFGR &= ~RCC_CFGR_PPRE2;
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
		//Enable PLL
		RCC->CR |= RCC_CR_PLLON;
		//check if PLL is ready
		while(!(RCC->CR & (1<<25))){}
		//Select PLL as system clock
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		//check to confirm PLL being used
		while(!(RCC->CFGR & RCC_CFGR_SWS_PLL )){}

	//------------------------------------------------------
	//Enable the system configuration RCC
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	//enable GPIOE RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	//enable GPIOA RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Point the SYSCFG to the correct PIN
	//Set to PE_3
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PE;

	//Set whether on rising or falling edge
	EXTI->FTSR |= EXTI_FTSR_TR3;
	//EXTI->RTSR |= EXTI_RTSR_TR2;
	//Enable the PIN interrupt
	EXTI->IMR |= EXTI_IMR_MR3;



	//SET pin to Input pull up
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR3_0;


	//SET GPIOA 6 to output
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
	GPIOA->OTYPER |= GPIO_OTYPER_OT_7;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0;
	GPIOA->ODR |= (1<<7);




	//enable NVIC interrupt
	NVIC_EnableIRQ(EXTI2_IRQn);
	//set NVIC interrupt priority
	NVIC_SetPriority(EXTI2_IRQn,0);


	while(1){
		if(EXTI->PR & (EXTI_PR_PR3)){
				EXTI->PR |= EXTI_PR_PR3;
				toggle = 1;
			}

		if(toggle == 1){
			GPIOA->ODR ^= GPIO_ODR_ODR_7;
			toggle = 0;
		}
	}
}



