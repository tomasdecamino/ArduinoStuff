
#include <CapacitiveSensor.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(80);
  Serial.println(sensorValue);
  if(sensorValue>1000){
    tone(8,sensorValue/10,50);
  } else {
   noTone(8); 
  }
  delay(100);
}



