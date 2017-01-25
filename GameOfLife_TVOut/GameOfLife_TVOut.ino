#include <TVout.h>
#define N 12
#define OFFSETX 5
#define OFFSETY 0

TVout TV;

boolean space[N][N];
boolean spaceTmp[N][N];


void setup ( )
{
  randomSeed(analogRead(0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      float r = random(10, 100);
      space[i][j] = (r >= 98);
    }
  }
  TV.begin( NTSC, 120, 96);
}

void loop ( )
{
  TV.clear_screen ( );
  TV.draw_rect(10, 10, 1, 1, WHITE, INVERT);
  displayGL();
  applyRule();
  TV.delay (2);

}

void displayGL() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (space[i][j]) TV.draw_rect(i * 4 + OFFSETX, j * 4 + OFFSETY, 2, 2, WHITE,INVERT);
    }
  }
}

void copyArray() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      space[i][j] = spaceTmp[i][j];
    }
  }
}

void applyRule() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int sum = 0;
      for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
          int x = (i + k) % N;
          int y = (j + l) % N;
          sum += space[x][y];
        }
      }
      if (space[i][j]) {
        if (sum == 2 || sum == 3) {
          spaceTmp[i][j] = true;
        } else {
          spaceTmp[i][j] = false;
        }
      }else{
        if (sum == 2){
         spaceTmp[i][j] = true;
        }else{
         spaceTmp[i][j] = false;
        } 
      }     
    }
  }
  copyArray();
}
