#include <Servo.h>

#define DISP 2
#define M 5
#define TIME 100

Servo servoX, servoY;
int posX = 90;
int posY = 90;
int lx1, lx2, ly1, ly2;

void setup() {
  // put your setup code here, to run once:
  servoX.attach(2);
  servoY.attach(3);
  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  // put your main code here, to run repeatedly:
  servoX.write(posX + DISP);
  delay(TIME);
  lx1 = analogRead(A0);
  servoX.write(posX - DISP);
  delay(TIME);
  lx2 = analogRead(A0);
  servoX.write(posX);
  delay(TIME);
  servoY.write(posY + DISP);
  delay(TIME);
  ly1 = analogRead(A0);
  servoY.write(posY - DISP);
  delay(TIME);
  ly2 = analogRead(A0);
  servoY.write(posY);
  //delay(1000);
  if(lx1<lx2) posX+=M;
  else posX-=M;
  if(ly1<ly2) posY+=M;
  else posY-=M;


}
