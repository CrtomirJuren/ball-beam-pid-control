/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Serial.h"

// serial event variables
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void initialize_serial(void){
  // set serial speed
  Serial.begin(9600);
  // wait until serial port opens
  while (! Serial) {
    delay(1);
  }
  //------SET ARDUINO SERIAL PLOTTER NAMES------------
  Serial.println("SP, mv, pv_nofilter, pv_filter, err");   
}

void serialEvent(void){
  /*
    SerialEvent occurs whenever a new data comes in the hardware serial RX. This
    routine is run between each time loop() runs, so using delay inside loop can
    delay response. Multiple bytes of data may be available.
  */
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void external_function(void){
  Serial.print('this is external data');  
}

/*
// class constructor
Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}

void Morse::function()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
*/

//--------------------SERIAL COM---------------------

// serial event variables
// transfer to serial.cpp
//String inputString = "";         // a String to hold incoming data
//bool stringComplete = false;  // whether the string is complete

// valid comand parsing variables
//bool validCommand = false;
//String rx_command;
//String rx_type;
//String rx_value;
//String parsingString = "";

//if received existing command, send back blink
/*
void valid_command_blink(void){
  digitalWrite(ledbuiltinPin, HIGH);
  delay(50);
  digitalWrite(ledbuiltinPin, LOW);
}
*/
/*
void execute_command(String command, String value){
  //execute_command: all commands that arduino executes are listed here
  if(command == "setpoint"){
    //echo back
    Serial.println(value);
    //if(value == "1"){digitalWrite(led1Pin, true);}
    //if(value == "0"){digitalWrite(led1Pin, false);}    
  }
  if(command == "LED2"){
    //if(value == "1"){digitalWrite(led2Pin, true);}
    //if(value == "0"){digitalWrite(led2Pin, false);}    
  }
  if(command == "LED3"){
    //if(value == "1"){digitalWrite(led3Pin, true);}
    //if(value == "0"){digitalWrite(led3Pin, false);}    
  }
  if(command == "LED4"){
    //if(value == "1"){digitalWrite(led4Pin, true);}
    //if(value == "0"){digitalWrite(led4Pin, false);}    
  }
  if(command == "BUTTON1"){
    //if(value == "1"){digitalWrite(led4Pin, true);}
    //if(value == "0"){digitalWrite(led4Pin, false);}    
  }
  if(command == "BUTTON2"){
    if(value == "STATUS"){
      Serial.print("BUTTON2:");
      //Serial.println(buttonState2);
    }
  }
}
*/

/*
void serialEvent() {

  //SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  //routine is run between each time loop() runs, so using delay inside loop can
  //delay response. Multiple bytes of data may be available.

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
*/

/*
void receive_serial(void){
  //-------------------------------------
  //-------RECEIVE SERIAL DATA-----------
  //-------------------------------------
  // receive string when completed with \n
  if (stringComplete) {
    //clean input string: remove trailing, terminating characters
    inputString.trim();      
    //Serial.println(inputString);  // echo back received command

    // parse received string into command:value
    rx_command = inputString.substring(0, inputString.indexOf(":"));
    rx_value = inputString.substring(rx_command.length() + 1);

    //Serial.print(rx_command);
    //Serial.print(",");
    //Serial.println(rx_value);
    //-----------check if command is valid---------------
    if((rx_command.length() != 0) and (rx_value.length() != 0)){
      validCommand = true;
    }else{
      validCommand = false;
      Serial.println("syntax error, COMMAND:VALUE");  
    }
    
    //-----------execute requested command---------------
    if(validCommand){
      execute_command(rx_command, rx_value);  
    }
   
    //-----finish and get ready for new input-------------
    inputString = "";
    stringComplete = false;
    validCommand = false;
  }
}
*/