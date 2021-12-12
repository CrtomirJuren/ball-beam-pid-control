/**************************************
 * @file    SerialManager.h
 * @brief   interface for SerialManager
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/

/*
    HardwareSerial and SoftwareSerial both inherit behavior 
    from Stream (which inherits behavior from Print). 
    If you pass the serial port as a "Stream" (pointer or reference)
    then it will work with both hardware and software serial ports.
*/

#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include <Arduino.h>
#include <Stream.h>
#include <HardwareSerial.h>

// Dependencies
// Print -> Stream -> HardwareSerial => [Serial]
// Stream ... it contains reading functionality

class SerialManager{
    private:
        // Stream* stream;
        // Stream serRef;

        // HardwareSerial serRef;

        unsigned long lastTimeSent;
        unsigned long sendPeriod; 

    public:
        SerialManager() {}
        
        // SerialManager(Stream &serRef);

};

#endif