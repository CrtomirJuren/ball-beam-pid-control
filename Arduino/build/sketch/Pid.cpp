/*
  pid.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.

  proportional–integral–derivative controller (PID controller or three-term controller) is a control loop mechanism employing feedbac

PV(process variable): current position
SP(setpoint): The desired position

The difference between the PV and SP is the error (e), which quantifies whether the arm is too low or too high and by how much.
The input to the process (the electric current in the motor) is the output from the PID controller. It is called either the manipulated variable (MV) or the control variable (CV).
*/

#include "Arduino.h"
#include "Pid.h"

/* TEST PARAMETERS FOR BALL BEAM PROJECT
//deluje -> kp = 0.5, ki = 0, kd = 4, 
//deluje -> kp = 0.2, ki = 0, kd = 4, 

//float pid_kp=0.5, pid_ki=0.05, pid_kd=10; boljše

//float pid_kp=0.5, pid_ki=0, pid_kd=6; hitrejše
//float pid_kp=0.5, pid_ki=0.5, pid_kd=6; NE DELUJE ki ZMEDE
//float pid_kp=0.5, pid_ki=0.1, pid_kd=6; DELUJE

VERZIJA 4
//float pid_kp=0.5, pid_ki=0.05, pid_kd=5;
*/

// class constructor
Pid::Pid(float Kp_in, float Ki_in, float Kd_in)
{
  //pinMode(pin, OUTPUT);
  // tuning parameters
  Kp = Kp_in;
  Ki = Ki_in;
  Kd = Kd_in;

  SPa = 0;
  MVa = 0;
  PV = 0;
  _error = 0;
  _error_previous = 0;
  _P = 0;
  _I = 0;
  _D = 0;
}

void Pid::setSetpoint(float setpoint)
{
  /* setpoint
   *  
   */
  SPa = setpoint;
}

float Pid::calculate(float process_variable)
{
  /* Calculate PID controller output
   * input: PV (processing variable): position, speed
   * output: 0% ... 100%
   */

  PV = process_variable;

  //calculate error
  _error_previous = _error;
  _error = SPa - PV;
  _error_diff = _error - _error_previous;

  //P (proportional)
  _P = _error * Kp;

  //I (integral)
  _I = _I + _error;
  _I = _I* Ki;
  
  //D (derivate)
  //derivate = (pid_mv - pid_mv_previous )*pid_kd;
  _D = Kd * _error_diff;

  //if pid_mv < 0, motor angle > 90, ball will accelerate towards sensor
  //if pid_mv = 0,  motor angle = 90, ball will not accelerate
  //if pid_mv > 0, motor angle < 90, ball will accelerate away from sensor
  //pid_mv = 0; // -100% < pid_mv< 100%
  MVa = _P + _I + _D;
  
  return MVa;  
}
