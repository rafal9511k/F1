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
#include <my_lib_adc.h>
#include <sharp_distance.h>

int main(void)
{
	__adc1_single_channel_init();
	for(uint32_t i = 0; i < 0xfffff; i++){

	}
	__adc1_eoc_interrupt_enable();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__adc1_start_conversion();
	for(uint32_t i = 0; i < 0xfffff; i++){

	}
	uint16_t data = ADC1->DR;
	while(1){

	}
}


void ADC1_2_IRQHandler(void){

}
