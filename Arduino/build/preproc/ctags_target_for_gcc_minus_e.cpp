# 1 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino"
/*

 * PID Ball Beam Project 

 * 

 * version 5

 * 

 * PV(process variable): current ball position

 * SP(setpoint): desired ball position

 */
# 10 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino"
//-----------------------------------------------------
//--------LIBRARIES, INCLUDES, HEADERS-----------------
//-----------------------------------------------------
# 14 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2

# 16 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
//#include <FastPID.h>
//#include <Servo.h>

# 20 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 21 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 22 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 23 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 24 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 25 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2
# 26 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino" 2

//-----------------------------------------------------
//-------------------DEFINES---------------------------
//-----------------------------------------------------




//-----------------------------------------------------
//---------------GLOBAL VARIABLES----------------------
//-----------------------------------------------------
//--------MAIN PROCESS VARIABLES-------------------
float position_sp = 150; //setpoint = distance[mm]
float pid_mv = 0; //manipulated variable -100 < mv < -100%

bool output_signed = false;

float ball_pos = 0;
float ball_pos_avg = 0;

//----------------------SERVO--------------------------
// const int servo_motor_pin = 9;
int servo_angle = 0; // variable to store the servo position
int angle_limit = 45; //limits relative to beam cca +/-30 degrees
int servo_offset = 91; //horizontal beam position is angle 0
int servo_sp; // variable to store the servo position


//-----------------------------------------------------
//------------OBJECTS INITIALIZATION-------------------
//-----------------------------------------------------
// moving avarage, length = 8 samples, start value = 
MovingAverage<unsigned> moving_avg_array(8, position_sp); // length 8 samples

/* Create Laser distance sensor Object: */
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

/* Create servo motor Object: */
Servo myservo;

Led led(2);
Led led_pcb(13);

Button button(5);

// initailize PID controller
Pid myPid(0.5, 0.05, 5);

//-----------------------------------------------------
//----------------SETUP LOOP---------------------------
//-----------------------------------------------------
void setup()
{
  //initialize serial communication
  initialize_serial();

  // reserve 200 bytes for the inputString:
  //inputString.reserve(200);

  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X");
    while(1);
  }

  //attaches the servo on pin 9 to the servo object
  myservo.attach(9);

  myPid.setSetpoint(position_sp); // [mm] 

  led.on();
  led_pcb.on();
  delayMicroseconds(200);
  led.off();
  led_pcb.off();
  delayMicroseconds(200);
  led.on();
  led_pcb.on();
}

//-----------------------------------------------------
//-----------------MAIN LOOP---------------------------
//-----------------------------------------------------
void loop()
{
  //--------GET SENSOR INPUT-------------
  // get distance from sensor VL53L0X
  ball_pos = get_distance();

  // position rolling avarage
  moving_avg_array.push(ball_pos);
  ball_pos_avg = moving_avg_array.get();

  // PID Calculation
  pid_mv = myPid.calculate(ball_pos_avg);

  //------UPDATE ACTUATOR OUTPUTS--------
  set_servo_position(pid_mv);

  //--------SEND DATA OVER SERIAL--------
  send_serial();

  //-----------LOOP TIME DELAY-----------
  delay(1);
}

void send_serial(void){
  // requested position
  Serial.print(position_sp); //  
  Serial.print(","); //

  //arduino serial plotter mode
  //Serial.print(ball_pos); //  
  //Serial.print(","); //
  //Serial.print(ball_pos_avg); //  
  //Serial.print(","); //
  //Serial.print(pid_pv_filter); //  
  //Serial.print(","); //
  //Serial.println(pid_err); //

  //Serial.print(myPid.PV); //  
  //Serial.print(","); //
  //Serial.print(pid_mv); //  
  //Serial.print(","); //
  //Serial.print(pid_pv_nofilter); //  
  //Serial.print(","); //
  //Serial.print(pid_pv_filter); //  
  //Serial.print(","); //
  //Serial.println(pid_err); //
  Serial.println(); //
}

/*************************************ss

    Returns distance measured from sensor VL53L0X

    @void

    @return distance[mm]

**************************************/
# 163 "c:\\Users\\crtom\\Documents\\ball-beam-project.git\\Arduino\\5-pid-v4\\5-pid-v4.ino"
int get_distance(void){
  // local variables
  bool measurement_success;
  float distance;

  // read measurement
  VL53L0X_RangingMeasurementData_t measure;

  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  // CHECK FOR MEASUREMENT PHASE ERROR
  if(measure.RangeStatus != 4){ // phase failures have incorrect data
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

void set_servo_position(int manipulated_variable){
  // constrain motor output
  servo_sp = map(manipulated_variable, -100, 100, servo_offset - angle_limit, servo_offset + angle_limit);

  //constraint the values for motor and system safety
  servo_sp = ((servo_sp)<(servo_offset - angle_limit)?(servo_offset - angle_limit):((servo_sp)>(servo_offset + angle_limit)?(servo_offset + angle_limit):(servo_sp)));

  //set_servo_position(servo_sp);
  myservo.write(servo_sp);
}
