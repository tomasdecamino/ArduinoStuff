#include <RedBot.h>
RedBotMotor motors;
int motorPower;  // variable for setting the drive power
int data;  // variable for holding incoming data from PC to Arduino

void setup(void)
{
  Serial.begin(9600);
}

void loop(void)
{
  // if there is data coming in on the Serial monitor, do something with it.
  if(Serial.available() > 0)
  {
    data = Serial.parseInt();
    data = constrain(data, -255, 255);  // constrain the data to -255 to +255
    motors.drive(data);
  }  
}

