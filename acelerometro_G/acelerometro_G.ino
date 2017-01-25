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
  long xRead = map(analogRead(xPin),minX,maxX,-1000,1000);
  long yRead = map(analogRead(yPin),minY,maxY,-1000,1000);
  long zRead = map(analogRead(zPin),minZ,maxZ,-1000,1000);


  //Output the caculations
  Serial.print(xRead);
  Serial.print(",");
  Serial.print(yRead);
  Serial.print(",");
  Serial.println(zRead);

  delay(100);//just here to slow down the serial output - Easier to read
}
