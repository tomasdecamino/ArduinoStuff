#define DIR_PIN 3
#define STEP_PIN 2
#define STOP_PIN 4
#define EN_PIN 5

#define DIR_PIN2 7
#define STEP_PIN2 6
#define STOP_PIN2 8
#define EN_PIN2 9

#define MAXY 6900
#define MAXX 6900

int aX,aY,aZ;

int countY=0;
int countX=0;
int s=100;
int dirX=1;
int dirY=1;

void setup() { 
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(DIR_PIN2, OUTPUT); 
  pinMode(STEP_PIN2, OUTPUT);
  pinMode(EN_PIN2, OUTPUT);
  pinMode(STOP_PIN2, INPUT_PULLUP);
  digitalWrite(EN_PIN,LOW);
  digitalWrite(EN_PIN2,LOW);
  Serial.begin(9600);
  //delay(10000); 
  resetY();
  resetX();
  moveTo(MAXX/2,MAXY/2);

} 

void loop(){ 
   //Serial.print(aX-analogRead(A0));
   //Serial.print(",");
   //Serial.print(aY-analogRead(A1));
   //Serial.print(",");
   //Serial.println(aZ);
   
 /*  if (abs(aX-analogRead(A0))>10){
      rotate(DIR_PIN,STEP_PIN,aX-analogRead(A0), .1);
   } 
   if (abs(aY-analogRead(A1))>10){
      rotate(DIR_PIN2,STEP_PIN2,-(aY-analogRead(A1)), .1);
   }
   */
  //s+=50;
  //rotate(DIR_PIN,STEP_PIN,s, .1);
  //rotate(DIR_PIN2,STEP_PIN2,s, .1);
  //rotate(DIR_PIN,STEP_PIN,aX-analogRead(A0), .1);
  //rotate(DIR_PIN2,STEP_PIN2,-(aY-analogRead(A1)), .1);
  //rotate(DIR_PIN2,STEP_PIN2,-2*s, .1);  
  Serial.println(digitalRead(STOP_PIN));
  if(digitalRead(STOP_PIN)==0){
    rotate(DIR_PIN,STEP_PIN,10,0.03);
  }else{
    rotate(DIR_PIN,STEP_PIN,-10,0.03); 
  }
  if(digitalRead(STOP_PIN2)==0){
    rotate(DIR_PIN2,STEP_PIN2,10,0.03);
  }else{
    rotate(DIR_PIN2,STEP_PIN2,-10,0.03); 
  }
  //moveTo(10*dirX,10*dirY);
}



void rotate(int dirpin, int steppin,int steps, float speed){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  
  steps = abs(steps);

  digitalWrite(dirpin,dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(steppin, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(steppin, LOW); 
    delayMicroseconds(usDelay); 
  } 
} 

void rotateDeg(float deg, float speed){ 
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0)? HIGH:LOW;
  digitalWrite(DIR_PIN,dir); 

  int steps = abs(deg)*(1/0.225);
  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
}

void resetY(){
 while(digitalRead(STOP_PIN2)==1){
   rotate(DIR_PIN2,STEP_PIN2,1, 0.03);
   countY++;
 }
 Serial.println(countY);
 rotate(DIR_PIN2,STEP_PIN2,-50, .03);
 delay(100);
 rotate(DIR_PIN2,STEP_PIN2,10, .03);
 delay(100); 
 countY=0;
}

void resetX(){
 while(digitalRead(STOP_PIN)==1){
   rotate(DIR_PIN,STEP_PIN,-1,.03);
   countX++;
 }
 Serial.println(countX);
 rotate(DIR_PIN,STEP_PIN,50, .03);
 delay(100);
 rotate(DIR_PIN,STEP_PIN,-10, .03);
 delay(100);
 countX=0; 
}

void moveTo(int x, int y){
  if(x>10&&x<MAXX){
   rotate(DIR_PIN,STEP_PIN,x-countX,0.03);
  }
  if(y>100&&y<MAXY){
    rotate(DIR_PIN2,STEP_PIN2,countY-y,0.03);
  }
  countX=x;
  countY=y;
  Serial.print(countX);
  Serial.print(",");
  Serial.println(countY);
}
