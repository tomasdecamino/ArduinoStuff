/*********************************************************************
  Written by Tomas de Camino Beck  for Inventoria.
*********************************************************************/
boolean actual = false;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  int state = digitalRead(2);
  if (actual != state) {
    actual = state;
  }
  if (actual) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

}
