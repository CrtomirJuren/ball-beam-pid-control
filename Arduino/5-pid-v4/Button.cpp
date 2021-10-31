#include "Arduino.h"
#include "Button.h"

// class constructor
Button::Button(byte pin){
    _pin = pin;
    _lastReading = LOW;
    
    init();
    //pinMode(_pin, INPUT);
    // update here
}

void Button::init(){
    pinMode(_pin, INPUT);
    update();
}

void Button::update(){
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    // byte newReading = digitalRead(pin);
    
    if (_newReading != _lastReading) {
        _lastDebounceTime = millis();
    }
    if (millis() - _lastDebounceTime > _debounceDelay) {
        // Update the 'state' attribute only if debounce is checked
        _state = _newReading;
    }
    _lastReading = _newReading;
}

byte Button::getState(){
    update();
    return _state;
}

bool Button::isPressed(){
    return (getState() == HIGH);
}

/*
    Button(byte pin) {
      this->pin = pin;
      lastReading = LOW;
      init();
    }
    void init() {
      pinMode(pin, INPUT);
      update();
    }
    void update() {
      // You can handle the debounce of the button directly
      // in the class, so you don't have to think about it
      // elsewhere in your code
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        // Update the 'state' attribute only if debounce is checked
        state = newReading;
      }
      lastReading = newReading;
    }
    byte getState() {
      update();
      return state;
    }
    bool isPressed() {
      return (getState() == HIGH);
    }
}; // don't forget the semicolon at the end of the class
*/