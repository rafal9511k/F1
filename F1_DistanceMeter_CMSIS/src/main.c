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
#include "string.h"
#include "stdlib.h"
			
uint16_t data;
char buffer[25];

void __usart_tx_init(void);
void __dma_transmit_init(char *buffer);
void __dma_send_data(uint16_t data);

int main(void)
{
	__usart_tx_init();
	__dma_transmit_init(buffer);
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI4_PB;
	GPIOB->CRL |= GPIO_CRL_CNF4_0;	// floating
//	GPIOA->ODR &= ~GPIO_ODR_ODR5;	// pin5 dowm

	EXTI->IMR |= EXTI_IMR_MR4;		// pin5 masked interrupt
	EXTI->RTSR |= EXTI_RTSR_TR4;	// rising edage
	EXTI->FTSR |= EXTI_FTSR_TR4;	// faling edage

	NVIC_EnableIRQ(EXTI4_IRQn);
//	EXTI->SWIER |= EXTI_SWIER_SWI5;	// software trigger
	hc_sr04_init();

	hc_sr04 = requestForMeasure;
	__hc_sr04_set_trigger();
	while(1){
		if(hc_sr04 == dataReady){
			 data = __hc_sr04_get_distance_mm();
			for(uint16_t i = 0; i < 0xffff; i++){

			}
			 __dma_send_data(data);

		}
		if(hc_sr04 == idle){
			hc_sr04_measure();
		}
	}
}



void EXTI4_IRQHandler(void){
	hc_sr04_irq_function();
	EXTI->PR |= EXTI_PR_PIF4;
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
	strcat(buffer, "\r\n");

	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
	DMA1->IFCR |= DMA_IFCR_CGIF7;
	DMA1_Channel7->CNDTR = 25;
	USART2->SR &= ~USART_SR_TC;
	DMA1_Channel7->CCR|= DMA_CCR_EN;


}
