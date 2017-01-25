
#include <CapacitiveSensor.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);

void setup() {
  
  Serial.begin(9600);
  capSensor.reset_CS_AutoCal();

}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(80);
  if(sensorValue >100){
    Serial.println(sensorValue);
    //capSensor.reset_CS_AutoCal();
  } else{
    Serial.println(0);
  }
  delay(100);
}



