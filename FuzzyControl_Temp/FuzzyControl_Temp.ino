// @author Tomas de Camino Beck
// www.inventoria.org
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FuzzyControl.h>

#define AMP 40
#define TT

float t = 0.0;
float off = 0.0;
float deltaTemp = 0;

fuzzyDomain temp, delta, out;

OneWire oneWire(A1);
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  sensors.begin();//inicia las lescturas del sensor

  //Crea Dominios
  temp.nset=3;
  temp.fset = new fuzzyDef[temp.nset];
  delta.nset=3;
  delta.fset = new fuzzyDef[temp.nset];
  out.nset=5;
  out.fset = new fuzzyDef[temp.nset];

  //rango de acci'on
  setDomain(&temp,TT-5,TT+5);
  setDomain(&delta,-2,2);
  setDomain(&out,0,1);
  
  Serial.begin(9600);
}

void loop() {
  // Leer sensores

  sensors.requestTemperatures();//pide las lecturas al sensor

  //Inferencia

  //Defuzificacion


  //Esta es una forma de controlar encendido y apagado
  //el ciclo se controla con la variable 0<=off<=1
  abs(sin(AMP * t)) > off ? digitalWrite(2, HIGH) : digitalWrite(2, LOW);
  t += 0.01;//para ir creando los ciclos 

  
  Serial.println(sensors.getTempCByIndex(0));
}
