#define CENTERL 91
#define CENTERR 89
#define SOFFSET 70

#define LEFTIR 3
#define RIGHTIR 6

int garraPin = 9;
int motorLpin = 2;
int motorRpin = 12;
int lineLpin = 3;
int lineRpin = 6;

Servo garra;
Servo motorL;
Servo motorR;

void stopServos() {
  motorL.write(CENTERL);
  motorR.write(CENTERR);//calibrate stop
}

void adeleBegin() {
  pinMode(INPUT, lineLpin);
  pinMode(INPUT, lineRpin);
  garra.attach(garraPin);
  motorL.attach(motorLpin);
  motorR.attach(motorRpin);
  garra.write(150);
  stopServos();
}



void forward() {
  motorL.write(180 - SOFFSET);
  motorR.write(0 + SOFFSET); //calibrate stop
}

void backward() {
  motorL.write(0 + SOFFSET);
  motorR.write(180 - SOFFSET); //calibrate stop
}

void left() {
  motorL.write(0 + SOFFSET);
  motorR.write(0 + SOFFSET); //calibrate stop
}

void right() {
  motorL.write(180 - SOFFSET);
  motorR.write(180 - SOFFSET); //calibrate stop
}

void closeGarra() {
  garra.write(150);
}

void openGarra() {
  garra.write(90);
}

void stayInside() {//Stays inside line
  if (digitalRead(RIGHTIR) || digitalRead(LEFTIR)) {
    backward();
    delay(300);
    //chooses left or right at random
    if (random(2) == 0) left();
    else right();
    delay(500);
  } else {
    forward();
    delay(10);
  }
}

void followLine() {//simple line follower
  if (digitalRead(RIGHTIR)) {
    right();
    delay(20);
  }
  if (digitalRead(LEFTIR)) {
    left();
    delay(20);
  }
  forward();
  delay(10);
}

void randomMove(int t) {
  int choice = random(4);
  switch (choice) {
    case 1:
      forward();
      break;
    case 2:
      left();
      break;
    case 3:
      right();
      break;
  }
  delay(t);
}

