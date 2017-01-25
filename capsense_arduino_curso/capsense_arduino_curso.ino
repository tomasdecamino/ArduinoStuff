#include <CapacitiveSensor.h>

CapacitiveSensor a = CapacitiveSensor(5,2);// Pin 5 emisor y Pin 2 Receptor  1Mohm
CapacitiveSensor b = CapacitiveSensor(6,3);// Pin 5 emisor y Pin 3 Receptor  330Kohm
CapacitiveSensor c = CapacitiveSensor(7,4);// Pin 5 emisor y Pin 4 Receptor  47Kohm

void setup(){
    pinMode(13,OUTPUT);
    a.set_CS_AutocaL_Millis(0xFFFFFFFF);//apaga autocalibrado
    Serial.begin(9600);
}

void loop(){
     int sensA = a.capacitiveSensor(60);//leer el valor capacitivo del sensor A
     int sensB = b.capacitiveSensor(60);//leer el valor capacitivo del sensor B
     int sensC = c.capacitiveSensor(60);//leer el valor capacitivo del sensor C
     
     Serial.print("Sensor A: ");
     Serial.print(sensA);
     Serial.print(" Sensor B: ");
     Serial.print(sensB);
     Serial.print(" Sensor C: ");
     Serial.println(sensC);
     
     if(sensA > 500){
       digitalWrite(13,HIGH);
     }
     else{
       digitalWrite(13,LOW);
     }
     
     delay(10);
     
}


