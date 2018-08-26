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
#include "pid.h"
#include "my_lib_adc.h"
#include "my_lib.h"
#include "sharp_distance.h"
#include "servo.h"

volatile double adc_voltage;
volatile pid_regulator pid;
double angle;

int main(void)
{
	angle = 0;
	PID_Initalize(&pid);
	PID_set_parameters(&pid, 0.2, 0.003, 0.001, 0.02);
	PID_set_setpoint(&pid, 300);
	__pwm_init();
	__pwm_enable_base_interrupt();
	__pwm_set_duty(0.075);
	__adc1_single_channel_init();
	__adc1_eoc_interrupt_enable();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
	__adc1_start_conversion();
	while(1){

	}
}

void TIM2_IRQHandler(void){
	__pwm_clear_it_flag();
	__adc1_start_conversion();

}

void ADC1_2_IRQHandler(void){
	uint16_t adc_value = __adc1_get_data();
	adc_voltage = (double)adc_value * __ADC_1LSB;
	pid.actual_position = __sharp_get_distance(adc_voltage);
	double pid_tmp = PID_calculate(&pid);

	angle = pid_tmp;
	if(angle > 90.0){
		angle = 90.0;
	}
	if(angle < -90.0){
		angle = -90.0;
	}
	double duty = __servo_angle_to_duty(angle);
	__pwm_set_duty(__servo_angle_to_duty(angle));
}
