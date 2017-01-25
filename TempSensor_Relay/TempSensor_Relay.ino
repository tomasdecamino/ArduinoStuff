// @author Tomas de Camino Beck
// www.inventoria.org
#include <OneWire.h>
#include <DallasTemperature.h>
#include <FuzzyControl.h>

float t = 0.0;
float amp = 40;
float off = 0.3;

OneWire oneWire(A1);//indica donde conectamos el sensor

DallasTemperature sensors(&oneWire);//inicializa la libreria

void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  sensors.begin();//inicia las lescturas
  digitalWrite(2, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensors.requestTemperatures();//pide las lecturas al sensor

  abs(sin(amp * t)) > off ? digitalWrite(2, HIGH) : digitalWrite(2, LOW);
  t += 0.01;
  Serial.println(sensors.getTempCByIndex(0));
}
