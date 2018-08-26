/*
 * my_lib_adc.c
 *
 *  Created on: 15.08.2018
 *      Author: rafal
 */

#include "my_lib_adc.h"

void __adc1_single_channel_init(void){
	__adc1_single_channel_gpio_init();
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		// adc1 clock enable

	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_EXTSEL_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTTRIG;
	// adc on, software trigger, external trigger
	ADC1->CR2 |= ADC_CR2_CAL;	// ADC calibration
	while (ADC1->CR2 & ADC_CR2_CAL){
		// waiting for end of calibration
	}
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_1;		// channel 0 sampling 13.5 cycles
}
void __adc1_start_conversion(void){
	ADC1->CR2 |= ADC_CR2_SWSTART;
}
void __adc1_single_channel_gpio_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


}
void __adc1_eoc_interrupt_enable(void){
	ADC1->CR1 |= ADC_CR1_EOCIE;	// end of conversion interrupt enable
}

uint16_t __adc1_get_data(void){
	return ADC1->DR;
}
