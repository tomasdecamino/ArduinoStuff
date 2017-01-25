#define M1 200 //mas para RC
#define M0 255

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward(30);
  //delay(5000);
  moveStop();
  moveLeft();
  delay(10000);
  moveStop();
  moveRight();
  delay(10000);
  moveStop();
  moveStop();
  delay(1000);

}

void moveForward(word t) {
  for(int i=0;i<t;i++){
    analogWrite(0, 0);
    analogWrite(1, M1);
    delay(400);
    analogWrite(0, M0);
    analogWrite(1, 0);
    delay(400);
    
  }
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

