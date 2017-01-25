/* Tomas de Camino Beck
    www.inventoria.org
*/
#define OUT 3
#define TEMPO 10

volatile long delayTime = 100;
long last = millis();


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);

  pinMode(A0, INPUT_PULLUP);
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

  pinMode(3, OUTPUT);

  //  Serial.begin(9600);

  attachInterrupt(0, tempo, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(delayTime);
  if (!digitalRead(A0)) {
    note(20000, 1);
  }
  digitalWrite(OUT, LOW);
  delay(delayTime*2);

}

void note(int n, int l) {
  for (int i = 0; i < l; i ++) {
    triangle();
    delayMicroseconds(n);
    digitalWrite(OUT, LOW);
    delayMicroseconds(n);
  }

}

void triangle() {
  for (int i = 0; i < 256; i ++) {
    analogWrite(OUT, i);

  }
  for (int i = 255; i > -1; i --) {
    analogWrite(OUT, i);
  }

}


void tempo() {
  long d = millis() - last;
  if (d > 0)delayTime = d;
  last = millis();
}
