/*
 * my_lib.h
 *
 *  Created on: 07.08.2018
 *      Author: rafal
 */

#ifndef MY_LIB_H_
#define MY_LIB_H_

#include <stm32f1xx.h>
#include "string.h"
#include "stdlib.h"

TIM_HandleTypeDef tim;
ADC_HandleTypeDef adc;

void __usart_tx_init(void);
void __dma_transmit_init(char *buffer);
void __dma_send_data(uint16_t data, char *buffer);
void __adc_init(void);
void __adc_start_conversion(void);
uint16_t __adc_get_data(void);

void __pwm_init(void);
void __pwm_set_compare(uint16_t compare);
void __pwm_set_duty(double duty);
void __pwm_enable_base_interrupt(void);
void __pwm_clear_it_flag(void);


#endif /* MY_LIB_H_ */
