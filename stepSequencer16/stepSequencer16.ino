#include <Adafruit_NeoPixel.h>
int currentStep = 16;
boolean steps[] = {true, false, true, false, true, false, true, false,true, false, true, false, true, false, true, false};
int encoderPin1 = 2;
int encoderPin2 = 3;
int buttonPin = 4;
int state = 0;

volatile int lastEncoded = 0;
volatile int encoderValue = 500;
volatile int pos=0;


long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

long lastMillis = millis();

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5,OUTPUT);

  pinMode(10,OUTPUT);
  pinMode(9,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on


  strip.setBrightness(64);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(buttonPin))state = (state + 1) % 2;
  if(steps[currentStep]) digitalWrite(10,HIGH);
  else digitalWrite(10,LOW);
  if (millis() - lastMillis > encoderValue) {
    colorStep(currentStep);
    currentStep = (currentStep + 1) % 16;
    lastMillis = millis();
  }
  if(!digitalRead(9)){
    steps[15-(pos/10)]=!steps[15-(pos/10)];
    //state=0;
  }
  delay(10);
  digitalWrite(5,HIGH);
  digitalWrite(5,LOW);

}

void colorStep(uint8_t s) {
  for (uint16_t i = 0; i < strip.numPixels(); i+=1) {
    if (steps[i]) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      //strip.setPixelColor(i+1, strip.Color(255, 0, 0));
    }
    else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
     // strip.setPixelColor(i+1, strip.Color(0, 0, 0));
    }
  }
  if (state==1) {
   // strip.setPixelColor(s, strip.Color(50, 200, 0));
    strip.setPixelColor((15-(pos/10)), strip.Color(200, 255, 255));
    if(steps[15-(pos/10)]) strip.setPixelColor((15-(pos/10)), strip.Color(178, 58,238));
    else strip.setPixelColor((15-(pos/10)), strip.Color(200, 255, 255));
  }
  else if(state==0) {
    strip.setPixelColor(s, strip.Color(0, 200, 0));
   // strip.setPixelColor(s + 1, strip.Color(0, 200, 0));
  }

  strip.show();
}

void updateEncoder() {
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (state==1) {
    //if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)  steps[8-(pos/10)]=!steps[8-(pos/10)];
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)  pos = (pos+1)%160;
  } else if(state==0){
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue = constrain(encoderValue -= 1, 10, 1000);
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue = constrain(encoderValue += 1, 10, 1000);
  }
  lastEncoded = encoded; //store this value for next time
}
