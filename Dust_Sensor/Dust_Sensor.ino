/*
 Interface to Sharp GP2Y1010AU0F Particle Sensor
 Program by Christopher Nafis 
 Written April 2012
 
 http://www.sparkfun.com/datasheets/Sensors/gp2y1010au_e.pdf
 http://sensorapp.net/?p=479
 
 Sharp pin 1 (V-LED)   => 5V (connected to 150ohm resister)
 Sharp pin 2 (LED-GND) => Arduino GND pin
 Sharp pin 3 (LED)     => Arduino pin 8
 Sharp pin 4 (S-GND)   => Arduino GND pin
 Sharp pin 5 (Vo)      => Arduino A0 pin
 Sharp pin 6 (Vcc)     => 5V
 */
int dustPin=A1;
int ledPower=8;
int delayTime=280;
int delayTime2=40;
float offTime=9680;

int dustVal=0;
float ppm=0;
char s[32];
float voltage = 0;
float dustdensity = 0;
float ppmpercf = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  ppm =0;
}

void loop(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime);
  dustVal=analogRead(dustPin); // read the dust value
  ppm = ppm+dustVal;
  delayMicroseconds(delayTime2);
  Serial.println(ppm);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);
  ppm=0;
  delay(200);
}



















