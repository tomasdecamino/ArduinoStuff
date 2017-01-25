#define M1 200 //mas para RC
#define M0 220

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward();
  delay(2000);
  moveStop();
  moveLeft();
  delay(1000);
  moveStop();
  moveRight();
  delay(1000);
  moveStop();
  delay(1000);

}

void moveForward() {
  analogWrite(0, M0);
  analogWrite(1, M1);
}


void moveLeft() {
  analogWrite(0, 0);
  analogWrite(1, M1);
}

void moveRight() {
  analogWrite(0, M0);
  analogWrite(1, 0);
}

void moveStop() {
  analogWrite(0, 0);
  analogWrite(1, 0);
}

