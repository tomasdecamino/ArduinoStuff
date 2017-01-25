//Written by TOmas de Camino

int lux;

const int controlPin1R =  2;
const int controlPin2R = 3;
const int controlPin1L =  4;
const int controlPin2L = 5;
const int enablePinR= 9;
const int enablePinL= 10;
int l1,l2;

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
  Serial.print(lux);
  mRight(1000);
  l1 =  constrain(map(analogRead(A0),0,1023,0,2000),0,2000);
  mLeft(2000);
  l2=  constrain(map(analogRead(A0),0,1023,0,2000),0,2000);
  if(l2>l1){
   mForward(1000);
  } else{
   mRight(1500);
   mForward(1000); 
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


