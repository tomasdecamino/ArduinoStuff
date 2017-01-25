/*
   @author  Tomás de Camino Beck
   www.inventoria.org
*/

int cont1 =0;

void setup() {
  Serial.begin(9600);//inicia el puerto serial
}

void loop() {
  int cont2=0;
  cont1 = cont1 + 1;
  Serial.println(cont1);
  cont2 = cont2 + 1;
  Serial.println(cont2);
}
