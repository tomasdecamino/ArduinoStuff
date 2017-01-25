#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
              
void setup()
{
  Serial.begin(9600);
  Mouse.begin();
  pinMode(13, OUTPUT);
  myservo.attach(6);
  
}



void loop()
{
   // digitalWrite(13, HIGH);
   // myservo.write(0);
   // delay(2000);
    digitalWrite(13, LOW);
    for(int i = 0; i <= 80; i++){
      myservo.write(i);
      delay(200);
      Serial.println(i);
    }

}


