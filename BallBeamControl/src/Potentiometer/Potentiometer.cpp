/**************************************
 * @file    Potentiometer.cpp
 * @brief   implementation for LedBlinker class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/
# include "Potentiometer.h"

/* class contructor overloads */
Potentiometer::Potentiometer(byte pin){
    this->pin = pin;
}

Potentiometer::Potentiometer(byte pin, unsigned int calib_min, unsigned int calib_max){
    this->pin = pin;
    this->calib_min = calib_min;
    this->calib_max = calib_max;
}


/* read from analog input */
unsigned int Potentiometer::readRaw(){
    //   read the input on analog pin 0:
    return analogRead(pin);
}

/* read from analog input */
float Potentiometer::readVoltage(){
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    return (readRaw() * (5.0 / 1023.0));
}

unsigned int Potentiometer::readPercentage(){

    // map(value, fromLow, fromHigh, toLow, toHigh)
    return (unsigned int) map(readRaw(), calib_min, calib_max, 0, 100);
    // unsigned int value = readRaw
    // float mapped = map(adc, 0, 1023, 0, 255);
}