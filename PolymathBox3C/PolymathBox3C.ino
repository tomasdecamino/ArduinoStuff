/* Tomas de Camino Beck
    www.funcostarica.org
*/

#include <Adafruit_NeoPixel.h>
#define OUT 3//output pin
#define PIN A4

int p =100;

volatile long delayTime = 100; //tempo based on sync input
long last = millis();

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);//interrupt

  pinMode(A0, INPUT_PULLUP);//on/off button

  //neopixel power and ground
  pinMode(A5, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  digitalWrite(A5, HIGH);

  //selector pins
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  pinMode(3, OUTPUT);//sound output

  attachInterrupt(0, tempo, RISING);
  strip.begin();
  strip.show();

  Serial.begin(9600);

}

void loop() {
  if (!digitalRead(A0)) {
    strip.setPixelColor(0, random(255), random(255), random(255));
    strip.show();
    if (!digitalRead(4)) seq1();
    if (!digitalRead(5)) seq2();
    if (!digitalRead(6)) seq3();
    if (!digitalRead(7)) seq4();
    if (!digitalRead(8)) seq5();
    if (!digitalRead(9)) seq6();
    if (!digitalRead(10)) seq7();
    if (!digitalRead(11)) seq8();
    if (!digitalRead(12)) seq9();
    if (!digitalRead(13)) seq10();
  }
  digitalWrite(OUT, LOW);
  strip.setPixelColor(0, 0, 0, 0);
  strip.setBrightness(255);
  strip.show();
  Serial.println(p);
  p+=100;
}

/***** functions and sequences*****/

// n determines de frequency and l the duration
void note(int n, int l) {
  for (int i = 0; i < l; i ++) {
    triangle();
    delayMicroseconds(n);
    digitalWrite(OUT, LOW);
    delayMicroseconds(n);
  }
}

void seq1() {
  note(2500, delayTime);
  note(2000, delayTime);
  note(5000, delayTime);
  note(1000, delayTime);
  note(15000, delayTime);

}

void seq2() {
  note(2500, delayTime);
  note(3500, delayTime);
  note(4500, delayTime);
  note(5500, delayTime);
  note(7500, delayTime);
}

void seq3() {
  note(10500, delayTime);
  note(4000, delayTime);
  note(80000, delayTime);
}

void seq4() {
  note(20000, delayTime * 2);
  note(3000, delayTime);
  note(400, delayTime);
  note(5500, delayTime / 2);
  note(7500, delayTime);
}

void seq5() {
  note(80000, delayTime * 2);
  note(40000, delayTime * 2);
}

void seq6() {
  note(5000, delayTime / 2);
  note(1000, delayTime);
  note(5000, delayTime / 2);
  note(600, delayTime);
}

void seq7() {
  note(1000, delayTime);
  note(40000, delayTime);
  note(5000, delayTime);
  note(40000, delayTime);
}

void seq8() {
  note(2500, delayTime);
  note(40000, delayTime);
  note(5000, delayTime);
  note(40000, delayTime);
}

void seq9() {
  note(500, delayTime * 2);
  note(5000, delayTime);
  note(100, delayTime);
  note(8000, delayTime / 2);
  note(500, delayTime);
  note(5000, delayTime);
}

void seq10() {
  note(500, delayTime);
  note(1000, delayTime);
  note(1500, delayTime);
}

/**** triangle sound wave ****/
void triangle() {
  for (int i = 0; i < 256; i +=2) {
    analogWrite(OUT, i);   
  }
}

//function for getting the tempo from sync input
void tempo() {
  long d = millis() - last;
  if (d > 0)delayTime = d / 4;
  last = millis();
}


