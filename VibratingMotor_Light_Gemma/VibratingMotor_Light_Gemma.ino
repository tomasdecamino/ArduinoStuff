//tomas de camino
//Gemma robot

#define sense 256

int motor = 0; //motor de vibracion de 3V
int sensorValue = 0;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(1,INPUT); //fotoresitor

}

void loop() {
    sensorValue =analogRead(1);
    if(sensorValue < sense){
      analogWrite(motor,map(255-constrain(sensorValue,0,255),0,255,100,255)); 
    }else{
      analogWrite(motor, LOW);
    }
    delay(500);
}
