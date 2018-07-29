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



typedef enum {
	idle,
	requestForMeasure,
	measuring,
	dataReady,
	error,
	notReady
} hc_sr04_state;

extern volatile hc_sr04_state hc_sr04;
volatile __hc_sr04_counter_cnt;
#endif /* HC_SR04_H_ */
