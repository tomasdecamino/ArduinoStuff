/*Light gradient detector
  Tomas de-Camino-Beck

detects de direction of the dark/brigth side
using 4 photoresistors
configured in a square, 
top:    A1, A3
bottom: A0, A2
 */

#include <math.h>



int s1,s2,s3,s4;

int min = 1023;
int max = 0;
int switchState = 0;

float dx = 0;
float dy = 0;

void setup()
{
  Serial.begin(9600);
  //push button for calibration
  pinMode(8,INPUT);
}


void loop(){
  switchState = digitalRead(8);
  //if(switchState==0){
    //get the readings
    s1 = getValue(A0);
    s2 = getValue(A1);
    s3 = getValue(A2);
    s4 = getValue(A3);
    //calculate x and y direction gradients
    dx = s4 - s3 + 0.5*(s3 - s4 + s2 - s1);
    dy = s1 - s3 + 0.5*(s3 - s4 + s2 - s1);
    //Calculation of magnitude and angle to send over serial
    //magnitude
    Serial.print(sqrt(square(dx)+square(dy)));
    Serial.print(",");
    //angle in radians
    //To point to light
    //Serial.println(atan2(dx,dy)+PI);
    //To point to shadow
    Serial.println(atan2(dx,dy));
 // } 
  //calibrate light conditions pressing the button
  //send 0s in the meantime 
 // else {
  //  calibrate();
  //  Serial.println("0,0");
  //}
  delay(50);


}

//Calibrate light conditions using A0 and A3
//Press the button an cover sensor A3
void calibrate(){
  int l0 =analogRead(A0);
  int l1 =analogRead(A3);
  if(l0>max){
    max = l0; 
  }
  if(l1<min){
    min = l1; 
  }
}

//function that maps to a more stable scale
int getValue(int pin){
  int val = analogRead(pin);
  val = map(val,min,max,0,255);
  val =  constrain(val,0,255);
  return(val);
}




