
/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo s1, s2, s3; // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  pinMode(A0, INPUT);
}

void loop() {
  val = analogRead(A0);
  val = map(val, 0, 1023, 180, 0);     // scale it to use it with the servo (value between 0 and 180)
  s1.write(val);
  s2.write(180-val);
  s3.write(val);
  delay(15);                           // waits for the servo to get there
}

