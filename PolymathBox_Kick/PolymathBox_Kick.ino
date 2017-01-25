/* Tomas de Camino Beck
    www.inventoria.org
*/

float a = 0.0;
long lastMillis = millis();
byte beats[] = {1, 0, 0, 0, 2, 0, 2, 0, 1, 0, 0, 0, 2, 0, 0, 0};

long last = millis();
volatile long delayTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  attachInterrupt(0, tempo, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.println(delayTime);
  int val = map(analogRead(A0), 0, 1023, 100, 1000);
  long m = millis();
  for (int i = 0; i < 16; i++) {
    switch (beats[i]) {
      case 0:
        nothing();
        break;
      case 1:
        kick();
        break;
      case 2:
        snare();
        break;
    }
    digitalWrite(9, LOW);
    delay(delayTime-2);
  }


}

void kick() {
  digitalWrite(9, HIGH);
  delay(1);
  digitalWrite(9, LOW);
  while (millis() - lastMillis < 700) {
    triangle(16000);
  }
  lastMillis = millis();
  digitalWrite(9, HIGH);
  delay(1);
  digitalWrite(9, LOW);

}



void triangle(int m) {
  for (int i = 0; i < 256; i += 2) {
    analogWrite(9, i);

  }
  digitalWrite(9, LOW);
  delayMicroseconds(m);
}

void snare() {

  for (int i = 0; i < 50; i++) {
    analogWrite(9, random(255));
    delayMicroseconds(100);
  }
  digitalWrite(9, LOW);
  delay(1);
}

void nothing() {
  digitalWrite(9, LOW);
  delay(1);

}

void tempo(){
  long d=millis()-last;
  if(d>0)delayTime = d;
  last=millis();
}

