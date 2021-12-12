/**************************************
 * @file    Application.h
 * @brief   interface for Application
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include <Stream.h>

# include "LedBlinker\Led\Led.h"    // no dependancy
# include "LedBlinker\LedBlinker.h" //LedBlinker class is dependant on Led class

# include "PushButton\PushButton.h" // no dependancy
# include "Potentiometer\Potentiometer.h" // no dependancy

# include "SerialManager\SerialManager.h" // no dependancy

enum StateMachine{
    STATE_IDLE,
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_END,
};

class Application
{
private:
    /* private attributes */
    int i;
    Led ledGreen;
    Led ledYellow;
    Led ledRed;
    LedBlinker ledBlinkerGreen;
    PushButton button;
    Potentiometer potentiometer;
    Stream *_streamRef;

    byte ledsBrightness;

    /* statemachine */ 
    int state = STATE_IDLE;
    bool isEntering = true;
    bool isExiting = false;

    unsigned long timerStart;
    const int StateDuration = 3000;

    unsigned long StateAStartTime;
    unsigned long StateBStartTime;
    unsigned long StateCStartTime;

    /* private method */
    void updateLedsBrightness();
    void fadeLeds();

public:
    /* constructor */
    Application() {}

    /* constructor overloads */
    /* pass objects with reference */
    Application(PushButton &button);

    // Application(Led &ledGreen,
    //              Led &ledYellow,
    //              Led &ledRed,
    //              LedBlinker &ledBlinkerGreen,
    //              PushButton &button,
    //              Potentiometer &potentiometer);   
    
    /* main methods */ 
    void init();          
    void update();

    void setSerial(Stream *streamObject);
    void sendText(char *someText);

    /* other methods */ 
    void allLedsOn();
    void allLedsOff();
    void setGreen();
    void setYellow();
    void setRed();
};

#endif