/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Serial_h
#define Serial_h

// access to standard types and constants
#include "Arduino.h"

void initialize_serial(void);

void serialEvent(void);

void external_function(void);
/*
class Morse
{
  public:
    // Constructor
    Morse(int pin);
    // Functions
    void dot();
    void dash();
    void function();
    
  private:
    // variables
    int _pin;
};
*/
#endif
