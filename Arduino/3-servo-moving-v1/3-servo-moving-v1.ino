/* Sweep
 by Črtomir Juren 7-11-2020
*/
#include <Servo.h>

const int servo_motor_pin = 9;
int angle_limit = 30;                 //limits relative to beam cca +/-30 degrees
int servo_offset = 91;                //horizontal beam position is angle 0
int servo_sp = 0;                     // variable to store the servo position
int delay_time = 100;

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(servo_motor_pin);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  // 1. start at beam horizontal position
  int servo_sp = servo_offset;   
  
  for (servo_sp = servo_offset+angle_limit; servo_sp <= servo_offset-angle_limit; servo_sp += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(servo_sp);              // tell servo to go to position in variable 'pos'
    delay(delay_time);                       // waits 15ms for the servo to reach the position
  }
  for (servo_sp = servo_offset-angle_limit; servo_sp >= servo_offset-angle_limit; servo_sp -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(servo_sp);              // tell servo to go to position in variable 'pos'
    delay(delay_time);                       // waits 15ms for the servo to reach the position
  }
}
