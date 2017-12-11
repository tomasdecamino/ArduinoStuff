#define CENTERL 91
#define CENTERR 89
#define SOFFSET 70

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
  motorL.write(180-SOFFSET);
  motorR.write(0+SOFFSET);//calibrate stop
}

void backward() {
  motorL.write(0+SOFFSET);
  motorR.write(180-SOFFSET);//calibrate stop
}

void left() {
  motorL.write(0+SOFFSET);
  motorR.write(0+SOFFSET);//calibrate stop
}

void right() {
  motorL.write(180-SOFFSET);
  motorR.write(180-SOFFSET);//calibrate stop
}

void closeGarra(){
  garra.write(150);
}

void openGarra(){
  garra.write(90);
}

