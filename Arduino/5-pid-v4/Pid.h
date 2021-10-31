/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Pid_h
#define Pid_h

// access to standard types and constants
#include "Arduino.h"

class Pid
{
  public:
    // Constructor
    Pid(float Kp_in, float Ki_in, float Kd_in);
    
    // Functions
    void setSetpoint(float setpoint);
    float calculate(float process_variable);

    // tuning parameters
    float Kp;
    float Ki;
    float Kd;

    float PV;
    float SPa;
    float MVa;

    float _error;
    float _error_previous;
    float _error_diff;
    
  private:   
    float _P;
    float _I;
    float _D;
};

#endif
