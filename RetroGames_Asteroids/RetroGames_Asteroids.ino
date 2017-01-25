/*********************************************************************
Written by Tomas de Camino Beck  for Inventoria.
*********************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
SSD1306 display(OLED_RESET);

int16_t x, y, shipX, shipY, laserX, laserY;
float sX, sY, lx, ly;
int h = 6;


void setup()   {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();   // clears the screen and buffer

  sX = random(1, 3);
  sY = random(1, 3);
  shipX = 64;
  shipY = 32;
  pinMode(2, INPUT_PULLUP);
  laserX = 64;
  laserY = 32;

}


void loop() {
  display.clearDisplay();
  int val = analogRead(A0);
  float pos = map(val, 0, 1023, 0, 740);
  float dir = PI / 180 * pos;
  drawShip(dir);
  display.fillRect(laserX, laserY, 2, 2, WHITE);
  display.fillRect(x, y, 9, 9, WHITE);
  display.display();
    if (!digitalRead(2)) {
    laserX = 64;
    laserY = 32;
    lx = sin(dir) * 3;
    ly = cos(dir) * 3;
  }
  x += sX;
  y += sY;
  laserX = constrain(laserX + lx, 0, 128);
  laserY = constrain(laserY + ly, 0, 64);
  bounce();
}

void bounce() {
  if (x > 119 || x < 1)sX *= -1;
  if (y > 55 || y < 1)sY *= -1;
}

void drawShip(float a) {
  int p1x = shipX + sin(a) * h;
  int p1y = shipY + cos(a) * h;
  int p2x = shipX + sin(a + 2.09) * h;
  int p2y = shipY + cos(a + 2.09) * h;
  int p3x = shipX + sin(a + 4.18) * h;
  int p3y = shipY + cos(a + 4.18) * h;
  display.drawLine( p1x, p1y, p2x, p2y, WHITE);
  display.drawLine(p2x, p2y, p3x, p3y, WHITE);
  display.drawLine( p1x, p1y, p3x, p3y, WHITE);

}


