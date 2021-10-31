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
MovingAverage<unsigned> moving_avg_array(8, 100);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//MAIN PID PROCESS VARIABLES
float pid_pv_nofilter = 0;              //noisy process variable = distance[mm]
float pid_pv_filter = 0;              //filtered process variable = distance[mm]
float pid_sp = 100;            //setpoint = distance[mm]
float pid_mv = 0;              //manipulated variable -100 < mv < -100%
float pid_err = 0;             //error = setpoint - process variable

int distance = 0;

void initialize_serial(void);
void send_serial(void);

void setup() {
  initialize_serial();
  
  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X");
    while(1);
  }
}

void loop() {

  //-------------------------------------
  //-----------GET DISTANCES-------------
  //filter and set pid process variable
  //-------------------------------------
  
  // read distance from sensor VL53L0X
  distance = get_distance();
  
  //add value to moving avarage
  moving_avg_array.push(distance);
  
  pid_pv_nofilter = distance;
  
  //read avarage of moving avarage array
  pid_pv_filter = moving_avg_array.get();
        
  pid_err = pid_sp - pid_pv_filter;
  
  //-------------------------------------
  //--------SEND DATA OVER SERIAL--------
  //-------------------------------------
  send_serial();

  //-------------------------------------
  //-----------LOOP TIME DELAY-----------
  //-------------------------------------
  delay(5);
}

/*************************************
    Returns distance measured from sensor VL53L0X
    @void
    @return distance[mm]
**************************************/
int get_distance(void){
  bool measurement_success;

  // read measurement
  VL53L0X_RangingMeasurementData_t measure;
            
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
  // CHECK FOR MEASUREMENT PHASE ERROR
  if(measure.RangeStatus != 4){  // phase failures have incorrect data
    measurement_success = true;
  }
  else{
    measurement_success = false;
  }
  
  // IF MEASUREMENT OK, READ DISTANCE
  if(measurement_success){
    distance = measure.RangeMilliMeter;
  
    //check if distance is over maximum
    if(distance > 300){
      distance = 300;
      //for debbuging, send 
      //Serial.print("max-distance-error");
    }
    return distance; 
  }
  // IF MEASUREMENT NOK, SKIP MEASUREMENT
  else{
  }
}

/*************************************

**************************************/
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

/*************************************

**************************************/
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
