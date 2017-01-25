//creado por Tomas de Camino Beck
//Para bionica veritas
void setup()
{
  //Asigna el pin 13 para salida
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);   // Prende el LED
  delay(500);              // espera 1 segundo
  digitalWrite(13, LOW);    // Apaga el LED
  delay(500);              // espera 1 segundo
}

