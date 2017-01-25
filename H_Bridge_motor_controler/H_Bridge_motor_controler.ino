const int controlPin1 =  2;
const int controlPin2 = 3;
const int enablePin= 9;

void setup(){
 pinMode(controlPin1,OUTPUT);
 pinMode(controlPin2,OUTPUT);
 pinMode(enablePin,OUTPUT); 
 digitalWrite(enablePin,LOW);
 Serial.begin(9600);
 
}

void loop(){
 digitalWrite(controlPin1,HIGH);
 digitalWrite(controlPin2,LOW); 
 for(int i =0; i<200;i++){
   analogWrite(enablePin,i);
   Serial.println(i);
   delay(500); 
 } 
}
