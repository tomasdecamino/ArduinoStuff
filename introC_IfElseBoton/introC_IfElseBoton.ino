/*********************************************************************
  Written by Tomas de Camino Beck  for Inventoria.
*********************************************************************/
void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void loop() {
  int state = digitalRead(2);
  if (state == 0) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

}
