/* Tomás de Camino Beck
 for remote codes check codes.txt
*/

#include <RobotKit.h>
#include <IRremote.h>

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    if (results.value == 16718055) {
      forward(100, 250);
    }
    if (results.value == 16730805) {
      backward(100, 250);
    }
    if (results.value == 16716015) {
      pivotLeft(100, 250);
    }
    if (results.value == 16734885) {
      pivotRight(100, 250);
    }
    irrecv.resume();
  }
  stopMotors();


}
