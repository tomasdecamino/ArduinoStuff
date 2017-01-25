//Written by TOmas de Camino

int lux;

const int controlPin1R =  2;
const int controlPin2R = 3;
const int controlPin1L =  4;
const int controlPin2L = 5;
const int enablePinR= 9;
const int enablePinL= 10;

void setup(){
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(controlPin1R,OUTPUT);
  pinMode(controlPin2R,OUTPUT);
  pinMode(controlPin1L,OUTPUT);
  pinMode(controlPin2L,OUTPUT); 
  pinMode(enablePinR,OUTPUT);
  pinMode(enablePinL,OUTPUT); 
  digitalWrite(enablePinR,LOW);
  digitalWrite(enablePinL,LOW); 
  digitalWrite(12,HIGH);
}

void loop(){
  lux = constrain(map(analogRead(A0),0,1023,0,2000),0,2000);
  Serial.println(lux);
  int var = random(1,6);
  Serial.println(var);
  int time = random(100,1000);
  switch (var) {
  case 1:
    mForward(100+lux);
    break;
  case 2:
    mStop();
    delay(500);
    break;
  case 3:
    mBackward(time);
    break;
  case 4:
    mRight(time);      
    break;
  case 5:
    mLeft(time);      
    break;
  }


}

void mBackward(int time){
  //motor der
  digitalWrite(controlPin1R,LOW);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,LOW);
  analogWrite(enablePinR,255);
  analogWrite(enablePinL,255);
  delay(time); 
}

void mForward(int time){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,LOW);
  //motor izq
  digitalWrite(controlPin1L,LOW);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinL,255); 
  analogWrite(enablePinR,255);
  delay(time);
}

void mRight(int time){
  //motor der
  digitalWrite(controlPin1R,LOW);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,LOW);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinL,255); 
  analogWrite(enablePinR,255);
  delay(time);
}


void mLeft(int time){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,LOW);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,LOW);
  analogWrite(enablePinL,255); 
  analogWrite(enablePinR,255);
  delay(time);
}

void mStop(){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinR,LOW);
  analogWrite(enablePinL,LOW); 
}


