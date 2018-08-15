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
#include "stdlib.h"
#include "string.h"
#include "math.h"

void __usart_tx_init(void);
void __dma_transmit_init(char *buffer);
void __dma_send_data(uint16_t data);
void __adc_init(ADC_HandleTypeDef *adc);
char buffer[25];

int main(void)
{
	ADC_HandleTypeDef adc;


	__adc_init(&adc);
	__usart_tx_init();
	__dma_transmit_init(buffer);
//	USART2->SR &= ~USART_SR_TC;

	uint16_t value;
	while(1){
		value = 0;
		for(int i = 0; i < 10; i++){
			HAL_ADC_Start(&adc);

			for(uint32_t j = 0; j < 0xff00; j++){

			}
			value += HAL_ADC_GetValue(&adc) ;
		}
		value /= 10;
		double voltage = ((double)value) * 0.80566;
		double distance = 1093.7 * exp(-0.002 * voltage);
		for(uint16_t i = 0; i < 25; i++){
			buffer[i] = '\0';
		}
		itoa((int)distance, buffer, 10);
		strcat(buffer, "\n");
		DMA1_Channel7->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR |= DMA_IFCR_CGIF7;
		DMA1_Channel7->CNDTR = 25;
		USART2->SR &= ~USART_SR_TC;
		DMA1_Channel7->CCR|= DMA_CCR_EN;



	}
}


void __usart_tx_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;	// Push-Pull, AF, 50MHz

	USART2->BRR = 0x341;							// baudrate 9600, 51.08
	USART2->CR1 = USART_CR1_UE | USART_CR1_TE;		// USART enable, tx enable
	USART2->CR3 = USART_CR3_DMAT;					// DMA Tx
//	USART2->DR = 'a';
}

void __dma_transmit_init(char *buffer){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel7->CCR = DMA_CCR_MINC | DMA_CCR_DIR;	// 8bit to 8bit from memory,
																	// incremented memory address, enable channel
	DMA1_Channel7->CMAR = (uint32_t)buffer; 	// memory address
	DMA1_Channel7->CPAR = (uint32_t)(&(USART2->DR));		// destination address
	DMA1_Channel7->CNDTR = 25;
	DMA1_Channel7->CCR |= DMA_CCR_EN;

}

void __dma_send_data(uint16_t data){
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

void __adc_init(ADC_HandleTypeDef *adc){
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


	adc->Instance = ADC1;
	adc->Init.ContinuousConvMode = DISABLE;
	adc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc->Init.DiscontinuousConvMode = DISABLE;
	adc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adc->Init.NbrOfConversion = 1;
	adc->Init.NbrOfDiscConversion = 1;
	adc->Init.ScanConvMode = ADC_SCAN_DISABLE;
	HAL_ADC_Init(adc);

	HAL_ADCEx_Calibration_Start(adc);

	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel = ADC_CHANNEL_0;
	adc_ch.Rank = ADC_REGULAR_RANK_1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
	HAL_ADC_ConfigChannel(adc, &adc_ch);
}
