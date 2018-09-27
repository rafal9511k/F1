/*
 * my_lib_usart.h
 *
 *  Created on: 25.09.2018
 *      Author: rafal
 */
#include "stm32f1xx.h"

#ifndef MY_LIB_USART_H_
#define MY_LIB_USART_H_

#define RX_BUFFER_SIZE 16
#define RX_END_OF_LINE "\r"
//#define RX_END_OF_LINE "\l\n"

void __usart_tx_init(void);
void __dma_transmit_init(char *buffer);
void __usart_rx_init(void);
void __usart_rx_irq_enable(void);
uint32_t __usart_rx_get_line(char *buffer);


#endif /* MY_LIB_USART_H_ */
