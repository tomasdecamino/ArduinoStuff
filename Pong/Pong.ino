// Tomás de Camino


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//game variables
int X1 = 11;
int X2 = 11;

int ballX = 11;
int ballY = 51;
int dirX = 1;
int dirY = 1;
int ballSpeed=1;


//space to be filled x=128 x y=8
//bits are used as y array


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(1);
  display.clearDisplay();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

}

void loop() {
  //cambia el grado de dificultad (velocidad de la bola)
  (digitalRead(BUTTON_A)) ? : ballSpeed--;
  (digitalRead(BUTTON_C)) ? : ballSpeed++;
  //limpia pantalla
  display.clearDisplay();
  //linea de el medio
  display.drawLine(0, 64, 34, 64, WHITE);

  
  //dibuja los pads
  drawPad(11, 120);
  drawPad(X1, 0);

  //mueve la bola
  movedrawBall();

  //redibuja la pantalla
  display.display();
}

void drawPad(int x, int y) {
  display.fillRect(x, y, 10, 2, WHITE);

}

void movedrawBall() {
  //mueve la bola
  ballX += dirX*ballSpeed;
  ballY += dirY*ballSpeed;
  //rebota en los bordes
  (ballX >= 0 && ballX < 30) ? : dirX *= -1;
  (ballY >= 0 && ballY < 124) ? : dirY *= -1;
  //revisa si pega en los pads y rebota


  display.fillRect(ballX, ballY, 5, 5, WHITE);

}

