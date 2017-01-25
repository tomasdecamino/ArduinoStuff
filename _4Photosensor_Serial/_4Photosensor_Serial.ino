const int sensorPin0 = A0;
const int sensorPin1 = A1;
const int sensorPin2 = A2;
const int sensorPin3 = A3;

  
void setup()
{
  Serial.begin(9600);

}


void loop(){
  Serial.print(analogRead(sensorPin0));
  Serial.print(",");
  Serial.print(analogRead(sensorPin1));
  Serial.print(",");  
  Serial.print(analogRead(sensorPin2));
  Serial.print(",");  
  Serial.println(analogRead(sensorPin3));
  delay(50);
 
  
  
}


