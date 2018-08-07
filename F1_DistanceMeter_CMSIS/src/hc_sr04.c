/*
 * hc-sr04.c
 *
 *  Created on: 29.07.2018
 *      Author: Rafal Kubis
 */
#include <hc_sr04.h>

volatile hc_sr04_state hc_sr04;
volatile uint16_t __hc_sr04_counter_cnt;


void hc_sr04_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM4EN;;
	// enable clk for, TIM2, TIM3
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN; // GPIOB , GPIOA clock enable

	__hc_sr04_tim_init();
	__hc_sr04_exti_init();



}

void __hc_sr04_tim_init(void){
//	TIM2->CR1 |= TIM_CR1_CEN;		// TIM2 enable. clk 8MHz, no division



//	TIM1->CR2 |= TIM_CR2_
/*
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0;
	TIM1->ARR = 800 - 1;				// Count to 79 -- 10us
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
	TIM1->CCR1 = 250;
	TIM1->CR1 |= TIM_CR1_OPM;
	TIM1->RCR = 1;
	TIM3->EGR |= TIM_EGR_UG;
	TIM1->CR1 |= TIM_CR1_CEN;

	TIM3->CR1 |= TIM_CR1_CEN;
	TIM3->ARR = 800 - 1;				// Count to 79 -- 10us


	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0; // PWM mode 2
	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
	TIM3->CCR1 = 250;
	TIM3->CR1 |= TIM_CR1_OPM;
	TIM3->SMCR |= TIM_SMCR_ETF | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1;
	TIM3->EGR |= TIM_EGR_CC1G | TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_CEN;
*/
	TIM4->ARR = 280;	// pulse period
	TIM4->RCR = 0;		// repetition
	TIM4->CCMR1 |= (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); // PWM mode 1
	TIM4->CCER |= TIM_CCER_CC1E;	// output capture/compare enable
	TIM4->CCR1  = 79;	// delay
	TIM4->CR1 |= TIM_CR1_OPM; 	//  One pulse mode
}

void __hc_sr04_exti_init(void){
//	GPIOA->CRL |= GPIO_CRL_CNF5_1;	// input mode, pull D/U
//	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

//	EXTI->IMR |= EXTI_IMR_IM5;		// pin5 masked interrupt
//	EXTI->RTSR |= EXTI_RTSR_TR15;	// rising edage
	//EXTI->FTSR |= EXTI_FTSR_TR5;	// faling edage

//	GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0;	// PA.6 AF mode for TIM3


	GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1; // PB6 AF mode, 50MHz


}

hc_sr04_state hc_sr04_measure(void){
	hc_sr04_state result;
	switch (hc_sr04){
		case idle:
			__hc_sr04_set_trigger();
			hc_sr04 = requestForMeasure;
			break;
	}

	return requestForMeasure;
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
	TIM4->CR1 |= TIM_CR1_CEN;
}

uint16_t __hc_sr04_get_distance_mm(void){
	double result = (double)((__hc_sr04_counter_cnt * HC_SR04_CLK_PEROID) / 58.0);
	hc_sr04 = idle;
	return (uint16_t)(result*10);
}
 inline void __hc_sr04_stop_timer(void){
	 TIM2->CR1 &= ~TIM_CR1_CEN;

 }

 inline void __hc_sr04_start_timer(void){
	 TIM2->CNT = 0;;
	 TIM2->CR1 |= TIM_CR1_CEN;
 }

 inline uint16_t __hc_sr04_timer_get_cnt(void){
	 return (uint16_t)(TIM2->CNT);
 }
