#define BT0 2
#define BT1 3
#define BT2 4
#define BT3 5

void setup() {
  // put your setup code here, to run once:
  pinMode(BT0, OUTPUT);
  pinMode(BT1, OUTPUT);
  pinMode(BT2, OUTPUT);
  pinMode(BT3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int f= analogRead(A0);
  wave(f);
}

void wave(int f){
  step(0);
  delayMicroseconds(f);
  step(15);
  delayMicroseconds(f);
}

void step(byte n) {
  digitalWrite(BT0, bitRead(n, 0));
  digitalWrite(BT1, bitRead(n, 1));
  digitalWrite(BT2, bitRead(n, 2));
  digitalWrite(BT3, bitRead(n, 3));

}

