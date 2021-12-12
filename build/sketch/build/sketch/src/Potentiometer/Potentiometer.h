/**************************************
 * @file    Potentiometer.h
 * @brief   interface for Potentiometer
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

class Potentiometer
{
private:
    /* private attributes */
    byte pin;
    unsigned int calib_min; // pot min possible value
    unsigned int calib_max; // pot max possible value

public:
    /* constructor */
    Potentiometer() {}       

    /* constructor overloads */
    Potentiometer(byte pin);
    Potentiometer(byte pin, unsigned int min, unsigned int max);

    /* methods */ 
    // direct ADC read 0-1024
    unsigned int readRaw();
    // voltage read 0-5 [V]
    float readVoltage();
    // read percantage range 0-100% 
    // offset of min and max is included
    unsigned int readPercentage();
};

#endif