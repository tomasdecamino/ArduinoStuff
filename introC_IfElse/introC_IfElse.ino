/*********************************************************************
  Written by Tomas de Camino Beck  for Inventoria.
  Bola que rebota
*********************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//posicion de la bola
int x = 64;
int y = 32;

//velocidad en x y y
int vX = 1;
int vY = 1;

SSD1306 display(4);

void setup() {

  randomSeed(A0); //cambia el inicio random
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // inicializa el OLED
  display.clearDisplay();   // limpia el buffer

  //velocidades iniciales random
  vX = random(-5, 5);
  vY = random(-5, 5);

}

void loop() {
  display.clearDisplay();

  // dibuja un c[irculo mas grande en los bordes
  if (x < 3 || x > 125 || y < 3 || y > 60) {
    display.drawCircle(x, y, 10, WHITE);//dibuja un circulo
  } else {
    display.fillCircle(x, y, 3, WHITE);
  }
  display.display(); //actuaiza la pantalla

  //recalcula posicion
  x += vX;
  y += vY;

  // choque elastico en paredes
  if (x > 128 || x < 1) {
    vX *= -1;
  }
  if (y > 64 || y < 1) {
    vY *= -1;
  }

}
