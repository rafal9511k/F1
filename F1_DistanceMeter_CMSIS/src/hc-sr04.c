/*
 * hc-sr04.c
 *
 *  Created on: 29.07.2018
 *      Author: Rafal Kubis
 */
#include "hc-sr04.h"

void hc_sr04_init(void){
	RCC->APB1ENR |= RCC_APB2ENR_IOPAEN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN;
	// enable clk for GPIOA, TIM2, TIM3
	__hc_sr04_tim_init();
	__hc_sr04_exti_init();


	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void __hc_sr04_tim_init(void){
//	TIM2->CR1 |= TIM_CR1_CEN;		// TIM2 enable. clk 8MHz, no division
	TIM3->CR1 |= TIM_CR1_OPM;
}

void __hc_sr04_gpio_exti_init(void){
	GPIOA->CRL |= GPIO_CRL_CNF5_1;	// input mode, pull D/U
	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

	EXTI->IMR |= EXTI_IMR_IM5;		// pin5 masked interrupt
	EXTI->RTSR |= EXTI_RTSR_TR15;	// rising edage
	EXTI->FTSR |= EXTI_FTSR_TR5;	// faling edage

	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1;

}

hc_sr04_state hc_sr04_measure(void){
	hc_sr04_state result;
	switch (hc_sr04){
		case idle:

	}

	return result;
}



void hc_sr04_irq_function(void){
	switch (hc_sr04){
		case requestForMeasure:
			hc_sr04 = measuring;
			__hc_sr04_start_timer();
			break;
		case measuring:
			hc_sr04 = dataReady;
			__hc_sr04_stop_timer();
			__hc_sr04_counter_cnt = __hc_sr04_timer_get_cnt();
			break;
	}
}

inline void __hc_sr04_set_trigger(void){

}

inline void __hc_sr04_reset_trigger(void){

}

uint16_t __hc_sr04_get_distance_mm(void){
	return 0;
}
 inline void __hc_sr04_stop_timer(void){
	 TIM2->CR1 &= ~TIM_CR1_CEN;
 }

 inline void __hc_sr04_start_timer(void){
	 TIM2->CR1 |= TIM_CR1_CEN;
 }

 inline uint16_t __hc_sr04_timer_get_cnt(void){
	 return TIM2->CNT;
 }
