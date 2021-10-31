# BALL AND BEAM PROJECT

Hardware, Software, Simulation for Ball Beam PID Control. FreeCAD, Arduino, Python, Jupyter, Binder




nastavljanje servo motorja

- servo motor ima možnost gibanja med 0 in 180°

- servo motor je nastavljen, da ima 90° za izhodiščno točko. to pa zato, ker bo krmiljen v + in v -. Zato ne sme biti na 0°. ker potem, če bi mu ukazali, premakni se v minus. se ne bi mogle.
- napiše se funkcija, da bo imel gibanje med -20° < angle < +20°



## DVE VERZIJI PROGRAMA - pid preko labview

labview prejme podatke senzorjev - preračuna pid in vrne nazaj pozicijo servota

vse narejeno na arduino. labview prikazuje podatke in lahko spreminja kp,ki,kd parametre



## ARDUINO CODE

- #include "Adafruit_VL53L0X.h"

  PROGRAMSKE SPECIFIKACIJE ZA KNJIžNJICO https://documentation.help/VL53L0X-API/index.html

  

- Using Serial Monitor to Control Servo Motor

- moving avarage library

- arduino library: FastPID - A fast 32-bit fixed-point PID controller for Arduino

  https://github.com/mike-matera/FastPID

  ### Moving avarage library example 

  ```
  // Include lib:
  #include <MovingAverage.h>
  
  // Create an Arithmetic Moving Average object of unsigned int type,
  // 10 in size
  // and initialize it with value 2
  MovingAverage<unsigned> test(10, 2);
  
  // This variable just generates input for average test
  unsigned delta_x = 0;
  
  void setup() {
    // Initialize serial interface
    Serial.begin(9600);
  }
  
  void loop() {
    // Pushes the input in the moving average object
    test.push(delta_x);
  
    // Generates the next input
    delta_x += 5;
    if (delta_x > 1000) delta_x = 0;
  
    // Prints each value stored in the moving average
    for (uint8_t i = 0; i < test.size(); i++) {
      Serial.print(test[i]);
      Serial.print(" ");
    }
    // Prints the result of the average
    Serial.print("= ");
    Serial.print(test.get());
    // Prints the value stored in the first and last indexes
    Serial.print(" | f: ");
    Serial.print(test.front());
    Serial.print(" b: ");
    Serial.println(test.back());
  
    delay(1000);
  }
  ```

  

### Reading Distance: Sensor VL53L0X - OK

- code

[arduino code](arduino-code\reading-dist-VL53L0X-v1\reading-dist-VL53L0X-v1.ino)



### Reading distance and smoothing avarage

