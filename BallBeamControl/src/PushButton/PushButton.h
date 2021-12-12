/**************************************
 * @file    PushButton.h
 * @brief   interface for Button class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>

enum ButtonMode {
    // pulldown, external
    BTN_EXT_DOWN = 0,
    // pullup, external
    BTN_EXT_UP = 1,
    // pullup, internal in mcu
    BTN_INT_UP = 2  
};

class PushButton
{
private:
    /* attributes */
    //BTN_EXT_DOWN, BTN_EXT_UP, BTN_INT_UP
    ButtonMode buttonMode; 

    byte pin;
    bool state;
    bool lastState;
    bool pressed;

    /* the following variables are unsigned longs because the time, measured in
       milliseconds, will quickly become a bigger number than can be stored in an int */
    unsigned long lastDebounceTime;  // the last time the output pin was toggled
    unsigned long debounceDelay;    // the debounce time; increase if the output flickers
    unsigned long lastTimeStateChanged;

    // get current button state, private method
    void readState();

public:
    /* constructor */
    PushButton() {}       // contructor, defualt, must have
    PushButton(byte pin, int debounceDelay, ButtonMode buttonMode); // contructor

    /* methods */ 
    // init the button, call this in setup()
    void init();
    
    bool isPressed();
};

#endif