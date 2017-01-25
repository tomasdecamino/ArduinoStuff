long lastMillis;
float temp,lastTemp = 0;
boolean flip = false;
int count = 0;

int coldvalPin = 2, 
int hotvalPin = 3;


void setup() {                
  Serial.begin(9600);
  pinMode(coldvalPin, OUTPUT); 
  pinMode(hotvalPin, OUTPUT);
  digitalWrite(coldvalPin, HIGH);  //valvula de agua fria abierta
  digitalWrite(hotvalPin, LOW);  //valvula de agua caliente cerrada
  lastMillis = millis();
  temp = ((analogRead(A0) * 0.004882814)-0.5)*100;
}


void loop() {

  if(flip){
      if(temp>lastTemp){
       digitalWrite(led, LOW);   
       digitalWrite(led, HIGH);   

      } else {
         digitalWrite(led, HIGH);  
         digitalWrite(led, LOW);  
      }
      flip = false;
      count = 0;
  }
  
  lastTemp = temp;
  delay(500);
  temp = ((analogRead(A0) * 0.004882814)-0.5)*100;
  if(abs(temp-lastTemp)>1) count++;
  
}
