#include "Arduino.h"
#include "ClassName.h"

// class constructor
ClassName::ClassName(int pin)
{
  //pinMode(pin, OUTPUT);
  _pin = pin;
}

void ClassName::dot()
{
  //digitalWrite(_pin, HIGH);
  delay(10);
  //digitalWrite(_pin, LOW);
  //delay(250);  
}

void ClassName::dash()
{
  //digitalWrite(_pin, HIGH);
  delay(10);
  //digitalWrite(_pin, LOW);
  //delay(250);
}
