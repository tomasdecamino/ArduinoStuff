/* @author: Tomas de Camino Beck
 * @version: 1.0 Jan 2016
 * www.inventoria.org
 * Hecho en Costa Rica
 */

String cmd; //stores commands from serial as string
#include <RedBot.h>

RedBotMotor motors;

void setup()
{
  Serial.begin(9600);//starts serial port
}

void loop()
{
  //1: forward, 3: backward, 0:left, 2:right
  char inChar;// variable for current command
  for (int i = 0; i < cmd.length(); i++) {
    inChar = cmd[i];//reads command from string
    if (inChar == '1') {
      motors.drive(-150);
      delay(750);
    }
    if (inChar == '3') {
      motors.drive(150);
      delay(750);
    }
    if (inChar == '0') {
      motors.leftDrive(-150);
      delay(750);
    }
    if (inChar == '2') {
      motors.rightDrive(-150);
      delay(750);
    }
    motors.brake();
    delay(300);//waits so it each command are seen as discrete moves
  }
  cmd = "";//clears command string to get ready for next

}

void serialEvent() {
  //reads serial data and stores it as string in global
  //variable cmd. Commad sequences are separated by new line
  if (Serial.available())
  {
    cmd = Serial.readStringUntil('/n');

  }
}
