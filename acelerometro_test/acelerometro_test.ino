//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the ADXL335, prints calculated orientation via serial
//////////////////////////////////////////////////////////////////


//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minX = 267;
int maxX = 404;
int minY = 268;
int maxY = 404;
int minZ = 264;
int maxZ = 398;


//to hold the caculated values
double x;
double y;
double z;


void setup(){
  Serial.begin(9600); 
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}


void loop(){

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minX, maxX, -90, 90);
  int yAng = map(yRead, minY, maxY, -90, 90);
  int zAng = map(zRead, minZ, maxZ, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  //Output the caculations
  Serial.print(xAng*DEG_TO_RAD);
  Serial.print(",");
  Serial.print(yAng*DEG_TO_RAD);
  Serial.print(",");
  Serial.println(zAng*DEG_TO_RAD);

  delay(100);//just here to slow down the serial output - Easier to read
}
