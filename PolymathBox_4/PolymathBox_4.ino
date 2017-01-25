/* Tomas de Camino Beck
    www.funcostarica.org
*/
#include <Wire.h>
#include <ZX_Sensor.h>


#define OUT 9
//range of notes in the theremin
#define MIN 100
#define MAX 1500

// Constants
const int ZX_ADDR = 0x10;  // ZX Sensor I2C address

// Global Variables
ZX_Sensor zx_sensor = ZX_Sensor(ZX_ADDR);
uint8_t x_pos;
uint8_t z_pos;


void setup() {
  // for the LED
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  digitalWrite(A0, HIGH);

  //audio output
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  //inicialize gesture sensor
  zx_sensor.init();

}

void loop() {
  if ( zx_sensor.positionAvailable() && zx_sensor.readZ() < 255) {
    digitalWrite(A0, HIGH);//light on
    x_pos = zx_sensor.readX();
    z_pos = zx_sensor.readZ();
    analogWrite(6, x_pos); //VU meter
    int val2 = map(z_pos, 0, 160, MIN, MAX);
    int val = map(x_pos, 0, 255, 0, 30);
    int t = random(15000);
    note(val2, val);

  }
  analogWrite(6, LOW);//VU meter to 0
  digitalWrite(A0, LOW);//light off
}

//to play a note at n and duration l
void note(int n, int l) {
  for (int i = 0; i < l; i ++) {
    triangle();
    delayMicroseconds(n);
    digitalWrite(OUT, LOW);
    delayMicroseconds(n);
  }
}

//a sort of  wave sound (more like sawtoth)
void triangle() {
  for (int i = 255; i > 0; i -= 2) {
    analogWrite(OUT, 255);
  }
}

