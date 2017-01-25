
#include <RedBot.h>

RedBotMotor motors;
boolean s1 = true;
boolean s2 = true;
boolean s3 = true;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char inChar;
  if (Serial.available()) {
    inChar = (char)Serial.read();
    if (inChar == '1') {
      motors.drive(-255);
      delay(450);
      motors.brake();
    }
    if (inChar == '3') {
      motors.drive(255);
      delay(450);
      motors.brake();
    }
    if (inChar == '0') {
      motors.leftDrive(-250);
      delay(550);
      motors.brake();
    }
    if (inChar == '2') {
      motors.rightDrive(-250);
      delay(550);
      motors.brake();
    }
  }

}
