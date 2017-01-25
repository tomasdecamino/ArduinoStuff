#include <TVout.h>



TVout TV;
unsigned char x, y;
float sX, sY;

boolean space[50][50];
boolean spaceTmp[50][50];


void setup ( )
{
  TV.begin( NTSC, 120, 96);
  sX = random(1, 5);
  sY = random(1, 5);
}

void loop ( )
{
  TV.clear_screen ( );
  TV.draw_rect(x, y, 1, 1, WHITE, INVERT);
  int val = analogRead(A0);
  int pos = map(val, 0, 1023, 1, 74);
  int val2 = analogRead(A1);
  int pos2 = map(val2, 0, 1023, 1, 74);
  TV.draw_line(0, pos + 1, 0, pos + 20, INVERT);
  TV.draw_line(118, pos2 + 1, 118, pos2 + 20, INVERT);
  TV.draw_line(60, 0, 60, 96, INVERT);
  TV.delay (50);
  x += sX;
  y += sY;
  if (x > 118 || x < 1)sX *= -1;
  if (y > 94 || y < 1)sY *= -1;
}

void copyArray() {
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      spaceTmp[i][j] = space[i][j];
    }
  }
}
