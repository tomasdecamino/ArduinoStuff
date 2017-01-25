#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

uint8_t servonum = 0;

long lastMillis;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pinMode(A0,INPUT);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!

void loop() {
  // Drive each servo one at a time
  //Serial.println(servonum);
  lastMillis=millis();
  while(millis()-lastMillis<120000){
    Serial.println(digitalRead(A0));
    if(digitalRead(A0)){
      moveWings(); 
    }
  }
}

//degrees to pulses
void moveDegree(int s, int deg){
  int pulselength = map(deg, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(s, 0, pulselength);
}

double delayNormal(int x,float m, float sigma){
  double res=m*(90-(1/(sigma*sqrt(2*PI))*exp(-sq(x-m)/(2*sq(sigma)))));
  return res;
}

void moveWings(){
  for (uint16_t deg = 0; deg < 180; deg++) {
    moveDegree(0, 180 - deg);
    moveDegree(1, deg / 2);
    moveDegree(2, deg);
    moveDegree(3, 90 - deg / 2);
    delay(1 + sq(deg - 90) / 80);
    //Serial.println(deg);
  }
  delay(1000);
  for (uint16_t deg = 90; deg >= 30; deg--) {
     moveDegree(4, deg);
     delay( sq(deg - 90) / 90);
   }
   for (uint16_t deg = 30; deg <= 150; deg++) {
     moveDegree(4, deg);
     delay( sq(deg - 90) / 90);
   }
   for (uint16_t deg = 150; deg >= 90; deg--) {
     moveDegree(4, deg);
     delay(50 + sq(deg - 90) / 90);
   }
  
  delay(1000);
  for (uint16_t deg = 180; deg > 0; deg--) {
    moveDegree(0, 180 - deg);
    moveDegree(1, deg / 2);
    moveDegree(2, deg);
    moveDegree(3, 90 - deg / 2);
    delay(7 + sq((180 - deg) - 90) / 90);
  }
  delay(1000);



}


