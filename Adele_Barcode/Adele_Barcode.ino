#include <Servo.h>
#include <Adafruit_CircuitPlayground.h>
#include "Adele_Robot.h"


int count = 0;//counts marks for code
boolean stopState = false;
uint16_t sensorRight, sensorLeft;//sensroRight reads guide, sensroLeft reads code
byte code = 0; //code read

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  Serial.begin(9600);
  pixelsOff();
  adeleBegin();
}

void loop() {
  
  //resets for new reading
  if (CircuitPlayground.rightButton()) {
    count = 0;
    code = 0;
    // pixelsOff();
    stopState = false;
    stopServos();
  }


  /**** READ CODE *****/
  if (CircuitPlayground.leftButton() && !stopState) {
    //detects changes B to W, W to B i.e. wait until change
    while (sensorRight != digitalRead(6)) {
      sensorRight = digitalRead(6);
      sensorLeft = digitalRead(3);//reads info bit
      CircuitPlayground.setPixelColor(9, 0, 255, 0);
      count++;
      bitWrite(code, count - 1, sensorLeft);//set the corresponding bit
    }
    CircuitPlayground.setPixelColor(9, 255, 0 , 0);
    
    //code has been read
    if (count >= 6) {
      stopState = true;
      for (int i = 0; i < 10; i++) {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(25 * i));
        CircuitPlayground.playTone(500 + i * 500, 80);
      }
      pixelsOff();
    }

  }

  /****** EXECUTE MODES ******/
  if (stopState) {
    switch (code) {
      case 1://stay inside blak line
        stayInside();
        break;
      case 2://move when sound
        if (CircuitPlayground.soundSensor() > 900) {
          CircuitPlayground.setPixelColor(9, 255, 100 , 0);
          CircuitPlayground.setPixelColor(0, 255, 100 , 0);
          randomMove(500);
          randomMove(500);
          randomMove(500);
          stopServos();
          CircuitPlayground.setPixelColor(9, 0, 0 , 0);
          CircuitPlayground.setPixelColor(0, 0, 0 , 0);
        }
        break;
      case 3://simple line follower
        followLine();
        break;
      case 4://randomwalk
        randomMove(300);
        delay(100);
        break;
      case 5://just move forward
        forward();
        delay(200);
        break;
    }
  }

}

void pixelsOff() {
  for (int i = 0; i < 10; i++)
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
}




