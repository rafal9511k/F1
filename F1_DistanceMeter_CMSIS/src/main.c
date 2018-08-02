/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include <hc_sr04.h>
#include "stm32f1xx.h"
			
uint16_t data;

int main(void)
{
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI5_PA;
	GPIOA->CRL |= GPIO_CRL_CNF5_0;	// floating
//	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

	EXTI->IMR |= EXTI_IMR_MR5;		// pin5 masked interrupt
	EXTI->RTSR |= EXTI_RTSR_TR5;	// rising edage
	EXTI->FTSR |= EXTI_FTSR_TR5;	// faling edage

	NVIC_EnableIRQ(EXTI9_5_IRQn);
//	EXTI->SWIER |= EXTI_SWIER_SWI5;	// software trigger
	hc_sr04_init();

	hc_sr04 = requestForMeasure;
	__hc_sr04_set_trigger();
	while(1){
		if(hc_sr04 == dataReady){
			 data = __hc_sr04_get_distance_mm();
		}
		if(hc_sr04 == idle){
			hc_sr04_measure();
		}
	}
}



void EXTI9_5_IRQHandler(void){
	hc_sr04_irq_function();
	EXTI->PR |= EXTI_PR_PIF5;
}
