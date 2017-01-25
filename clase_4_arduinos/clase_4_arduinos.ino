#include <Adafruit_NeoPixel.h> //incluir la libreria

#define PIN 3 //constante (sustituye la palabra PIN por 3)

Adafruit_NeoPixel nLed = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  nLed.begin();//encender la cadena
  nLed.show(); //iniciar con todos apagados
}

void loop(){

  for(int i = 0; i< 16;i++){
    int g = random(255);
    int r = random(255);
    int b = random(255);
    nLed.setPixelColor(i, nLed.Color(g,r,b));
    nLed.show();
    delay(500);
    nLed.setPixelColor(i, nLed.Color(0,0,0));
    nLed.show();
  }

}



