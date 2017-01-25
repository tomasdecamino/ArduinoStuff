/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

int m = 0;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  speed(70);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  speed(m);
  if (Serial.available())
    m = Serial.parseInt();
  delay(1000);

}

void speed(int s) {
  int maxspeed = map(s, 0, 100, 0, 180);
  for (pos = 0; pos <= maxspeed; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }

}

