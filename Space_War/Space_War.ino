#include <TVout.h>

TVout TV;
unsigned char x, y, shipX, shipY, laserX, laserY;
float sX, sY, lx, ly;
int h = 5;

void setup ( )
{
  TV.begin( NTSC, 120, 96);
  sX = random(1, 5);
  sY = random(1, 5);
  shipX = 60;
  shipY = 48;
  pinMode(4, INPUT_PULLUP);
  laserX = 60;
  laserY = 48;
}

void loop ( )
{
  TV.clear_screen ( );
  TV.draw_rect(laserX, laserY, 1, 1, WHITE, INVERT);
  TV.draw_rect(x, y, 5, 5, WHITE, INVERT);
  int val = analogRead(A0);
  float pos = map(val, 0, 1023, 0, 740);
  float dir = PI / 180 * pos;
  drawShip(dir);
  TV.delay (50);
  if (!digitalRead(4)) {
    laserX = 60;
    laserY = 48;
    lx = sin(dir) * 10;
    ly = cos(dir) * 10;
  }
  x += sX;
  y += sY;
  laserX =constrain(laserX+lx,-1,121);
  laserY =constrain(laserY+ly,-1,97);
  if (x > 118 || x < 1)sX *= -1;
  if (y > 94 || y < 1)sY *= -1;
}

void drawShip(float a) {
  int p1x = shipX + sin(a) * h;
  int p1y = shipY + cos(a) * h;
  int p2x = shipX + sin(a + 2.09) * h;
  int p2y = shipY + cos(a + 2.09) * h;
  int p3x = shipX + sin(a + 4.18) * h;
  int p3y = shipY + cos(a + 4.18) * h;

  TV.draw_line( p1x, p1y, p2x, p2y, WHITE);
  TV.draw_line(p2x, p2y, p3x, p3y, WHITE);
  TV.draw_line( p1x, p1y, p3x, p3y, WHITE);

}


