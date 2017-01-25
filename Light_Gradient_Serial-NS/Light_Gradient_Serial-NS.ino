/*Light gradient detector
  Tomas de-Camino-Beck

detects de direction of the dark/brigth side
using 4 photoresistors
configured in a square,
top:    A1, A3
bottom: A0, A2
 */

#include <math.h>
int s1, s2, s3, s4;

float dx = 0;
float dy = 0;

void setup()
{
  Serial.begin(9600);

}

void loop() {
  s1 = getValue(A0);
  s2 = getValue(A1);
  s3 = getValue(A2);
  s4 = getValue(A3);
  //calculate x and y direction gradients
  dx = s4 - s3 + 0.5 * (s3 - s4 + s2 - s1);
  dy = s1 - s3 + 0.5 * (s3 - s4 + s2 - s1);
  //Calculation of magnitude and angle to send over serial
  //magnitude
  Serial.print(sqrt(square(dx) + square(dy)));
  Serial.print(",");
  //angle in radians
  //To point to light
  Serial.println(atan2(dx,dy)+PI);
  delay(50);

}




