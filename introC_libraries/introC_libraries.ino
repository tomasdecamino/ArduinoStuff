/*********************************************************************
  Written by Tomas de Camino Beck  for Inventoria.
*********************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int circleSize = 1;

SSD1306 display(4);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // inicializa el OLED
  display.clearDisplay();   // limpia el buffer

}

void loop() {
  display.drawCircle(64, 32, circleSize, WHITE);//dibuja un circulo
  display.display(); //actuaiza la pantalla
  delay(400);  //espera 400 milisegundos
  circleSize+=2;  // aumenta el diametro en 2 
}
