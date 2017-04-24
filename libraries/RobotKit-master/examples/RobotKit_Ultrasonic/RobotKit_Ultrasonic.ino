/* @author: Alex Roberto Vargas Benamburg
 * August 2016
 * www.funcostarica.org

Made for teaching poruposes www.funcostarica.org
Released under MIT License
Copyright (c) 2016  Alex Roberto Vargas Benamburg (vbalex.com)
 */

#include <RobotKit.h>

const int triggerPin = 3; // it can be any pin
const int echoPin = 2;    // On Duemilanove use only 2 or 3 digital pin, more information: https://www.arduino.cc/en/Reference/AttachInterrupt

void setup() {
  Serial.begin(19200);
  startUltrasonic(triggerPin,echoPin); //start the ultrasonic sensor
}

void loop() {
  float distance = getUltrasonic(); //Get the distance in centimeters
  Serial.println(distance); // print in Serial Monitor or Serial Ploter
  delay(250); // delay 1/4 of seconds
  updateUtrasonic();//Request update ultrasonic valuea
}
