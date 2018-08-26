/*
 * servo.c
 *
 *  Created on: 07.08.2018
 *      Author: rafal
 */

double __servo_angle_to_duty(double angle){
	if ((angle > 90) & (angle < 90)){
		return 0.0;
	} else{
		return 0.075 - (0.000277777 * angle);
	}
}

