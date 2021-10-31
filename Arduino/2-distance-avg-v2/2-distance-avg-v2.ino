/*
 * 
 * 3,3V = rdeča
 * gnd = črna
 * SDA = modra
 * SCL = rumena
 * 
 */

// Include lib:
#include "Adafruit_VL53L0X.h"
#include <MovingAverage.h>

// Create an Arithmetic Moving Average object of unsigned int type,
// 10 in size and initialize it with value 2
MovingAverage<unsigned> distance_array(8, 0);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//MAIN PID PROCESS VARIABLES
float pid_pv_nofilter = 0;              //noisy process variable = distance[mm]
float pid_pv_filter = 0;              //filtered process variable = distance[mm]
float pid_sp = 100;            //setpoint = distance[mm]
float pid_mv = 0;              //manipulated variable -100 < mv < -100%
float pid_err = 0;             //error = setpoint - process variable

int distance = 0;

void setup() {
  initialize_serial();
  
  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println("Signal[mm]"); 
  //Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void loop() {
  
  VL53L0X_RangingMeasurementData_t measure;
          
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data

    //set min distance
    
    //set max distance
    if(measure.RangeMilliMeter>500){
      Serial.println(0);
    }
    else{
        distance = measure.RangeMilliMeter;
        // Pushes the input in the moving average object

        //add value to moving avarage
        distance_array.push(distance);

        pid_pv_nofilter = distance;
        pid_pv_filter = distance_array.get();

   }

  } else {
    //Serial.println(" out of range ");
  }

  pid_err = pid_sp - pid_pv_filter;
  send_serial();
  delay(5);
}
  
void initialize_serial(void){
  // set serial speed
  Serial.begin(9600);
  // wait until serial port opens
  while (! Serial) {
    delay(1);
  }
  //------SET ARDUINO SERIAL PLOTTER NAMES------------
  Serial.println("sp,pv_nofilter,pv_filter,err");   
}

void send_serial(void){
  //arduino serial plotter mode
  Serial.print(pid_sp); //  
  Serial.print(","); //
  Serial.print(pid_pv_nofilter); //  
  Serial.print(","); //
  Serial.print(pid_pv_filter); //  
  Serial.print(","); //
  Serial.println(pid_err); //
}
