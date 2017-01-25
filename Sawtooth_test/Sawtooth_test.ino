/* Tomas de Camino Beck
 *  www.inventoria.org
 */

float a = 0.0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  float p = float(analogRead(A0) + 1) / 1023;
  a += 0.0001;
  int val = floor((1 + sawTooth(a, p)) / 2 * 255);
  int val2 = map(analogRead(A1), 0, 1023, 500, 15000);
  analogWrite(9, val);
  delayMicroseconds(val2+random(10000));
  digitalWrite(9, LOW);
  delayMicroseconds(val2);
}

float sawTooth(float x, float period) {
  float st = -2 / PI * atan(1 / (tan((x * PI) / period)));
  return st;

}

