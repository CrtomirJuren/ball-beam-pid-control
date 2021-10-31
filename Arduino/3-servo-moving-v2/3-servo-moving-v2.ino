/* Sweep
 by Črtomir Juren 7-11-2020


 
VALUES ARE BEING CHANGE RELATIVE TO MOTOR OR BEAM COORDINATION SYSTEM

******* POINT OF THIS CODE, solving a problem  *************
  - pid manipulated output is in percantage -100% < pid_mv < 100%
  - motor has a different coordiantion than beam
  - i need to calculate conenction between pid_mv and servo motor angle
  
Values are calculated and processed in following order
 1. INPUT IS pid_mv
 2. OUTPUT IS motor setting position
 
 1. motor_setpoint
 2. motor_offset
 3. motor_limited
 
*/

#include <Servo.h>

//-----------------------------------------------------
//---------------GLOBAL VARIABLES----------------------
//-----------------------------------------------------

//MAIN PID PROCESS VARIABLES
//float pid_pv = 0;                     //process variable = distance
//float pid_sp = 100;                   //setpoint = distance
float pid_mv = 0;                     //manipulated variable 0-100% motor angle
//float pid_err = 0;                    //error = setpoint - process variable

const int servo_motor_pin = 9;
int angle_limit = 30;                 //limits relative to beam cca +/-30 degrees
int servo_offset = 91;                //horizontal beam position is angle 0

int servo_sp;                        // variable to store the servo position
//int servo_sp; 

int delay_time = 100;

Servo myservo;                        // create servo object to control a servo

void setup() {
  initialize_serial();
  
  myservo.attach(servo_motor_pin);    // attaches the servo on pin 9 to the servo object
}

void loop() {
  
  // set relative position: input in range (-15deg < angle < +15deg)
  //set_servo_position(0);
  //myservo.write(60);  

  //if pid_mv < 0, motor angle > 90, ball will accelerate towards sensor
  //if pid_mv =0,  motor angle = 90, ball will not accelerate
  //if pid_mv > 0, motor angle < 90, ball will accelerate away from sensor
  pid_mv = 0; // -100% < pid_mv< 100%

  set_servo_position(pid_mv); 

  // Send data to arduino plotter
  send_serial();
}


void set_servo_position(int manipulated_variable){
  // constrain motor output
  servo_sp = map(manipulated_variable, -100, 100, servo_offset - angle_limit, servo_offset + angle_limit);

  //constraint the values for motor and system safety
  servo_sp = constrain(servo_sp, servo_offset - angle_limit, servo_offset + angle_limit); 
  //set_servo_position(servo_sp);
  myservo.write(servo_sp);               
}

void initialize_serial(void){
  // set serial speed
  Serial.begin(9600);
  // wait until serial port opens
  while (! Serial) {
    delay(1);
  }
  //------SET ARDUINO SERIAL PLOTTER NAMES------------
  Serial.println("motor_setpoint,motor_offseted,motor_limited");   
}

void send_serial(void){
  //arduino serial plotter mode
  Serial.print(pid_mv); //  
  Serial.print(","); //
  Serial.println(servo_sp); //
}
