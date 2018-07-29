/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
			

int main(void)
{
	RCC->APB1ENR |= RCC_APB2ENR_IOPAEN | RCC_APB1ENR_TIM2EN;

	GPIOA->CRL |= GPIO_CRL_CNF5_1;	// input mode, pull D/U
	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

	EXTI->IMR |= EXTI_IMR_IM5;		// pin5 masked interrupt
	EXTI->RTSR |= EXTI_RTSR_TR15;	// rising edage
	EXTI->FTSR |= EXTI_FTSR_TR5;	// faling edage

	NVIC_EnableIRQ(EXTI9_5_IRQn);
//	EXTI->SWIER |= EXTI_SWIER_SWI5;	// software trigger



	for(;;);
}



void EXTI9_5_IRQHandler(void){

	EXTI->PR |= EXTI_PR_PIF5;
}
