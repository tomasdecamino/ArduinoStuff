/* @author: Tomas de Camino Beck
   August 2016
   www.funcostarica.org

  Made for teaching poruposes www.funcostarica.org
  Released under MIT License
  Copyright (c) 2016  Alex Roberto Vargas Benamburg (vbalex.com)
*/

#include <RobotKit.h>
void setup() {
  setMotors();
  Serial.begin(9600);
  setSensor(4);
  startUltrasonic(3, 2); //trig, echo//start the ultrasonic sensor
}

void loop() {
  float distance = getDistance();
  Serial.print(distance); // print in Serial Monitor or Serial Ploter
  Serial.print(",");
  Serial.println(digitalRead(4));
  if(distance<50){
    stopMotors();
    randomPivot(200,500);
  }
  forward(150,300);
}
