/**************************************
 * @file    Led.cpp
 * @brief   implementation for Led class
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

# include "Led.h"

/* class contructor */
Led::Led(byte pin){
    this->pin = pin; //_pin = pin;
    state = LOW;
}

Led::Led(byte pin, bool isPWM){
    this->pin = pin; //_pin = pin;
    this->isPWM = isPWM;
    state = LOW;

    setBrightness(100);
    // brightness = 255;
}

/* initialization method */
void Led::init(){
    pinMode(pin, OUTPUT);
}

/* initialization method, overload*/
void Led::init(byte defaultState){
    init();
    if(defaultState == HIGH){
        on();
    }
    else{
        off();
    }
}

// brightness is in percentage 0-100[%]
void Led::setBrightness(int brightness){
    // convert user input 0-100[%] -> 0-255
    brightness = map(brightness, 0, 100, 0, 255);

    // store to class attribute
    this->brightness = brightness;
}

/* led on method */ 
void Led::on(){
    state = HIGH;

    // if led is pwm controlled
    if (isPWM){
        analogWrite(pin, brightness);
    }
    // if led is normal digital on/off
    else{
        digitalWrite(pin, state);   // turn the LED on (HIGH is the voltage level)        
    }
}

/* led off method */ 
void Led::off(){
    state = LOW;
    digitalWrite(pin, state);   // turn the LED on (HIGH is the voltage level)
}

//  abstracting, so code is written in higher language
bool Led::isPoweredOn(){
    // if state is HIGH, than return true
    return (state == HIGH);
}

void Led::toggle(){
    // if (state == HIGH){
    if (isPoweredOn()){
        off();
    }
    else{
        on();
    }
}