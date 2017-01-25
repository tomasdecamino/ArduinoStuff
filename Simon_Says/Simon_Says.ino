#include <Adafruit_NeoPixel.h>
#include <Servo.h> 

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
Servo servo; 


long micVal,gameStart;
boolean playing=false;
boolean waitPrize=false;
int scream=0;
int maxLevel=0;
int incomingByte;

void setup(){
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(4,OUTPUT);
  
  strip.begin();
  strip.show();
  servo.attach(9);
  servo.write(45);


}

void loop(){
  int count=0;
  if(!playing && !waitPrize){
    servo.write(45);
    colorWipe(strip.Color(255, 0,0), 50,true);
    colorWipe(strip.Color(0, 0, 0), 0,true); 
    colorWipe(strip.Color(255, 0, 0), 50,false);
    colorWipe(strip.Color(0, 0, 0), 0,true); 
    long startMillis = millis();
    Serial.println(0);
    count = 0;
    while(millis()-startMillis<5000){
      delay(50);
      count+=digitalRead(2);
    }
    playing=count>30;
    if(playing){
      gameStart=millis();
      for (int i=0;i<3;i++){
        servo.write(45);
        colorWipe(strip.Color(255, 255, 255), 60,true);
        colorWipe(strip.Color(0, 0, 0), 0,true);
        delay(100);
        maxLevel=0;
      }
      Serial.println(1);
    }// Blue
  }  
  if(playing){
    micVal=0;
    long startMillis = millis();
    while(millis()-startMillis<20){
      int tmp =512-analogRead(A0);
      micVal += abs(tmp);
    }
    scream = map(micVal,0,80000,0,8);
    maxLevel=max(maxLevel,scream);
    Serial.println(maxLevel+1);
    colorLevel(maxLevel);

    playing=!((scream==0)&&(millis()-gameStart>15000));
    if(maxLevel==8){
      waitPrize=true;
      playing=false;
      maxLevel=0;
    }
    delay(100);
  }
  if(waitPrize){
    servo.write(45);
    colorWipe(strip.Color(128, 0, 255), 50,true);
    colorWipe(strip.Color(0, 0, 0), 50,true);
    if(Serial.available()){
      incomingByte = Serial.read();
      if(incomingByte==48){
        Serial.flush();
        waitPrize=false;
        playing=false;
        maxLevel=0;
        delay(8000);
        Serial.println(0);
      }
      if(incomingByte==49){
        Serial.flush();
        Serial.println(0);
        waitPrize=false;
        playing=false;
        maxLevel=0;
        digitalWrite(4,HIGH);
        servo.write(150);
        delay(150);
        servo.write(45);
        delay(5000);
        digitalWrite(4,LOW);
        colorWipe(strip.Color(255, 255, 255), 200,true);
        colorWipe(strip.Color(0, 0, 0), 0,true);
      }
    } 
  }

}

void colorLevel(long level) {
  for(int i=0; i<strip.numPixels(); i++) {
    if(i<level){  
      strip.setPixelColor(i, strip.Color(255*i/7, (255-(200*i/7)), 0));
    }
    else{
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
  }
  strip.show();
}

void colorWipe(uint32_t c, uint8_t wait,boolean right) {
  if(right){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }
  else{
    for(uint16_t i=strip.numPixels();i>0; i--) {
      strip.setPixelColor(i-1, c);
      strip.show();
      delay(wait);
    } 
  }
}








