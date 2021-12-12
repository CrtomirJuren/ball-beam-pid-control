/**************************************
 * @file    Application.cpp
 * @brief   implementation for Application class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/
# include "Application.h"

/* class contructor overloads */
// Application::Application(Led &ledGreen,
//                          Led &ledYellow,
//                          Led &ledRed,
//                          LedBlinker &ledBlinkerGreen,
//                          PushButton &button,
//                          Potentiometer &potentiometer){
                               
//     this->ledGreen = ledGreen;
//     this->ledYellow = ledYellow;
//     this->ledRed = ledRed;
//     this->ledBlinkerGreen = ledBlinkerGreen;
//     this->button = button;
//     this->potentiometer = potentiometer;
// } 

Application::Application(PushButton &button){
    this->button = button;
}

/* initialization method, default */
void Application::init(){
    // init controls
    button.init();

//     // init indicators
//     ledGreen.init();
//     ledYellow.init();
//     ledRed.init();



    /* init statemachine */
    state = STATE_IDLE;
    isEntering = true;

    /* after init end, wait for safety*/
    delay(100);
}

void Application::setSerial(Stream *streamObject){
    // save pointer to Serial object
    _streamRef = streamObject;
}

void Application::sendText(char *someText)
{
    _streamRef->println(someText);
}

void Application::updateLedsBrightness(){
    // unsigned int percent = potentiometer.readPercentage();
  
    // set led dimming value  
    //   ledGreen.setBrightness(percent);
    //   ledYellow.setBrightness(percent);
    //   ledRed.setBrightness(percent);
}

void Application::fadeLeds(){
    // change the brightness for next time through the loop:
    //   brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    //   if (brightness <= 0 || brightness >= 255) {
    // fadeAmount = -fadeAmount;
    //   }
}

/* run */ 
void Application::update(){
    unsigned long timeNow = millis();
    unsigned long errMsg = 1000;
    // // updateLedsBrightness();

    // /* statemachine */
    switch(state){
    //     /*******************************/
        case STATE_IDLE:{
            /* entering */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("IDLE: State Enter");
            }

            /* running */
            if (button.isPressed()){
                isExiting = true;
                sendText("IDLE: Button pressed");
            }
            
            /* exiting */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state                
                state = STATE_A;
            }
            break;
        }
    //     /*******************************/
        case STATE_A:{
            /* entering */
            if (isEntering){
                isEntering = false;
                timerStart = millis();
                sendText("A: State Enter");
                setGreen();
            }

            /* running */
            if (button.isPressed()){
                isExiting = true;
                sendText("IDLE: Button pressed");
            }

            /* exiting */
            if (isExiting){
                isExiting = false;
                isEntering = true;
                // next state
                state = STATE_IDLE;
                sendText("A: State Exit");
            }
            break;
        }
    //     /*******************************/
    //     case STATE_B: {
    //         /* entering state */
    //         if (isEntering){
    //             isEntering = false;
    //             timerStart = millis();
    //             sendText("B: State Enter");
    //             setYellow();
    //         }
            
    //         /* running */
    //         if (timeNow - timerStart > StateDuration){
    //             isExiting = true;
    //         }

    //         /* exiting state */
    //         if (isExiting){
    //             isExiting = false;
    //             isEntering = true;
    //             // next state
    //             state = STATE_C;
    //             sendText("B: State Exit");
    //         }
    //         break;
    //     }
    //     /*******************************/
    //     case STATE_C: {
    //         /* entering state */
    //         if (isEntering){
    //             isEntering = false;
    //             timerStart = millis();
    //             sendText("C: State Enter");
    //             setRed();
    //         }
            
    //         /* running */
    //         if (timeNow - timerStart > StateDuration){
    //             isExiting = true;
    //         }

    //         /* exiting state */
    //         if (isExiting){
    //             isExiting = false;
    //             isEntering = true;
    //             // next state
    //             state = STATE_END;
    //             sendText("C: State Exit");
    //         }
    //         break;
    //     }
    //     /*******************************/
    //     case STATE_END: {
    //         /* entering state */
    //         if (isEntering){
    //             isEntering = false;
    //             timerStart = millis();
    //             sendText("END: State Enter");
    //             // functions on enter
    //             allLedsOff();
    //         }
            
    //         /* running */
    //         isExiting = true;
            
    //         /* exiting state */
    //         if (isExiting){
    //             isExiting = false;
    //             isEntering = true;
    //             // next state
    //             state = STATE_IDLE;
    //             sendText("END: State Exit");
    //         }
    //         break;
    //     }
    //     /*******************************/
        default: {
            // error
            if (timeNow - timerStart > errMsg){
                timerStart = timeNow;
                sendText("Unknown state request");
            }
            
        }
    }
}

void Application::allLedsOff(){
    // ledGreen.off();
    // ledYellow.off();
    // ledRed.off();
}

void Application::allLedsOn(){
    // ledGreen.on();
    // ledYellow.on();
    // ledRed.on();
}

void Application::setGreen(){
    // ledGreen.on();
    // ledYellow.off();
    // ledRed.off();
}

void Application::setYellow(){
    // ledGreen.off();
    // ledYellow.on();
    // ledRed.off();
}

void Application::setRed(){
    // ledGreen.off();
    // ledYellow.off();
    // ledRed.on();
}

