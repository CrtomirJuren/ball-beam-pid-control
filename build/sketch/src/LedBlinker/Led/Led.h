/**************************************
 * @file    Led.h
 * @brief   interface for Led class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    /* attributes */
    byte pin;      
    bool state;
    bool isPWM;
    int brightness;

    /* private methods */
    bool isPoweredOn();

public:
    /* constructor */
    Led() {}       
    
    /* constructor ovverides */
    Led(byte pin); 
    Led(byte pin, bool isPWM);

    /* methods */ 
    // init the pin for LED, call this in setup()
    void init();
    void init(byte defaultState);

    // power on the LED
    void on();
    //power off the LED
    void off();
    //power on/off the LED, depending on previous state
    void toggle();

    // set brightness if LED is in pwm mode
    void setBrightness(int brightness);

};

#endif