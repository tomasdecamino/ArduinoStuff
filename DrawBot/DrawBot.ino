#define PWMA 9
#define AIN1 8
#define AIN2 7
#define STBY 6
#define BIN1 5
#define BIN2 4
#define PWMB 3



void setup(){
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT); 
  pinMode(AIN2,OUTPUT); 
  pinMode(STBY,OUTPUT);   
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  digitalWrite(STBY,LOW); 

  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH); 
  Serial.begin(9600);

  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

}

void loop(){
  digitalWrite(STBY,HIGH);
  int mB = 512-analogRead(A0);
  int mA = 512-analogRead(A1);
  if(mB>0){
    left('B');
    int p=map(mB,0,512,0,255);
    analogWrite(PWMB,p);
    digitalWrite(10,p>50);

  }
  else{
    int p=map(512+mB,0,512,0,255);
    right('B');
    analogWrite(PWMB,255-p);
    digitalWrite(10,(255-p)>50); 
  }
  if(mA>0){
    left('A');
    int p=map(mA,0,512,0,255);
    analogWrite(PWMA,p);
    digitalWrite(11,p>50); 
  }
  else{
    int p=map(512+mA,0,512,0,255);
    right('A');
    analogWrite(PWMA,255-p);
    digitalWrite(11,(255-p)>50);  
  }
}

void left(char motor){
  if(motor=='B'){
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
  }
  else{
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
  }

}

void right(char motor){
  if(motor=='B'){
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
  }
  else{
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
  }

}





