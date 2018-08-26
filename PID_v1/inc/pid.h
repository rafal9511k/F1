/*
 * pid.h
 *
 *  Created on: 17.08.2018
 *      Author: rafal
 */

#ifndef PID_H_
#define PID_H_

typedef struct pid_regulator{
	double error;
	double error_p;
	double integral;
	double derivative;
	double output;
	double MAX;
	double MIN;
	double Kp, Kd, Ki;
	double dt;
	double setpoint;
	double actual_position;
} pid_regulator;

void PID_Initalize(pid_regulator *pid);
void PID_set_parameters(pid_regulator *pid, double Kp, double Ki, double Kd, double dt);
void PID_set_setpoint(pid_regulator *pid, double setpoint);
double PID_calculate(pid_regulator *pid);

#endif /* PID_H_ */
