float t=0.0;
float amp =0.001;
boolean on=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//timer function
 amp=0.1;//set On time
 float off=0.5;  //offtime 0 - 1, 0 always on
 abs(sin(amp*t))>off? digitalWrite(13,HIGH) : digitalWrite(13,LOW);
 t+=0.1;
 Serial.println(amp);
}
