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
#include "inc/my_lib_usart.h"


char rx_buffer[RX_BUFFER_SIZE];

int main(void)
{
	char *pointer;
	for(uint32_t i = 0; i < RX_BUFFER_SIZE; i++){
		rx_buffer[i] = 'a';
	}
	__usart_rx_init();
	uint32_t length = __usart_rx_get_line(pointer);
	for(;;);
}


//	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
//	DMA1->IFCR |= DMA_IFCR_CGIF7;
//	DMA1_Channel7->CNDTR = 7;
//	USART2->SR &= ~USART_SR_TC;
//	DMA1_Channel7->CCR|= DMA_CCR_EN;
