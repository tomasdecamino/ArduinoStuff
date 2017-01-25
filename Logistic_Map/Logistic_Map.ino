// Random blink using chaos
// logistic Map for Chaos
// @author Tomas de Camino Beck
// www.funcostarica.org

float n=0.1; //population size
float r = 3;// biotic potential

void setup() {
  Serial.begin(9600);// Initialice serial
  pinMode(A0,INPUT);  // Potentiometer
  pinMode(13,OUTPUT); // Led
}

void loop() {
  Serial.println(n);// send n to serial port
  //chane r using potentiometer
  int val = analogRead(A0); //read potentiometer
  r = constrain((float)(val+1)/1025 * 3,2,3); 
  // calculate population
  n+=r*n*(1-n);
  //Turn led on/off based on population size
  if(n>=1){
    digitalWrite(13,HIGH);
    
  }else{
    digitalWrite(13,LOW);
  }
  delay(100);
}
