/**************************************
 * @file    Application.cpp
 * @brief   implementation for Application class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/
# include "Application.h"

/* class contructor overloads */
TrafficLight::TrafficLight(Led &ledGreen,
                           Led &ledYellow,
                           Led &ledRed,
                           LedBlinker &ledBlinkerGreen,
                           PushButton &button,
                           Potentiometer &potentiometer){
                               
    this->ledGreen = ledGreen;
    this->ledYellow = ledYellow;
    this->ledRed = ledRed;
    this->ledBlinkerGreen = ledBlinkerGreen;
    this->button = button;
    this->potentiometer = potentiometer;
} 

/* initialization method, default */
void TrafficLight::init(){
    // init indicators
    ledGreen.init();
    ledYellow.init();
    ledRed.init();

    // init controls
    button.init();

    /* init statemachine */
    // state = STATE_IDLE;
    // isEntering = true;

    /* after init end, wait for safety*/
    delay(100);
}

void TrafficLight::setSerial(Stream *streamObject){
    // save pointer to Serial object
    _streamRef = streamObject;
}

void TrafficLight::sendText(char *someText)
{
    _streamRef->println(someText);
}

void TrafficLight::updateLedsBrightness(){
    unsigned int percent = potentiometer.readPercentage();
  
    // set led dimming value  
    //   ledGreen.setBrightness(percent);
    //   ledYellow.setBrightness(percent);
    //   ledRed.setBrightness(percent);
}

void TrafficLight::fadeLeds(){
    // change the brightness for next time through the loop:
    //   brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    //   if (brightness <= 0 || brightness >= 255) {
    // fadeAmount = -fadeAmount;
    //   }
}

/* run */ 
void TrafficLight::update(){
    unsigned long timeNow = millis();

    // updateLedsBrightness();

    /* statemachine */
    switch(state){
        /*******************************/
        case STATE_IDLE:{
            /* entering state */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("IDLE: State Enter");
            }

            /* running state */
            if (button.isPressed()){
                isExiting = true;
                sendText("IDLE: Button pressed");
            }
            
            /* exiting state */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state                
                state = STATE_A;
            }
            break;
        }
        /*******************************/
        case STATE_A:{
            /* entering */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("A: State Enter");
                setGreen();
            }

            /* running */
            if (timeNow - timerStart > StateDuration){
                isExiting = true;
            }

            /* exiting */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state
                state = STATE_B;
                sendText("A: State Exit");
            }
            break;
        }
        /*******************************/
        case STATE_B: {
            /* entering state */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("B: State Enter");
                setYellow();
            }
            
            /* running */
            if (timeNow - timerStart > StateDuration){
                isExiting = true;
            }

            /* exiting state */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state
                state = STATE_C;
                sendText("B: State Exit");
            }
            break;
        }
        /*******************************/
        case STATE_C: {
            /* entering state */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("C: State Enter");
                setRed();
            }
            
            /* running */
            if (timeNow - timerStart > StateDuration){
                isExiting = true;
            }

            /* exiting state */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state
                state = STATE_END;
                sendText("C: State Exit");
            }
            break;
        }
        /*******************************/
        case STATE_END: {
            /* entering state */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("END: State Enter");
                // functions on enter
                allLedsOff();
            }
            
            /* running */
            isExiting = true;
            
            /* exiting state */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state
                state = STATE_IDLE;
                sendText("END: State Exit");
            }
            break;
        }
        /*******************************/
        default: {
            //todo
        }
    }
}

void TrafficLight::allLedsOff(){
    ledGreen.off();
    ledYellow.off();
    ledRed.off();
}

void TrafficLight::allLedsOn(){
    ledGreen.on();
    ledYellow.on();
    ledRed.on();
}

void TrafficLight::setGreen(){
    ledGreen.on();
    ledYellow.off();
    ledRed.off();
}

void TrafficLight::setYellow(){
    ledGreen.off();
    ledYellow.on();
    ledRed.off();
}

void TrafficLight::setRed(){
    ledGreen.off();
    ledYellow.off();
    ledRed.on();
}

