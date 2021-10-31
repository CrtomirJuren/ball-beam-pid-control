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
MovingAverage<unsigned> test(8, 0);

// This variable just generates input for average test
unsigned delta_x = 0;

int distance = 0;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
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

    //set max distance
    if(measure.RangeMilliMeter>500){
      Serial.println(0);
    }
    else{
        distance = measure.RangeMilliMeter;
        // Pushes the input in the moving average object
        test.push(distance);

        //this is the oblika za arduino serial plotter
        //Serial.println(measure.RangeMilliMeter); //  
        Serial.print(distance); //
        Serial.print(","); //
        Serial.println(test.get()); //  
   }

  } else {
    //Serial.println(" out of range ");
  }
    
  delay(5);
}
