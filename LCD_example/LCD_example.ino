
//@author Tomas de Camino Beck
// libreria:
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int botonActual = 0;

void setup() {
  // numero de columnas y filas del LCD
  lcd.begin(16, 2);
  lcd.clear();
  // Escribe el mensaje en la pantalla
  lcd.print("hola a todos");
  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);//acomoda la pos del cursor
  int val = analogRead(A0); //
  if (val != botonActual) {
    botonActual = val;
  }
  lcd.print(botonActual);
  delay(100);
}

