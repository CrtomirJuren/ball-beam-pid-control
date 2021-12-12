/**************************************
 * @file    LedBlinker.h
 * @brief   interface for LedBlinker class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef LEDBLINKER_H
#define LEDBLINKER_H

# include <Arduino.h>
# include "Led\Led.h"

class LedBlinker
{
private:
    /* private attributes */
    Led led; // reference to the object

    unsigned long lastTimeBlinked;
    unsigned long blinkDelay;      
        
    /* private methods */
    void toggleLed();

public:
    /* constructor */
    LedBlinker() {}       // defualt, must have

    /* constructor overloads */
    LedBlinker(Led &led);                            // 500ms default delay
    LedBlinker(Led &led, unsigned long blinkDelay);  // custom blink delay

    /* methods: initialization, call this in setup() */ 
    void init();

    /* methods: setter, getter*/
    unsigned long getBlinkDelay();
    void setBlinkDelay(unsigned long blinkDelay);

    /* methods */ 
    void update();
    void setBrightness(unsigned int brightness);
};

#endif