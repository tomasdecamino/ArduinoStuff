// @author Tomas de Camino Beck
// www.inventoria.org
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);//inicializa el LCD

OneWire oneWire(A1);//indica donde conectamos el sensor

DallasTemperature sensors(&oneWire);//inicializa la libreria

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  sensors.begin();//inicia las lescturas
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Temperatura C:");
  lcd.setCursor(0, 1);
  sensors.requestTemperatures();//pide las lecturas al sensor
  lcd.print(sensors.getTempCByIndex(0));
  //getTempCByIndex(0) se utiliza 
  //pues se pueden conectar varios sensores
  lcd.display();//muestra la informacion
}
