/*
 * sharp_distance.h
 *
 *  Created on: 18.08.2018
 *      Author: rafal
 */

#ifndef SHARP_DISTANCE_H_
#define SHARP_DISTANCE_H_


// Sharp distance meter aproximation function y = exp_A * (e^(Exp_B * x))
// x = voltage from sensor, y = distance
// Constants:
#define exp_A	1093.7
#define exp_B	-0.002

double __sharp_get_distance(double voltage);

#endif /* SHARP_DISTANCE_H_ */
