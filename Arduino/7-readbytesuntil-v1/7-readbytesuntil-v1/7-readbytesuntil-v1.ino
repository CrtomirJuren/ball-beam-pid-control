
//--------------VARIABLES------------------
char messageBuffer[5];
size_t bytesReceived;

//--------------FUNCTIONS------------------
void init_serial(void){
  Serial.begin(9600);
}

void init_io(void){
  //initialize IO
  pinMode(LED_BUILTIN, OUTPUT);
}

void run_state(void){

  if (Serial.available() > 0) {
    bytesReceived = Serial.readBytesUntil('\n', messageBuffer,10);
    if(bytesReceived > 0){
      Serial.print("bytes received:");
      Serial.println(messageBuffer);

      //clear buffer array, get it ready for next msg
      memset(0, messageBuffer, sizeof(messageBuffer));
      }
  }
  delay(100);  
}
//--------------SETUP------------------
void setup() {
  // initialize IO
  init_io();
  // initialize serial:
  init_serial();
}
//--------------LOOP------------------
void loop() {
  run_state();
}
