const int XPin = A0;
const int YPin = A1;
const int ZPin = A2;


//minX 262,MaxX 419, minY 265, Max Y 424, minZ 259, MaxZ 424
//266, 409, 264, 412, 259, 416

int valX,valY,valZ;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);

}

void loop() {
  unsigned long XSum = 0;
  unsigned long YSum = 0;
  unsigned long ZSum = 0;
  
  for (int i=0; i<100; i++) {
    valX = analogRead(XPin);
    valY = analogRead(YPin);
    valZ = analogRead(ZPin);
    XSum+=valX;
    YSum+=valY;
    ZSum+=valZ;
  }
  
  if(digitalRead(2)==LOW){
   digitalWrite(12,HIGH); 
   Serial.print(XSum/100,DEC);
   Serial.print(", ");
   Serial.print(YSum/100,DEC);
   Serial.print(", ");
   Serial.println(ZSum/100,DEC);
   delay(2000);
   digitalWrite(12,LOW); 
  }
  
}
