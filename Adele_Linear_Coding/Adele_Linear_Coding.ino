#include <Servo.h>
#include <Adafruit_CircuitPlayground.h>
#include "Adele_Robot.h"


int count = 0;//counts marks for code
int ruleNumber = 0; //number of rules
byte rule[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned long duration;

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

  duration = pulseIn(19, HIGH, 4000000);
  //Serial.println(duration);

  //resets for new reading if pressed for 2 seconds... count 1001, 1002
  if (duration > 1000000) {
    //Serial.println("in");
    count = 0;
    code = 0;
    pixelsOff();
    stopState = false;
    stopServos();
  }
  if (duration > 0 && duration < 1000000) {
    count++;
    stopState = false;
    for (int i = 0; i < 10; i++){
      if(rule[i]>0) CircuitPlayground.setPixelColor(i, 0, 255 , 0);
      else CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  }
  Serial.println(ruleNumber);

  /**** READ CODE *****/
  if (CircuitPlayground.leftButton() && !stopState) {
    Serial.println("in");
    //detects changes B to W, W to B i.e. wait until change
    while (sensorRight != digitalRead(6)) {
      sensorRight = digitalRead(6);
      sensorLeft = digitalRead(3);//reads info bit
      ;
      count++;
      Serial.println(count);
      bitWrite(code, count - 1, sensorLeft);//set the corresponding bit
    } 

    //code has been read
    if (count >= 6) {
      rule[ruleNumber] = code;
      ruleNumber++;
      stopState = true;
      code = 0;
      CircuitPlayground.playTone(440, 500);
      pixelsOff();
    }

  }

  /****** EXECUTE MODES ******/
  if (stopState) {
    switch (code) {
      case 1://stay inside blak line
        forward();
        delay(100);
        break;
      case 2://move when sound
        backward();
        delay(100);
        break;
      case 3://simple line follower
        left();
        delay(100);
        break;
      case 4://randomwalk
        right();
        delay(100);
        break;
    }
  }

}

void pixelsOff() {
  for (int i = 0; i < 10; i++)
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
}




