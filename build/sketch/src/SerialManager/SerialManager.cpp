/**************************************
 * @file    SerialManager.cpp
 * @brief   implementation for SerialManager
 * @author  Črtomir Juren
 * @version 1.0 4/10/20 
 **************************************/
# include "SerialManager.h"

/* class contructor */
// SerialManager::SerialManager(HardwareSerial &serRef){

// }

// SerialManager::SerialManager(Stream &serRef){
//     this->serRef = serRef;
// }

// SerialManager::TestPrint(){

// }

// void SerialManager::setSerial(HardwareSerial *serRef)
// {
//     this->serRef = serRef;
// }

// void sendText(char *someText)
// {
//     serRef->println(someText);
// }
// SerialManager(HardwareSerial* serial, unsigned long sendPeriod){
//     stream = serial;
//     this->sendPeriod = sendPeriod;
//     lastTimeSent = millis();
// }

// void send(const char* msg){
//     unsigned long timeNow = millis();

//     if ((timeNow - lastTimeSent) >= sendPeriod){
//         lastTimeSent = timeNow;
//         stream->println(msg);
//     }
// }

// void sendString(String &msg){
//     unsigned long timeNow = millis();

//     if ((timeNow - lastTimeSent) >= sendPeriod){
//         lastTimeSent = timeNow;
//         stream->println(msg);
//     }
// }