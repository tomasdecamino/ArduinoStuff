#include <SoftwareSerial.h>  //Include the Soft Serial Library
 
int ledPin = 13;
SoftwareSerial BTSerial(2, 3);  // RX, TX
 
void setup() {
  Serial.begin(9600);  // start serial communication at 9600bps
  BTSerial.begin(9600);  //Start Bluetooth Serial Connection
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); 
  delay(1000);
  digitalWrite(ledPin, LOW); 
  BTSerial.write("test");
}
 
void loop() {
  if( BTSerial.available() ) {  // if data is available to read
    Serial.println("datos");
    if( BTSerial.read() == 200)  //Check for capital H
      digitalWrite(ledPin, HIGH);  
    else
      digitalWrite(ledPin, LOW);
  }
}
