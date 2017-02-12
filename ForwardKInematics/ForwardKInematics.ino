//Tomas de Camino Beck
// www.funcostarica.org

#include <math.h>

// length of arm1 and amr2 length
#define ARM1 11.5
#define ARM2 12

//90 degree calibration
#define A1_90 660
#define A2_90 361

void setup() {
  //set pins A0  base potentiometer
  //A1 elbow potentiometer
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // get readings from pots
  // calibrate with pot reading at 90 degrees

  //base pot
  int val1 = analogRead(A0);
  int angle1 = map(val1, A1_90, 1022, 90, 0);

  //elbow pot
  int val2 = analogRead(A1);
  int angle2 = map(val2, 0, A2_90, 0, 90);

  //get distance from origin and angle
  //remember we have to convert to radians
  float c = getSide(ARM1,ARM2,PI-angle2*(PI/180));
  float beta = getAngle(ARM1,ARM2,c);

  //get coordinates x,y
  float x = c*cos(beta+(angle1*PI/180));
  float y = c*sin(beta+(angle1*PI/180));
  
  //calibration to serial (uncomment for calibration)
  //Serial.print(val1);
  //Serial.print(",");
  //Serial.print(angle1);
  //Serial.print(",");
  //Serial.print(val2);
  //Serial.print(",");
  //Serial.println(angle2);
  
  //coordinates to serial (comment for cailbration)
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);


}

//*********law of cosines***********
//get the angle knowing 3 sides
float getAngle(float a, float b, float c){
  return acos((sq(a)+sq(c)-sq(b))/(2*a*c));
}

//get one side knowing two sides and opposite angle
float getSide(float a, float b, float ang){
  return sqrt(sq(a)+sq(b)-2*a*b*cos(ang));
}

