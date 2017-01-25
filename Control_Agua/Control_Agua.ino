long lastMillis;
float temp,lastTemp = 0;
boolean flip = false;
int count = 0;
int coldvalPin = 2; 
int hotvalPin = 3;
void setup() {                
  Serial.begin(9600);
  pinMode(coldvalPin, OUTPUT); 
  pinMode(hotvalPin, OUTPUT);
  digitalWrite(coldvalPin, HIGH);  //valvula de agua fria abierta
  digitalWrite(hotvalPin, LOW);  //valvula de agua caliente cerrada
  lastMillis = millis();
  temp = ((analogRead(A0)/1024.0*5.0)-0.5)*100;
}
void loop() {
 
  while((millis()-lastMillis)<2000);
  temp = ((analogRead(A0) * 0.004882814)-0.5)*100;
  Serial.println(temp);
  if(temp>28){
     digitalWrite(coldvalPin, LOW);  //valvula de agua fria abierta
     digitalWrite(hotvalPin, HIGH);  //valvula de agua caliente cerrada
  }else{
    digitalWrite(coldvalPin, LOW);  //valvula de agua fria abierta
    digitalWrite(hotvalPin, HIGH);  //valvula de agua caliente cerrada
  }
  lastMillis=millis();
}
