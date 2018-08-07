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

void __usart_tx_init(void);
void __dma_transmit_init(char *buffer);

char buffer[] = "1\n2\n";

int main(void)
{
	__usart_tx_init();
	__dma_transmit_init(buffer);
//	USART2->SR &= ~USART_SR_TC;


	while(1){
		for(uint32_t i =0; i < 0xfffff; i++){

		}
		DMA1_Channel7->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR |= DMA_IFCR_CGIF7;
		DMA1_Channel7->CNDTR = 7;
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



