#include <Servo.h> 
Servo frontLegs;
Servo rearLegs;

void setup(){

  frontLegs.attach(10);
  rearLegs.attach(11);
  frontLegs.write(90);
  rearLegs.write(90);
  delay(4000);

}

void loop(){
  //moveStep();
  moveLeft();
  
}

void moveStep(){
  frontLegs.write(105);
  delay(500);
  rearLegs.write(125);
  delay(500);
  //move right
  frontLegs.write(85);
  delay(500);
  rearLegs.write(45);
  delay(500);
}

void moveBack(){
  frontLegs.write(85);
  delay(500);
  rearLegs.write(125);
  delay(500);
  //move right
  frontLegs.write(105);
  delay(500);
  rearLegs.write(45);
  delay(500);
}

void moveRight(){
  if(frontLegs.read()!=30){
    frontLegs.write(90);
    delay(500);
    frontLegs.write(30);
  }
  frontLegs.write(30);
  delay(500);
  rearLegs.write(105);
  delay(500);
  rearLegs.write(65);
  delay(500);
}

void moveLeft(){
  if(frontLegs.read()!=150){
    frontLegs.write(90);
    delay(500);
    frontLegs.write(150);
  }

  frontLegs.write(150);
  delay(500);
  rearLegs.write(105);
  delay(500);
  rearLegs.write(65);
  delay(500);
}
