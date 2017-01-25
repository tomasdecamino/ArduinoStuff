const int sensorPin = 0;
const int sensorPin2 = 1;

void setup(){
 Serial.begin(9600);
  
}

void loop(){
  int l = map(analogRead(sensorPin),0,1023,0,255);
  int l2 = map(analogRead(sensorPin2),0,1023,0,255);
  Serial.print(l);
  Serial.print(",");
  Serial.println(l2);
  delay(100);
  
}
