/*
 * hc-sr04.c
 *
 *  Created on: 29.07.2018
 *      Author: Rafal Kubis
 */
#include "hc-sr04.h"

void hc_sr04_init(void){
	RCC->APB1ENR |= RCC_APB2ENR_IOPAEN | RCC_APB1ENR_TIM2EN;
	// enable clk for GPIOA and TIN2
	__hc_sr04_tim_init();
	__hc_sr04_exti_init();


	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void __hc_sr04_tim_init(void){
//	TIM2->CR1 |= TIM_CR1_CEN;		// TIM2 enable. clk 8MHz, no division
}

void __hc_sr04_exti_init(void){
	GPIOA->CRL |= GPIO_CRL_CNF5_1;	// input mode, pull D/U
	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

	EXTI->IMR |= EXTI_IMR_IM5;		// pin5 masked interrupt
	EXTI->RTSR |= EXTI_RTSR_TR15;	// rising edage
	EXTI->FTSR |= EXTI_FTSR_TR5;	// faling edage
}

void hc_sr04_measure(void){

}

void hc_sr04_irq_function(void){

}

double __hc_sr04_get_distance_cm(void){
	return -1;
}
 inline void __hc_sr_stop_timer(void){
	 TIM2->CR1 &= ~TIM_CR1_CEN;
 }

 inline void __hc_sr_start_timer(void){
	 TIM2->CR1 |= TIM_CR1_CEN;
 }
