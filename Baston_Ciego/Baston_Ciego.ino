// initialize
int PingPin = 7 ;          // pin used for the Ping Sensor
int BaudRate = 9600 ;      // Baud rate
unsigned long d=0; 
 
// set up
void setup() {
  Serial.begin(BaudRate) ; // Setup Serial
  pinMode(11,OUTPUT);
}
 
void loop() {
  pinMode(PingPin, OUTPUT)    ;
  digitalWrite(PingPin, LOW)  ;  // init sensor to ensure clean HIGH pulse
  delayMicroseconds(2)        ;  
  digitalWrite(PingPin, HIGH) ;  // make the sensor send a pulse 
  delayMicroseconds(5)        ;  
  digitalWrite(PingPin, LOW)  ;  // Set LOW again
  pinMode(PingPin, INPUT)     ;  // Get ready to capture the duration of the resulting pulse
  // Capture how long the pin stays in HIGH state.
  unsigned long Duration = pulseIn(PingPin, HIGH) ;  
  if (Duration == 0) {
    Serial.println ("No Pulse received from the sensor") ;
  }
  else
  {
    d = Convert_Time_Space(Duration);
    Serial.print ("Distance : ") ;
    Serial.print(d) ;  // convert the duration into distance
    Serial.println (" cm"); 
    if(d<50){
      analogWrite(11,150); 
    }else{
     analogWrite(11,0); 
    }
  }
  delay (100) ;  
}
 
unsigned long Convert_Time_Space(const unsigned long fnDuration )
{
  // This function could be more precise by using floats
  // and taking into account temperature and humidity
  // I used 29 microseconds per cm. 
  return fnDuration / 29 / 2 ;
}
