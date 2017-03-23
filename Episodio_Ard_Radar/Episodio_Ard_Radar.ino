//Tomas de Camino Beck
//www.funcostarica.org

#include <Servo.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN  13
#define ECHO_PIN     12

Servo servo;
int a=0;
int dir=5;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
  {
  Serial.begin(9600);
  servo.attach(9);
  servo.write(0);
  }

void loop()
  {
  
  float cmMsec;
  //lee el tiempo del ultrasonico
  long microsec = ultrasonic.timing();

  //calcula la distancia
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //mandar al puerto serial
  Serial.print(int(cmMsec));
  Serial.print(",");
  Serial.println(a);
  //mover servo
  a+=dir;
  servo.write(a);

  //para que servo cambie de direccion
  if(a==0)dir=5;
  if(a==180)dir=-5;
  //espera
  delay(100);
  }
