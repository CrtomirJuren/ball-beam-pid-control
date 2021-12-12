/**************************************
 * @file    ClassTemplate.h
 * @brief   interface for ClassTemplate
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

#ifndef CLASS_TEMPLATE_H
#define CLASS_TEMPLATE_H

#include <Arduino.h>

class ClassTemplate
{
private:
    /* private attributes */
    byte pin;

    /* private methods */ 

public:
    /* constructor */
    ClassTemplate() {}       

    /* constructor overloads */
    ClassTemplate(byte a); 
    ClassTemplate(byte a, byte b); 
    ClassTemplate(byte a, byte b, byte c); 

    /* public methods */ 
    // inits the class, call this in setup()
    void init();          // init method, default
    void init(byte d);    // init method, overload

    void run();
};

#endif