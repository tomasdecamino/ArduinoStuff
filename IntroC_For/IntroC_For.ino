//  Written by Tomas de Camino Beck  for Inventoria.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int num = 10;
int posX[num] ;
int posY[num];

SSD1306 display(4);

void setup() {
  randomSeed(A0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // inicializa el OLED
  display.clearDisplay();   // limpia el buffer
  for (int i = 0; i < num; i++) {
    posX[i] = 64;
    posY[i] = 32;
  }
}

void loop() {
  display.clearDisplay();
  for (int i = 0; i < num; i++) {
    posX[i] = constrain(posX[i] + random(-3, 3),1,127);
    posY[i] = constrain(posY[i] + random(-3, 3),1,63);
    display.fillCircle(posX[i], posY[i],  1, WHITE); //dibuja un circulo
    display.display(); //actuaiza la pantalla
  }
  delay(100);
}
