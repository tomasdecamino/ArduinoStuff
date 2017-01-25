
#include <RedBot.h>
RedBotSensor lightSensor = RedBotSensor(A2); // initialize a sensor object on A3
RedBotMotor motors;


void setup()
{
  Serial.begin(9600);
}

void loop()
{

 int var = random(3)
 int val = map(lightSensor.read(),0,1023,255,0);

 switch (var) {
    case 1:
      motors.drive(-255);
      break;
    case 2:
      motors.drive(255);
      break;
    case 2:
      motors.drive(255);
      break;      
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
  char inChar;
  if (Serial.available()) {
    inChar = (char)Serial.read();
    if (inChar == 'u') {
      motors.drive(-255);
      delay(100);
      motors.brake();
    }
    if (inChar == 'd') {
      motors.drive(255);
      delay(100);
      motors.brake();
    }
    if (inChar == 'l') {
      motors.leftDrive(-255);
      delay(50);
      motors.brake();
    }
    if (inChar == 'r') {
      motors.rightDrive(-255);
      delay(50);
      motors.brake();
    }
  }

}
