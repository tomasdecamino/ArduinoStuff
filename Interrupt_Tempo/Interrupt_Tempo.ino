long last = millis();
volatile long delayTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  attachInterrupt(0, tempo, RISING);
  Serial.begin(9600);
  last = millis();
}

void tempo(){
  long d=millis()-last;
  if(d>0)delayTime = d;
  last=millis();
}

void loop() {
 Serial.println(delayTime);
}
