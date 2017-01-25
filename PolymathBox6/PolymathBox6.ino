
/* Tomas de Camino Beck
    www.funcostarica.org
*/
#include <CurieIMU.h>


#define OUT 9

int ax, ay, az;
int gx, gy, gz;

int val1,val2;
boolean state = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  val1 =1000;
  val2=100;
  CurieIMU.begin();

  //attachInterrupt(0, stateChange, RISING);
}

void loop() {
 CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);
  if (digitalRead(4)) {
    digitalWrite(3, HIGH);
    
    val1 =constrain(val1+ map(gx+gz, -4000, 4000, 100,-200),1000,20000);
    val2 = constrain(val2+ map(gy, -4000, 4000, -1,1),1,20);
    note(val1, val2);
  } else {
    digitalWrite(3, LOW);
    digitalWrite(OUT, LOW);
  }


}

void note(int n, int l) {
  for (int i = 0; i < l; i ++) {
    triangle();
    delayMicroseconds(n);
    digitalWrite(OUT, LOW);
    delayMicroseconds(n);
  }
}

float sawTooth(float x, float period) {
  float st = -2 / PI * atan(1 / (tan((x * PI) / period)));
  return st;

}

void triangle() {
  for (int i = 0; i < 256; i += 5) {
    analogWrite(OUT, i);
  }
}


