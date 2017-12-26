#define SENSOR1 A0
#define SENSOR2 A1
#define SENSOR3 A3
#define TH 100

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  int s1 = analogRead(SENSOR1);
  int s2 = analogRead(SENSOR2);
  int s3 = analogRead(SENSOR3);
  if(equalQ(s1,s2,TH)&&equalQ(s1,s3,TH)&&equalQ(s2,s3,TH)){
    Serial.println((s1+s2+s3)/3);
  }else{
    Serial.println("Botella volteada");
  }
}

boolean equalQ(int a, int b, int th){
  int dif = a-b;
  return abs(dif)>th;
}
