int p = 5;
int val = 0;
long lastMillis = micros();

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  val = map(analogRead(A0), 0, 1023, 0, 15000);
  p = map(analogRead(A1), 0, 1023, 10000, 50000);
  sawTooth();
  if(micros()-lastMillis>p) delayMicroseconds(15000-p);

}

void sawTooth() {
  for (int i = 0; i < 256; i ++) {
    analogWrite(9, i);

  }
  digitalWrite(9, LOW);
  delayMicroseconds(val);
}

void triangle() {
  for (int i = 0; i < 256; i ++) {
    analogWrite(9, i);

  }
  for (int i = 255; i > -1; i --) {
    analogWrite(9, i);

  }
  digitalWrite(9, LOW);
  delayMicroseconds(val);
}

void square() {
  digitalWrite(9, HIGH);
  delayMicroseconds(val);
  digitalWrite(9, LOW);
  delayMicroseconds(val);
}




