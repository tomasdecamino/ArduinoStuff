/* Tomás de Camino Beck
 for remote codes check codes.txt
*/

#include <RobotKit.h>

int RECV_PIN = 7;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  startRemote(RECV_PIN);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long ul = getRemote();
  if (ul) {
    if (ul == REMOTE_2) {
      forward(100, 250);
    }
    if (ul == REMOTE_8) {
      backward(100, 250);
    }
    if (ul == REMOTE_4) {
      pivotLeft(100, 250);
    }
    if (ul == REMOTE_6) {
      pivotRight(100, 250);
    }
  }
  stopMotors();
}
