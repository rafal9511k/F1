/*
 * my_lib_usart.c
 *
 *  Created on: 25.09.2018
 *      Author: rafal
 */
#include "my_lib_usart.h"
#include "stm32f1xx.h"
#include "string.h"

extern volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
extern volatile uint32_t rx_cnt;

void __usart_tx_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;	// Push-Pull, AF, 50MHz

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

void __usart_rx_init(void){
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	GPIOA->CRL |= GPIO_CRL_CNF3_0;					// input PU/PD
	USART2->BRR = 0x341;							// baudrate 9600, 51.08
	USART2->CR1 = USART_CR1_UE | USART_CR1_RE;		// USART enable, rx enable
}

void __usart_rx_irq_enable(void){
	rx_cnt = 0;
	USART2->CR1 |= USART_CR1_RXNEIE;
}
/*
 * 		Function __usart_rx_get_line returns length of line when new line of data is available if not
 * 		return 0;
 */


uint32_t __usart_rx_get_line(char *buffer){
	static char *end_of_line = NULL;
	static char *new_end_of_line = NULL;
	uint32_t length;
	if(end_of_line == NULL){
		end_of_line = strstr(rx_buffer, RX_END_OF_LINE);
		if(end_of_line == NULL){
			new_end_of_line == NULL;
			return 0;
		} else {
			buffer = rx_buffer;
			return (end_of_line - buffer);
		}
	} else {
		new_end_of_line = strstr(end_of_line, RX_END_OF_LINE);
		if( new_end_of_line == NULL){
			return 0;
		} else {
			buffer = end_of_line;
			length = new_end_of_line - end_of_line;
			end_of_line = new_end_of_line;
			return length;
		}
	}


}


