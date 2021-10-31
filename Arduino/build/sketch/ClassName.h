#ifndef ClassName_h
#define ClassName_h

// access to standard types and constants
#include "Arduino.h"

class ClassName
{
  public:
    // Constructor
    ClassName(int pin);
    // Functions
    void dot();
    void dash();
    
  private:
    // variables
    int _pin;
};

#endif
