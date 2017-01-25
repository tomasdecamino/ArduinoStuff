long startmillis = millis();
int val=0;

void setup(){
 Serial.begin(9600);
  
}

void loop(){
 startmillis = millis();
 while(millis()-startmillis<50){
   val+=analogRead(A0);
 }
 Serial.println(constrain(map(val,400,8000,0,255),0,255));
 val=0;
  
}
