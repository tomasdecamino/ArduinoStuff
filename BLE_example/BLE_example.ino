#include <SoftwareSerial.h>  //Include the Soft Serial Library
 
int ledPin = 13;
 
void setup() {
  Serial.begin(9600);  // start serial communication at 9600bps
  pinMode(ledPin, OUTPUT);
}
 
void loop() {
  if( Serial.available() ) {  // if data is available to read
    char data= Serial.read();
    Serial.println(data);
    if( data == 200)  //Check for capital H
      digitalWrite(ledPin, HIGH);  
    else
      digitalWrite(ledPin, LOW);
  }
}
