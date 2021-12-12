/**************************************
 * @file    PushButton.cpp
 * @brief   implementation for Button class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

/*  The circuit
    EXTERNAL PULLDOWN:
    - LED attached from pin 13 to ground (LED_BUILTIN)
    - pushbutton attached to pin 2 from +5V
    - 10K resistor attached to pin 2 from ground
    
    EXTERNAL PULLUP:

    INTERNAL PULLUP:

*/

# include "PushButton.h"

// /* class contructor */
PushButton::PushButton(byte pin, int debounceDelay, ButtonMode buttonMode){
    this->pin = pin; 
    this->debounceDelay = debounceDelay;    // default(50), debounce time; increase if the output flickers
    this->buttonMode = buttonMode;

    lastTimeStateChanged = millis(); //  the last time the output pin was toggled
}

/* initialization method */
void PushButton::init(){
    // internal pullup resistor used
    if(buttonMode == BTN_INT_UP){
        pinMode(pin, INPUT_PULLUP);
    }
    // external mode
    else{
        pinMode(pin, INPUT);
    }

    // first state read
    // readState(); cant use this because of debounce
    state = digitalRead(pin);
}

// private method, to read button state and debounce
void PushButton::readState(){
    unsigned long timeNow = millis();

    // debounce functionality, check time to last button read
    if ((timeNow - lastTimeStateChanged) > debounceDelay){
        bool newState = digitalRead(pin);
        // save state only if change
        if (newState != state){
            state = newState;
            lastTimeStateChanged = timeNow;
        }
    }
}

// public method, to se if button is pressed
bool PushButton::isPressed(){
    readState();
    
    // if pulldown mode
    if(buttonMode == BTN_EXT_DOWN){
        // return true if we are reading high
        return(state == HIGH);
    }
    // if pullup mode
    else{
        // return true if we are reading low
        return(state == LOW);
    }
}