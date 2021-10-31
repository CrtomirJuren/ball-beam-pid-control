/*
 * PID Voltage Regulator Example. 
 * 
 * See the accompaning circuit in VoltageRegulator.png. 
 * The circuit is a very poor regulator that's complex
 * and nonlinear. A good example to show PID tuning. 
 * 
 * If connected correctly the LED shows the approximate
 * output of the system. The brightness should respond
 * to the dial. Check the serial port to see what the 
 * actual system values are. 
 * 
 ********************************************************/
#include "Adafruit_VL53L0X.h"

#include <MovingAverage.h>
#include <FastPID.h>
#include <Servo.h>

#define PIN_INPUT     A0
#define PIN_SETPOINT  A1
#define PIN_OUTPUT    9

//--------------SERVO VARIABLES------------
int max_servo_angle = 75;
int min_servo_angle = 105;

//----------------------------------------

// PID VARIABLE NAMES 
float pid_pv = 0;         //process variable = distance
float pid_sp = 100;   //setpoint = distance
float pid_mv = 0;         //manipulated variable 0-100% motor angle
float pid_err = 0;      //error = setpoint - process variable

float pid_kp=0.01, pid_ki=0,1, pid_kd=0.001;

float pid_mv_previous; //used in derivate calculation
float proportional, integral, derivate;

uint32_t t_1, t_2, t_delta;
  
int output_bits = 8;
bool output_signed = false;

// This variable just generates input for average test
unsigned delta_x = 0;

int distance = 0;
int distance_avg = 0;

MovingAverage<unsigned> test(8, 0);// Create an Arithmetic Moving Average object of unsigned int type, 10 in size and initialize it with value 2

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

Servo myservo;  // create servo object to control a servo
int servo_angle = 0;    // variable to store the servo position

void setup()
{
  Serial.begin(9600);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {
    Serial.println(F("VL53L0X-Boot-Failed"));
    while(1);
  }

  //-------------SET SERIAL PLOTTER NAMES------------
  Serial.println("sp,pv,err,mv,angle,p,i,d"); 

  // SETUP SERVO MOTOR
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
//------1. GET TIME AT START OF LOOP----------
  t_1 = micros();

//------2. GET CURRENT DISTANCE POSITION = PROCESS VARIABLE------------------
  VL53L0X_RangingMeasurementData_t measure;
          
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    //set max distance
    if(measure.RangeMilliMeter>500)    {
      Serial.println(0);
    }
    else{
        distance = measure.RangeMilliMeter;
        // Pushes the input in the moving average object
        test.push(distance);
        distance_avg = test.get();
    }
  } 
  else{
    //Serial.println(" out of range ");
  }
  
  pid_pv = distance_avg;     
  //---------------------------------------------------------
  // START OF PID CALCULATION, output of PID controller = manipulated variable
  //calculate error
  pid_err = pid_sp - pid_pv;

  //P calculate proportional value
  proportional = pid_err * pid_kp;

  //I calculate integral value
  integral = integral + pid_err;
  integral = integral*pid_ki;

  pid_mv_previous = pid_mv;
  
  //pid_mv = proportional + integral + derivate;
  //pid_mv = proportional;
  pid_mv = integral;

  //D calculate derivate value    return (current_control_output_value - previous_control_output_value) * derivative_gain_value
  derivate = (pid_mv - pid_mv_previous )*pid_kd;

  // TRANSFORM PID MANIPULATED VARIABLE TO SERVO ANGLE, WITH MAX-MIN LIMITS
  servo_angle = map(pid_mv, 0, 100, max_servo_angle, min_servo_angle);
  /*
  if(servo_angle > max_servo_angle){
    servo_angle = max_servo_angle;
  }
  if(servo_angle < min_servo_angle){
    servo_angle = min_servo_angle;
  }
  */
    myservo.write(servo_angle);              // tell servo to go to position in variable 'pos'
  
  //LOOP TIME 100Hz
  delay(10);
  //-----------GET TIME AT END OF PID LOOP----------------------
  t_2 = micros();
  t_delta = t_2 - t_1;
  //------------SHOW EVERYTHING ON SERIAL PLOTTER--------------------------------------------

  //this is the oblika za arduino serial plotter
  //Serial.println(measure.RangeMilliMeter); //  
  //Serial.print(t_delta); //
  //Serial.print(","); //    
  Serial.print(pid_sp); //  
  Serial.print(","); //
  Serial.print(pid_pv); //
  Serial.print(","); //
  Serial.print(pid_err); //
  Serial.print(","); //
  Serial.print(pid_mv); //
  Serial.print(","); //
  Serial.print(servo_angle); //
  Serial.print(","); //
  Serial.print(proportional); //
  Serial.print(","); //
  Serial.print(integral); //
  Serial.print(","); //
  Serial.print(derivate); //
  Serial.println(); //

}
