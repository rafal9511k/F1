/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f103xb.h"

#include "my_lib_usart.h"

char buffer[] = "1\n2\n";
uint8_t rx_buffer[RX_BUFFER_SIZE];
uint32_t rx_cnt;
uint8_t rx_data_rdy;
int main(void)
{

//	__usart_tx_init();
//	__dma_transmit_init(buffer);

//	USART2->SR &= ~USART_SR_TC;
	__usart_rx_init();
	__usart_rx_irq_enable();
	NVIC_EnableIRQ(38);

	while(1){
		for(uint32_t i =0; i < 0xfffff; i++){

		}
	//	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
	//	DMA1->IFCR |= DMA_IFCR_CGIF7;
	//	DMA1_Channel7->CNDTR = 7;
	//	USART2->SR &= ~USART_SR_TC;
	//	DMA1_Channel7->CCR|= DMA_CCR_EN;


	}
}

void USART2_IRQHandler(void){
	rx_buffer[rx_cnt] = USART2->DR;
	rx_buffer[rx_cnt + 1] = '\0';
	if (rx_buffer[rx_cnt] == '\r'){
		rx_data_rdy = 1;
	}
	if(rx_cnt < RX_BUFFER_SIZE - 1){
		rx_cnt++;
	}

}





