/*
   by Tomas de-Camino-Beck

   Patterns are stored as a byte, each bit
   corresponding to a square in the pattern
   in the following manner

   bit:  0 1 2
         3 a 4
         5 6 7
   center of pattern "a" is always on
   position x,y refers to the center of the block


  This example was created by Tomàs de Camino Beck (tomas@funcostarica.org)
  GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
*/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5
//number of blocks in the game
#define NPATTERNS 100
#define BLOCKSIZE 4  //how big are the blocks
#define NSPACE 30

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//game variables
int bX = 12;
int bY = 10;
byte currentPattern = 0;

//space to be filled x=128 x y=8
//bits are used as y array
uint8_t gameSpace[NSPACE];

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(1);
  display.clearDisplay();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  //create random blocks
  currentPattern = random(255);
  //first line full
   gameSpace[NSPACE-1] = 1023;
}

void loop() {
  display.clearDisplay();
  //draws space
  drawSpace();


  //draws a block
  drawBlock(bX, bY, currentPattern);
  bY += BLOCKSIZE;
  int rX = bX / BLOCKSIZE;
  int rY = bY / BLOCKSIZE;
  /****checks if it is the end***/





  /*** check buttons *****/
  //A, C control left and right movements
  (digitalRead(BUTTON_A)) ? : bX -= BLOCKSIZE;
  (digitalRead(BUTTON_C)) ? : bX += BLOCKSIZE;
  //makes sure it stays inbound
  bX = constrain(bX, BLOCKSIZE, 32 - BLOCKSIZE * 3);
  //Rotate blocks
  (digitalRead(BUTTON_B)) ? : currentPattern = shiftBlock(currentPattern);

  /*** checks it is moves anf fits piece ****/
  if (bY >= 120 || checkBottom(currentPattern,  rX, rY)) {
    bY = 10;
    fit(currentPattern, rX, rY);
    currentPattern = random(255);
  }

  /***** show scoreboard *******/

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("S:");
  display.setCursor(12, 0);
  display.println(score());
  display.drawLine(0, 9, 28, 9, WHITE);

  /********************/

  display.display();
  delay(100);
}

void drawBlock(int x, int y, byte pattern) {
  /* bit:  0 1 2
           3 a 4
           5 6 7
     center of pattern "a" is always on
  */

  /***bottom row***/
  if (bitRead(pattern, 5))display.fillRect(x - BLOCKSIZE , y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 6))display.fillRect(x , y - BLOCKSIZE , BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 7))display.fillRect(x + BLOCKSIZE, y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  /***mid row (center always on)***/
  if (bitRead(pattern, 3))display.fillRect(x - BLOCKSIZE, y , BLOCKSIZE, BLOCKSIZE, WHITE);
  display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 4))display.fillRect(x + BLOCKSIZE , y , BLOCKSIZE, BLOCKSIZE, WHITE);
  /***top row***/
  if (bitRead(pattern, 0))display.fillRect(x - BLOCKSIZE, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 1))display.fillRect(x , y + BLOCKSIZE , BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 2))display.fillRect(x + BLOCKSIZE, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);

}

byte shiftBlock(byte pattern) {
  //rotates left by reconfiguring bits
  /*    bit:  0 1 2  shifts to:  2 4 7
              3 a 4              1 a 6
              5 6 7              0 3 5
  */
  byte out;//to write new configuration
  bitWrite(out, 2, bitRead(pattern, 0));
  bitWrite(out, 4, bitRead(pattern, 1));
  bitWrite(out, 7, bitRead(pattern, 2));
  bitWrite(out, 1, bitRead(pattern, 3));
  bitWrite(out, 6, bitRead(pattern, 4));
  bitWrite(out, 0, bitRead(pattern, 5));
  bitWrite(out, 3, bitRead(pattern, 6));
  bitWrite(out, 5, bitRead(pattern, 7));
  return out;
}

//check if there is something below the block
boolean checkBottom(byte pattern, byte x, byte y) {
  boolean mstop = false;
  if (bitRead(pattern, 5))mstop = bitRead(gameSpace[y + 1], x-1);
  if (bitRead(pattern, 6))mstop = bitRead(gameSpace[y + 1], x);
  if (bitRead(pattern, 7))mstop = bitRead(gameSpace[y + 1], x + 1);
  return mstop;
}

//fit the pattern in space array filling
void fit(byte pattern, byte x, byte y) {
  bitWrite(gameSpace[y + 1], x - 1, bitRead(pattern, 0) || bitRead(gameSpace[y + 1], x - 1));
  bitWrite(gameSpace[y + 1], x, bitRead(pattern, 1) || bitRead(gameSpace[y + 1], x ));
  bitWrite(gameSpace[y + 1], x + 1, bitRead(pattern, 2) || bitRead(gameSpace[y + 1], x + 1));

  bitWrite(gameSpace[y], x - 1, bitRead(pattern, 3) || bitRead(gameSpace[y], x - 1));
  bitWrite(gameSpace[y], x, 1);
  bitWrite(gameSpace[y], x + 1, bitRead(pattern, 4) || bitRead(gameSpace[y], x + 1));

  bitWrite(gameSpace[y - 1], x - 1, bitRead(pattern, 5) || bitRead(gameSpace[y - 1], x - 1));
  bitWrite(gameSpace[y - 1], x , bitRead(pattern, 6) || bitRead(gameSpace[y - 1], x ));
  bitWrite(gameSpace[y - 1], x + 1, bitRead(pattern, 7) || bitRead(gameSpace[y - 1], x + 1));
}

void drawSpace() {
  for (byte y = 0; y < NSPACE; y++) {
    for (byte x = 0; x < 8; x++) {
      if (bitRead(gameSpace[y], x)) {
        display.drawRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
      } else {
        display.drawRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, BLACK);
      }
    }
  }
}

//get score as % total space filling
int score(){
  float s =0;
  for (byte y = 0; y < NSPACE; y++)s+=count(gameSpace[y]);
  return int(s/(8*NSPACE)*100);
}

/**counting bits (Kernighan method)
 * l &= l-1 what it does is removes the rightmost bit
 * until no bit is left (counting in c)
 */
int count(unsigned int l) {
    int c;
    for (c = 0; l != 0; c++, l &= l-1);
    return c;
}

