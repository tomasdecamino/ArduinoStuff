#define TIME 200
#define LIGHT 200

void setup(){
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT); 

}

void loop(){
  if(analogRead(1)<LIGHT){
    moveLeft(TIME);
    int l=analogRead(1);
    moveRight(2*TIME);
    int r=analogRead(1);
    moveLeft(TIME);
    if(l>r){
      moveLeft(TIME);
    }else{
      moveRight(TIME);
    }
  }
  delay(500);
}

void moveLeft(int time){
  digitalWrite(0,HIGH);
  delay(time);
  digitalWrite(0,LOW);
}

void moveRight(int time){
  digitalWrite(1,HIGH);
  delay(time);
  digitalWrite(1,LOW);
}


