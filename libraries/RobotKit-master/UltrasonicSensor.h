/* @author: Alex Roberto Vargas Benamburg
 * August 2016
 * www.funcostarica.org

Made for teaching poruposes www.funcostarica.org
Released under MIT License
Copyright (c) 2016  Alex Roberto Vargas Benamburg (vbalex.com)
 */

uint8_t ultrasonictriggerPin;
uint32_t ultrasonicTime;
uint32_t ultrasonicCounter;

//Functions for ultrasonic range sensor
void updateUtrasonic(){
  digitalWrite(ultrasonictriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonictriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonictriggerPin, LOW);
  ultrasonicCounter = micros();
}

void triggerUltrasonic(){
  ultrasonicTime = micros()-ultrasonicCounter;
}

void startUltrasonic(uint8_t tPin, uint8_t ePin){
  ultrasonictriggerPin = tPin;
  pinMode(ultrasonictriggerPin,OUTPUT);
  pinMode(ePin,INPUT);
  attachInterrupt(digitalPinToInterrupt(ePin), triggerUltrasonic, CHANGE);
  updateUtrasonic();
}

float getUltrasonic(){
  return ultrasonicTime/58.0;
}
