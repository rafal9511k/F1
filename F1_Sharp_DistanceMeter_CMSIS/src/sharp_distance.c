/*
 * sharp_distance.c
 *
 *  Created on: 18.08.2018
 *      Author: rafal
 */
#include <sharp_distance.h>

double __sharp_get_distance(double voltage){
	double distance = exp_A * exp(exp_B * voltage);
	return distance;
}

