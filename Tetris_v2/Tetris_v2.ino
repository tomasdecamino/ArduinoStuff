/*
   by Tomas de-Camino-Beck

   Patterns are stored as a byte, each bit
   corresponding to a square in the pattern
   in the following manner

   bit:  0 1 2
         3 a 4
     5    5 6 7
   center of pattern "a" is always on
   position x,y refers to the center of the block
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
#define NSPACE 100

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//game variables
int bX = 123;
int bY = 12;
byte currentPattern = 0;

//space to be filled x=128 x y=8
//bits are used as y array
uint8_t gameSpace[NSPACE];

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  //create random blocks
  currentPattern = random(255);
  //first line full
  gameSpace[0] = 1023;
}

void loop() {
  display.clearDisplay();
  //draws space
  drawSpace();


  //draws a block
  drawBlock(bX, bY, currentPattern);
  bX -= BLOCKSIZE;
  int rX = bX / BLOCKSIZE;
  int rY = bY / BLOCKSIZE;
  /****checks if it is the end***/


  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100, 0);
  display.println(currentPattern);
  display.setCursor(20, 0);
  //display.println(rY);




  /*** check buttons *****/
  //A, C control left and right movements
  (digitalRead(BUTTON_A)) ? : bY -= BLOCKSIZE;
  (digitalRead(BUTTON_C)) ? : bY += BLOCKSIZE;
  //makes sure it stays inbound
  bY = constrain(bY, BLOCKSIZE, 32 - BLOCKSIZE * 3);
  //Rotate blocks
  (digitalRead(BUTTON_B)) ? : currentPattern = shiftBlock(currentPattern);

  /*** checks if fits ****/
  if (bX == 0 || checkBottom(currentPattern,  rX - 1, rY - 1)) {
    bX = 120;
    fit(currentPattern, rX, rY);
    currentPattern = random(255);
  }


  display.display();
  delay(50);
}

void drawBlock(int x, int y, byte pattern) {
  /* bit:  0 1 2
           3 a 4
           5 6 7
     center of pattern "a" is always on
  */

  /***bottom row***/
  if (bitRead(pattern, 5))display.fillRect(x - BLOCKSIZE , y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 6))display.fillRect(x - BLOCKSIZE, y , BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 7))display.fillRect(x - BLOCKSIZE, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  /***mid row (center always on)***/
  if (bitRead(pattern, 3))display.fillRect(x, y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 4))display.fillRect(x , y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  /***top row***/
  if (bitRead(pattern, 0))display.fillRect(x + BLOCKSIZE, y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 1))display.fillRect(x + BLOCKSIZE, y , BLOCKSIZE, BLOCKSIZE, WHITE);
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
  if (bitRead(pattern, 5))mstop = bitRead(gameSpace[x], y);
  if (bitRead(pattern, 6))mstop = bitRead(gameSpace[x], y + 1);
  if (bitRead(pattern, 7))mstop = bitRead(gameSpace[x], y + 2);
  return mstop;
}

//fit the pattern in our space array
void fit(byte pattern, byte x, byte y) {
  bitWrite(gameSpace[x - 1], y - 1, bitRead(pattern, 5));
  bitWrite(gameSpace[x - 1], y, bitRead(pattern, 6));
  bitWrite(gameSpace[x - 1], y + 1, bitRead(pattern, 7));

  bitWrite(gameSpace[x], y - 1, bitRead(pattern, 3));
  bitWrite(gameSpace[x], y, 1);
  bitWrite(gameSpace[x], y + 1, bitRead(pattern, 4));

  bitWrite(gameSpace[x + 1], y - 1, bitRead(pattern, 0));
  bitWrite(gameSpace[x + 1], y , bitRead(pattern, 1));
  bitWrite(gameSpace[x + 1], y + 1, bitRead(pattern, 2));
}

void drawSpace() {
  for (byte x = 0; x < NSPACE; x++) {
    for (byte y = 0; y < 8; y++) {
      if (bitRead(gameSpace[x], y)) {
        display.fillRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
      } else {
        display.fillRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, BLACK);
      }
    }
  }
}

