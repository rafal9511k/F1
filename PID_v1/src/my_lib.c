/*
 * my_lib.c
 *
 *  Created on: 07.08.2018
 *      Author: rafal
 */

#include "my_lib.h"





void __dma_send_data(uint16_t data, char *buffer){
	for(uint16_t i = 0; i < 25; i++){
		buffer[i] = '\0';
	}
	itoa((int)data, buffer, 10);
	strcat(buffer, "\l\n");
	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
	DMA1->IFCR |= DMA_IFCR_CGIF7;
	DMA1_Channel7->CNDTR = 25;
	USART2->SR &= ~USART_SR_TC;
	DMA1_Channel7->CCR|= DMA_CCR_EN;


}

void __adc_init(void){
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pin = GPIO_PIN_0;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);

	RCC_PeriphCLKInitTypeDef adc_clk;
	adc_clk.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	adc_clk.AdcClockSelection = RCC_ADCPCLK2_DIV2;
	HAL_RCCEx_PeriphCLKConfig(&adc_clk);


	adc.Instance = ADC1;
	adc.Init.ContinuousConvMode = DISABLE;
	adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc.Init.DiscontinuousConvMode = DISABLE;
	adc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adc.Init.NbrOfConversion = 1;
	adc.Init.NbrOfDiscConversion = 1;
	adc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	HAL_ADC_Init(&adc);

	HAL_ADCEx_Calibration_Start(&adc);

	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel = ADC_CHANNEL_0;
	adc_ch.Rank = ADC_REGULAR_RANK_1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
	HAL_ADC_ConfigChannel(&adc, &adc_ch);
}

uint16_t __adc_get_data(void){
	return HAL_ADC_GetValue(&adc);
}

void __adc_start_conversion(void){
	HAL_ADC_Start(&adc);
}


void __pwm_init(void){
	HAL_Init();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_1;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);

	tim.Instance = TIM2;
	tim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	tim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
	tim.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim.Init.Period = 999;
	tim.Init.Prescaler = 160;
	tim.Init.RepetitionCounter = 0;
//	HAL_TIM_Base_Init(&tim);
	HAL_TIM_PWM_Init(&tim);
	HAL_TIM_Base_Start_IT(&tim);

	TIM_OC_InitTypeDef oc;
	oc.Pulse = 100;
	oc.OCMode = TIM_OCMODE_PWM1;
	oc.OCPolarity = TIM_OCPOLARITY_HIGH;
	oc.OCNPolarity = TIM_OCNPOLARITY_LOW;
	oc.OCFastMode = TIM_OCFAST_ENABLE;
	oc.OCIdleState = TIM_OCIDLESTATE_SET;
	oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	oc.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&tim, &oc, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&tim, TIM_CHANNEL_2);
}

void __pwm_enable_base_interrupt(void){
//	HAL_TIM_Base_Start_IT(&tim);
}

void __pwm_set_compare(uint16_t compare){
	__HAL_TIM_SET_COMPARE(&tim, TIM_CHANNEL_2, compare);
}

void __pwm_set_duty(double duty){
	double high = (double)tim.Init.Period * duty;
	__pwm_set_compare((uint16_t) high);
}

void __pwm_clear_it_flag(void){
	__HAL_TIM_CLEAR_IT(&tim, TIM_IT_UPDATE);
}
