/*
 * my_lib_adc.h
 *
 *  Created on: 15.08.2018
 *      Author: rafal
 */

#ifndef MY_LIB_ADC_H_
#define MY_LIB_ADC_H_

#include "stm32f1xx.h"

#define __ADC_1LSB 0.80566

void __adc1_single_channel_gpio_init(void);
void __adc1_single_channel_init(void);
void __adc1_start_conversion(void);
void __adc1_eoc_interrupt_enable(void);
uint16_t __adc1_get_data(void);


#endif /* MY_LIB_ADC_H_ */
