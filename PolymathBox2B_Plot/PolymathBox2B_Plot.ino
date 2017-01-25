/* Tomas de Camino Beck
    www.funcostarica.org
*/

#define OUT 9

float a = 0.0;
long lastMillis = millis();


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(A5, OUTPUT);
  digitalWrite(A5,LOW);
  pinMode(A4,OUTPUT);
  digitalWrite(A4,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 // float p = float(analogRead(A0) + 1) / 5023;
  a += .001;
  int val2 = map(analogRead(A0), 0, 1023, 1, 80000);
  int val = map(analogRead(A1), 0, 1023, 0, 20);
  int t = random(15000);
  note(val2,val);
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
  for (int i = 0; i < 256; i +=5) {
    analogWrite(OUT, i); 
    Serial.println(i);  
  }
}

