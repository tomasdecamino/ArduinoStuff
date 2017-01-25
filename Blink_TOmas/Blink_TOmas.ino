//Intro a C
//@author Tomas de Camino Beck

// setup funciona solo al inicio
void setup() {
  // inicializa el pin 13
  pinMode(13, OUTPUT);
}

// loop se repite cada 4 microsegundos en Arduino
void loop() {
  digitalWrite(13, HIGH);   // prede el LED
  delay(1000);              // espera un segundo
  digitalWrite(13, LOW);    // apaga el LED
  delay(1000);              // espera un segundo
}
