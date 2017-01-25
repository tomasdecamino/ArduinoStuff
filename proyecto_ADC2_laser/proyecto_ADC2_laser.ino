int th = 200;

void setup(){
  Serial.begin(9600); 
}

void loop(){
  int sensor0 =analogRead(A0);
  int sensor1 =analogRead(A1);
  //int sensor1 =100;

  Serial.print(sensor0);
  Serial.print(',');  
  Serial.println(sensor1);

  if((sensor0 <th) && (sensor1)<th){
    noTone(6); 
  }
  else{
    tone(6,680);

  }
  //delay(500);
}


