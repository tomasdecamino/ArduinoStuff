
#include <CapacitiveSensor.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);
CapacitiveSensor capSensor2 = CapacitiveSensor(4,3);

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(30);
  long sensorValue2 = capSensor2.capacitiveSensor(30);
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(sensorValue2);
  delay(500);
}



