//Gemma Blink


int led = 0;
unsigned long startMillis= millis();
int sensorValue = 0;
#define sensitivity1 500

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(1,INPUT);
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);

}

// the loop routine runs over and over again forever:
void loop() {
  sensorValue =abs(512-analogRead(1));
  if(sensorValue>sensitivity1){
  analogWrite(led,map(sensorValue,0,512,0,255));
  } else{
    digitalWrite(led,LOW);
  }
  
}
