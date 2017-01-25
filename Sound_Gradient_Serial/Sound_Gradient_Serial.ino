/*Light gradient detector
  Tomas de-Camino-Beck

  detects de direction of the dark/brigth side
  using 4 photoresistors
  configured in a square,
  top:    A1, A3
  bottom: A0, A2
*/

#define MINA0 127
#define MINA1 127
#define MINA2 127
#define MINA3 127

#include <math.h>
long s1, s2, s3, s4;

float dx = 0;
float dy = 0;

void setup()
{
  Serial.begin(9600);
  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;
}

void loop() {
  for (int i = 0; i < 200; i++) {
    s1 += vol(A0, MINA0);
    s2 += vol(A1, MINA1);
    s3 += vol(A2, MINA2);
    s4 += vol(A3, MINA3);
  }

  //calculate x and y direction gradients
  dx = s4 - s3 + 0.5 * (s3 - s4 + s2 - s1);
  dy = s1 - s3 + 0.5 * (s3 - s4 + s2 - s1);
  //Calculation of magnitude and angle to send over serial
  //magnitude
      Serial.print(sqrt(square(dx) + square(dy)));
      Serial.print(",");
      //angle in radians
      //To point to light
      Serial.println(atan2(dx, dy) + PI);

  //uncommnet for mic test
//  Serial.print(s1);
//  Serial.print(",");
//  Serial.print(s2);
//  Serial.print(",");
//  Serial.print(s3);
//  Serial.print(",");
//  Serial.println(s4);

  //uncommnet for mic test
//  Serial.print(analogRead(A0));
//  Serial.print(",");
//  Serial.print(analogRead(A1));
//  Serial.print(",");
//  Serial.print(analogRead(A2));
//  Serial.print(",");
//  Serial.println(analogRead(A3));



  s1 = 0;
  s2 = 0;
  s3 = 0;
  s4 = 0;

}

int vol(int pin, int m) {
  int val = analogRead(pin)-m ;
  return (abs(val)>3)?1:0;
}




