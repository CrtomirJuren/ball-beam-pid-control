/*
 *
 *
 */

/*** INCLUDES ***/
# include "src\Application.h"         //Application class, it contains all classes

// # include "src\LedBlinker\LedBlinker.h" //LedBlinker class is dependant on Led class
// # include "src\LedBlinker\Led\Led.h"    // no dependancy

// # include "src\PushButton\PushButton.h" // no dependancy
// # include "src\Potentiometer\Potentiometer.h" // no dependancy

// # include "src\SerialManager\SerialManager.h" // no dependancy

/*** DEFINES ***/
// // Led indicators
// # define LED_GREEN_PIN 9
// # define LED_YELLOW_PIN 10
// # define LED_RED_PIN 11

// button
# define BUTTON_PIN 2

// potentiometer
// # define POTENTIOMETER_PIN A0

/*** CLASS CONSTRUCTORS ***/
PushButton button(BUTTON_PIN, 50, BTN_EXT_UP);

// // potentiometer
// Potentiometer potentiometer(POTENTIOMETER_PIN, 88, 1023);

/*** APPLICATION CONSTRUCTOR ***/
Application application(button);


/*** SETUP ***/
void setup() {
  /* initalize serial communication */
  Serial.begin(9600);
  while (!Serial) {
    ; // wait to connect. For native USB port only
  }
  application.setSerial(&Serial);
  
  application.init();
}


/*** MAIN LOOP ***/
void loop(){
  application.update();
}

// #####################################
/*** INCLUDES ***/
// # include "src\Application.h"         //Application class, it contains all classes

// # include "src\LedBlinker\LedBlinker.h" //LedBlinker class is dependant on Led class
// # include "src\LedBlinker\Led\Led.h"    // no dependancy

// # include "src\PushButton\PushButton.h" // no dependancy
// # include "src\Potentiometer\Potentiometer.h" // no dependancy

// # include "src\SerialManager\SerialManager.h" // no dependancy

/*** DEFINES ***/
// // Led indicators
// # define LED_GREEN_PIN 9
// # define LED_YELLOW_PIN 10
// # define LED_RED_PIN 11

// // button
// # define BUTTON_PIN 5

// // potentiometer
// # define POTENTIOMETER_PIN A0

// /*** CLASS CONSTRUCTORS ***/
// // Led Indicators
// Led ledGreen(LED_GREEN_PIN, true);
// Led ledYellow(LED_YELLOW_PIN, true);
// Led ledRed(LED_RED_PIN, true);

// LedBlinker ledBlinkerGreen(ledGreen, 200);

// PushButton button(BUTTON_PIN, 50, BTN_EXT_UP);

// // potentiometer
// Potentiometer potentiometer(POTENTIOMETER_PIN, 88, 1023);

// Application class
// Application application(ledGreen, 
//                         ledYellow,
//                         ledRed,
//                         ledBlinkerGreen,
//                         button,
//                         potentiometer);

// void loop(){
//   trafficLight.update();
// }


// void setup() {
//   /* initalize serial communication */
//   Serial.begin(9600);
//   while (!Serial) {
//     ; // wait to connect. For native USB port only
//   }
//   trafficLight.setSerial(&Serial);
  
//   trafficLight.init();
// }