/*
  Serial Event Arduino code Template example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  created 26 May 2020
  by Črtomir Juren

RECEIVE AND PARSE SERIAL COMMAND
oblika:    COMMAND:TYPE:VALUE\n
types:     type_bool, type_int, type_float, type_string
example:   LED1:int:1\n

DO NOT FORGET, COMMAND MUST HAVE NEW LINE
*/
// serial event variables
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

// valid comand parsing variables
bool validCommand = false;
String rx_command;
String rx_type;
String rx_value;
String parsingString = "";

//IO variables
const int ledbuiltinPin =  LED_BUILTIN;// the number of the LED pin

//if received existing command, send back blink
void valid_command_blink(void){
  digitalWrite(ledbuiltinPin, HIGH);
  delay(50);
  digitalWrite(ledbuiltinPin, LOW);
}

//--------------SETUP------------------
void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Arduino ready");
  // reserve 200 bytes for the inputString:
  inputString.reserve(500);
  
  pinMode(ledbuiltinPin, OUTPUT);
}

//-----------MAIN LOOP-----------------
void loop() {
  // receive string when completed with \n
  if (stringComplete) {
    //clean input string: remove trailing, terminating characters
    inputString.trim();      

    //Start string parsing to get COMMAND:TYPE:VALUE\n
    parsingString = inputString;
    
    // parse COMMAND
    rx_command = parsingString.substring(0,  parsingString.indexOf(":"));
    //shrani ostanek
    parsingString =  parsingString.substring(rx_command.length() + 1);
        
    // parse TYPE
    rx_type = parsingString.substring(0,  parsingString.indexOf(":"));
    //shrani ostanek
    parsingString =  parsingString.substring(rx_type.length() + 1);
    
    // parse VALUE
    rx_value =  parsingString;

  /* DEBUG
    Serial.print("parsed result: ");
    Serial.print(rx_command);
    Serial.print(",");
    Serial.print(rx_type);
    Serial.print(",");
    Serial.println(rx_value);
  */
    //-----------check if command is valid---------------
    if((rx_command.length() != 0) and (rx_value.length() != 0) and (rx_type.length() != 0)){
      validCommand = true;
    }else{
      validCommand = false;
//DEBUG Serial.println("syntax error, COMMAND:TYPE:VALUE, setpoint:type_float:1.01");  
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

/*
  execute_command: all commands that arduino executes are listed here
*/
void execute_command(String command, String value){
  if(command == "LED1"){
   
  }
  if(command == "LED2"){
   
  }
  if(command == "LED3"){
  
  }
  if(command == "LED4"){
 
  }
  if(command == "BUTTON1"){
  
  }
  if(command == "BUTTON2"){

    }
  }


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
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
