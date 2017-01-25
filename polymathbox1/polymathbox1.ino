/* Tomas de Camino Beck
    www.funcostarica.org
*/


float a = 0.0;
long lastMillis = millis();
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(2, OUTPUT);
  randomSeed(A0);
  digitalWrite(2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  a += 0.001;
  int val2 = map(analogRead(A1), 0, 1023, 10, 5000);

  int t = random(15000);
  while (millis() - lastMillis < val2) {
    //triangle(2000);
    float p = float(analogRead(A0) + 1) / 1024;
    int val = floor((1 + sawTooth(a, p)) / 2 * 255);
    analogWrite(9, val);
    delayMicroseconds(t);
    digitalWrite(9, LOW);
    delayMicroseconds(t);
  }
  lastMillis = millis();
}

float sawTooth(float x, float period) {
  float st = -2 / PI * atan(1 / (tan((x * PI) / period)));
  return st;

}

void triangle(int m) {
  for (int i = 0; i < 256; i ++) {
    analogWrite(9, i);

  }
  for (int i = 255; i > -1; i --) {
    analogWrite(9, i);

  }
  digitalWrite(9, LOW);
  delayMicroseconds(m);
}

