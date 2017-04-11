// Tomás de Camino
// www.funcostarica.org

//Utiliza Feather y Pantalla OLED

// Boton C incrementa velocidad de bola
// Boton A disminuye velocidad
// Boton B reinicia juego


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//pad position
int X1 = 11, X2 = 11;

//ball position and direction
int ballX = 16, ballY = 64;
int dirX = 1, dirY = 1;
int ballSpeed = 1;

//score
int playerA = 0, playerB = 0;


void setup() {
  //prepara display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(1);
  display.clearDisplay();
  //botones
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  //pad pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  //si aprieta B reinicia
  if (!digitalRead(BUTTON_B)) reiniciaPong();

  //cambia el grado de dificultad (velocidad de la bola)
  (digitalRead(BUTTON_A)) ? : ballSpeed--;
  (digitalRead(BUTTON_C)) ? : ballSpeed++;

  //limpia pantalla
  display.clearDisplay();

  //linea de el medio
  display.drawLine(0, 64, 34, 64, WHITE);

  //dibuja los pads
  X1 = map(analogRead(A0), 0, 1023, 31, 3);
  X2 = map(analogRead(A1), 0, 1023, 3, 31);
  drawPad(X2, 124);
  drawPad(X1, 0);

  //mueve la bola
  movedrawBall();
  //verifica donde esta la bola y rebota
  bounceBall();

  //puntos en pantalla
  display.setRotation(0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor( 68, 0);
  display.println(playerA);
  display.setCursor( 52, 0);
  display.println(playerB);
  display.setRotation(1);

  //redibuja la pantalla
  display.display();
}

void drawPad(int x, int y) {
  display.fillRect(x - 3, y, 6, 2, WHITE);

}

void movedrawBall() {
  //mueve la bola
  ballX += dirX * ballSpeed;
  ballY += dirY * ballSpeed;

  //dibuja la bola
  display.fillRect(ballX, ballY, 3, 3, WHITE);

}

//Este procedimiento es lo principal del juego
void bounceBall() {
  //rebota en los bordes de X
  (ballX >= 0 && ballX < 30) ? : dirX *= -1;

  //bordes de Y son puntos
  if (ballY < 0) {
    playerB++;
    initBall();
  }
  if (ballY > 124) {
    playerA++;
    initBall();
  }
  //revisa si pega en los pads y rebota
  int d1 = ballX - X1;
  int d2 = ballX - X2;
  (ballY == 0 && abs(d1) <= 2) ? : dirY *= -1;
  (ballY == 124 && abs(d2) <= 2) ? : dirY *= -1;

}

void initBall() {
  ballX = 16;
  ballY = 64;
  (random(4) >= 2) ? dirX = 1 : dirX = -1;
  (random(4) >= 2) ? dirY = 1 : dirY = -1;
}

void reiniciaPong() {
  ballX = 16;
  ballY = 64;
  (random(4) >= 2) ? dirX = 1 : dirX = -1;
  (random(4) >= 2) ? dirY = 1 : dirY = -1;
  playerA = 0;
  playerB = 0;
}

