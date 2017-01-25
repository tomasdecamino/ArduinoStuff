/*
   by Tomas de-Camino-Beck

   Patterns are stored as a byte, each bit
   corresponding to a square in the pattern
   in the following manner

   bit:  0 1 2
         3 a 4
         5 6 7
   center of pattern "a" is always on
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
int x = 0;
int y = 12;
//array that contains blocks and coordinates
byte blockArray[NPATTERNS][3];
int current = 0;

//space to be filled 128 x 8
//bits are used as y array
uint8_t gameSpace[NSPACE];

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  //create random blocks
  for (int i = 0; i < NPATTERNS; i++) {
    blockArray[i][0] = random(255);
    blockArray[i][1] = 123;
    blockArray[i][2] = 12;
  }

}

void loop() {
  display.clearDisplay();
  //draws a block
  drawBlock(blockArray[current][1], blockArray[current][2], blockArray[current][0]);

  //checks if it is the end
  blockArray[current][1]--;
  (blockArray[current][1] <= current * BLOCKSIZE * 3) ? current++ : blockArray[current][1]--;


  //A, C control left and right movements
  if (!digitalRead(BUTTON_A))blockArray[current][2] -= 1;
  if (!digitalRead(BUTTON_C))blockArray[current][2] += 1;
  blockArray[current][2] = constrain(blockArray[current][2], BLOCKSIZE, 32 - BLOCKSIZE * 3);

  //Rotate blocks
  if (!digitalRead(BUTTON_B))blockArray[current][0] = shiftBlock(blockArray[current][0]);

  //how fast a block moves
  for (int i = 0; i < current; i++) {
    drawBlock(blockArray[i][1], blockArray[i][2], blockArray[i][0]);
  }
  display.display();
}

void drawBlock(int x, int y, byte pattern) {
  //top row
  if (bitRead(pattern, 0))display.fillRect(x - BLOCKSIZE, y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 1))display.fillRect(x, y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 2))display.fillRect(x + BLOCKSIZE, y - 4, BLOCKSIZE, BLOCKSIZE, WHITE);
  //mid row (center always on)
  if (bitRead(pattern, 3))display.fillRect(x - BLOCKSIZE, y, BLOCKSIZE, BLOCKSIZE, WHITE);
  display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 4))display.fillRect(x + BLOCKSIZE, y, BLOCKSIZE, BLOCKSIZE, WHITE);
  //Bottom row
  if (bitRead(pattern, 5))display.fillRect(x - BLOCKSIZE, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 6))display.fillRect(x, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
  if (bitRead(pattern, 7))display.fillRect(x + BLOCKSIZE, y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);

}

byte shiftBlock(byte pattern) {
  //rotates left by reconfiguring bits
  /* so bit:  0 1 2  shifts to:  2 4 7
              3 a 4              1 a 6
              5 6 7              0 3 5
  */
  byte out;
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


void checkBottom(byte pattern) {

}

void fit(byte pattern, byte x, byte y) {
  bitWrite(gameSpace[y], x, bitRead(pattern, 5));
  bitWrite(gameSpace[y], x + 1, bitRead(pattern, 6));
  bitWrite(gameSpace[y], x + 2, bitRead(pattern, 7));

  bitWrite(gameSpace[y + 1], x, bitRead(pattern, 3));
  bitWrite(gameSpace[y + 1], x + 1, 1);
  bitWrite(gameSpace[y + 1], x + 2, bitRead(pattern, 4));

  bitWrite(gameSpace[y + 2], x, bitRead(pattern, 0));
  bitWrite(gameSpace[y + 2], x + 1, bitRead(pattern, 1));
  bitWrite(gameSpace[y + 2], x + 2, bitRead(pattern, 2));
}

void drawSpace() {
  for (int y = 0; x < NSPACE; x++) {
    for (int x = 0; x < 8; x++) {
      if (bitRead(gameSpace[y], x)) {
        display.fillRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, WHITE);
      } else {
        display.fillRect(x * BLOCKSIZE, y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, BLACK);
      }
    }
  }
}

