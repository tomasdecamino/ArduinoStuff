#define PWMA 3
#define AIN1 4
#define AIN2 5
#define STBY 6
#define BIN1 7
#define BIN2 8
#define PWMB 9



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
}

void loop(){
  digitalWrite(STBY,HIGH);
  Serial.println(240/255.0 * 6.0);
  analogWrite(PWMA,255);
 /* for(int i=0;i<230;i++){
    
   
   analogWrite(PWMA,i);
   delay(1000);
  }8?
  delay(2000);
  digitalWrite(STBY,LOW);
  delay(2000);*/
  
}
