/*
 * hc-sr04.h
 *
 *  Created on: 29.07.2018
 *      Author: Rafal Kubis
 *
 *      HC-SR04 distance meter
 *      Using GPIO External Interrupt with Timer TIM2
 *      to count time for propagation signal
 *      from sensor and back.
 *      PA5 - echo - time of propagated signal
 *      PA6 - trigger,  HIGH state for min. 20ms
 */


#ifndef HC_SR04_H_
#define HC_SR04_H_

#include "stm32f1xx.h"

#define HC_SR04_CLK_PEROID 0.125


typedef enum {
	idle,
	requestForMeasure,
	measuring,
	dataReady,
	error,
	notReady
} hc_sr04_state;

void hc_sr04_init(void);
void __hc_sr04_tim_init(void);
void __hc_sr04_exti_init(void);
hc_sr04_state hc_sr04_measure(void);
void hc_sr04_irq_function(void);
extern void __hc_sr04_set_trigger(void);
uint16_t __hc_sr04_get_distance_mm(void);
extern void __hc_sr04_stop_timer(void);
extern void __hc_sr04_start_timer(void);
extern uint16_t __hc_sr04_timer_get_cnt(void);


volatile hc_sr04_state hc_sr04;
volatile uint16_t __hc_sr04_counter_cnt;


#endif /* HC_SR04_H_ */
