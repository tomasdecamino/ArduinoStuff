#define LEFTDIR 10
#define RIGHTDIR 11
#define LEFTSPEED 5
#define RIGHTSPEED 6

int leftL, rightL;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pivotLeft(100,200);
  leftL=analogRead(A0);
  pivotRight(100,400);
  rightL=analogRead(A0);  
  stopMotors();
  if(leftL<rightL){
    pivotLeft(100,400);
  }
  
  forward(150,100,1000);

}

void setMotors() {
  pinMode(LEFTDIR, OUTPUT);
  pinMode(LEFTSPEED, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);
  pinMode(RIGHTSPEED, OUTPUT);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
}

//*******Movement functions ********/
//two options with or without delay time
void forward(int mSpeed) {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);

}

void forward(int mSpeed, int t) {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
  delay(t);
}

void forward(int lSpeed, int rSpeed, int t) {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, lSpeed);
  analogWrite(RIGHTSPEED, rSpeed);
  delay(t);
}

void backward(int mSpeed) {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);

}
  
void backward(int mSpeed, int t) {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
  delay(t);
}

void backward(int lSpeed, int rSpeed, int t) {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, lSpeed);
  analogWrite(RIGHTSPEED, rSpeed);
  delay(t);
}

void pivotLeft(int mSpeed) {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
}

void pivotLeft(int mSpeed, int t) {
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
  delay(t);
}

void pivotRight(int mSpeed) {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
}

void pivotRight(int mSpeed, int t) {
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH);
  analogWrite(LEFTSPEED, mSpeed);
  analogWrite(RIGHTSPEED, mSpeed);
  delay(t);
}

void stopMotors() {
//  digitalWrite(LEFTDIR, LOW);
//  digitalWrite(RIGHTDIR, LOW);
  analogWrite(LEFTSPEED, 0);
  analogWrite(RIGHTSPEED, 0);
}

