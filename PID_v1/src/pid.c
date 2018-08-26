/*
 * pid.c
 *
 *  Created on: 17.08.2018
 *      Author: rafal
 */
#include <pid.h>

void PID_Initalize(pid_regulator *pid){
	pid->integral = 0.0;
	pid->derivative = 0.0;
	pid->error_p = 0.0;
	pid->error = 0.0;
	pid->output = 0.0;

}

void PID_set_parameters(pid_regulator *pid, double Kp, double Ki, double Kd, double dt){
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->dt = dt;
}

void PID_set_setpoint(pid_regulator *pid, double setpoint){
	pid->setpoint = setpoint;
}

double PID_calculate(pid_regulator *pid){
	pid->error = pid->setpoint - pid->actual_position;
	pid->integral = pid->integral + (pid->error * pid->dt);
	pid->derivative = (pid->error_p - pid->error) / pid->dt;
	pid->output = (pid->error * pid->Kp) + (pid->integral * pid->Ki) + (pid->derivative * pid->Kd);
	pid->error_p = pid->error;
	return pid->output;
}
