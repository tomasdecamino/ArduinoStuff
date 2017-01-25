#include <RobotKit.h>

int leftL, rightL;
String cmd;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  Serial.begin(9600);
}

void loop(){
  //1: forward, 3: backward, 0:left, 2:right
  char inChar;// variable for current command
  for (int i = 0; i < cmd.length(); i++) {
    inChar = cmd[i];//reads command from string
    if (inChar == '1') {
      forward(150,750);
    }
    if (inChar == '3') {
      backward(150,750);
    }
    if (inChar == '0') {
      pivotLeft(150,750);

    }
    if (inChar == '2') {
      pivotRight(150,750);
    }
    stopMotors();
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
