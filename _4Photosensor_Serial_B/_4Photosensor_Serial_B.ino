const int sensorPin0 = A0;
const int sensorPin1 = A1;
const int sensorPin2 = A2;
const int sensorPin3 = A3;
int min = 0;
int max = 0;
int switchState = 0;
  
void setup()
{
  Serial.begin(9600);
  pinMode(8,INPUT);
}


void loop(){
  switchState = digitalRead(8);
  if(switchState==0){
  Serial.print(getValue(sensorPin0));
  Serial.print(",");
  Serial.print(getValue(sensorPin1));
  Serial.print(",");  
  Serial.print(getValue(sensorPin2));
  Serial.print(",");  
  Serial.println(getValue(sensorPin3));
  } else {
   calibrate();
   Serial.println("0,0,0,0");
  }
  delay(50);
  
  
}

void calibrate(){
  int l0 =analogRead(sensorPin0);
  int l1 =analogRead(sensorPin1);
    if(l0>max){
     max = l0; 
    }
    if(l1<min){
     min = l1; 
    }
}

int getValue(int pin){
  int val = analogRead(pin);
  val = map(val,min,max,0,255);
  val =  constrain(val,min,max);
  return(val);
}

