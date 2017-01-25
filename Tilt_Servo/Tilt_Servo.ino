// @author Tomas de Camino Beck
// inventoria.org & funcostarica.org

#include <Servo.h>

Servo miservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP); // inicia el pin A0
  miservo.attach(6);
}

void loop() {
  int tilt = digitalRead(2);
  if (tilt == 0) {
    miservo.write(0);
  } else {
    miservo.write(180);
  }
  delay(200);
}
