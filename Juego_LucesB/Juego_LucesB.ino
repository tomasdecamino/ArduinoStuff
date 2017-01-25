
boolean r1,r2,r3,r4,r5,r6;
float randR;

void setup(){
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  turnAll(HIGH);
  delay(1000);
  turnAll(LOW);
  r1=true;
  r2=true;
  r3=true;
  r4=true;
  r5=true;
  r6=true;  
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  randR=random(10);
  Serial.print(randR);
  
  if(randR>-1){
    turnRute(2,HIGH);
    turnRute(4,HIGH);
    turnRute(5,HIGH);
    turnRute(6,HIGH);
    turnRute(7,HIGH); 
  
  }
  else{
    turnRute(9,HIGH);
    turnRute(3,HIGH);
    turnRute(2,HIGH); 
  }
}

void loop(){
  delay(200);
  //Serial.println(r1);
  if(r1){
    r1=(digitalRead(A0)==1);
  }
  if(r2){
    r2=(digitalRead(A1)==1);
  }
  if(r3){
    r3=(digitalRead(A2)==1);
  }
  if(r4){
    r4=(digitalRead(A3)==1);
  }
  if(r5){
    r5=(digitalRead(A4)==1);
  }
  if(r6){
    r6=(digitalRead(A5)==1);
  }
  if(!r1){
    turnRute(3,LOW);
    turnRute(4,HIGH);
  }
  /*if(!r2){
    turnRute(7,LOW);
    turnRute(8,HIGH); 
  }*/
  if(!r3&&(randR)){
    for(int j=0;j<10;j++){
      turnAll(HIGH);
      delay(200);
      turnAll(LOW);
      delay(200);
    }
  }
  if(!r4){
    turnRute(2,LOW);
    turnRute(3,LOW);
    turnRute(5,HIGH);
    turnRute(6,HIGH);
    turnRute(7,HIGH);    
  }
  if(!r6){
    for(int j=0;j<10;j++){
      turnAll(HIGH);
      delay(200);
      turnAll(LOW);
      delay(200);
    }
  }  

}

void turnAll(int val){
  for(int i=2;i<12;i++){
    digitalWrite(i,val);
  }

}

void turnRute(int id, int val){
  digitalWrite(id,val); 
}











