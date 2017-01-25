// Tomas de Camino
// www.inventoria.org

#define TIME 2000

void setup() {
  pinMode(2, OUTPUT); //verde
  pinMode(3, OUTPUT); //amarillo
  pinMode(4, OUTPUT); //Rojo
  pinMode(8, INPUT_PULLUP); //Boton
}
void loop() {
  // verde por un rato
  cambioColor(0);
  delay(TIME);
  //secuencia del amarillo
  cambioColor(1);
  delay(200);
  allOff();
  delay(200);
  cambioColor(1);
  delay(200);
  allOff();
  delay(200);
  cambioColor(1);
  delay(200);
  allOff();
  //cambio al rojo
  cambioColor(2);
  delay(TIME);

}

void cambioColor(int val) {
  switch (val) {
    case 0:
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      break;
    case 1:
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      break;
    case 2:
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      break;
  }
}

void allOff() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

