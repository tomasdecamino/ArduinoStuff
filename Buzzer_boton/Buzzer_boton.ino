//@author Tomas de Camino Beck
// inventoria.org & funcostarica.org

void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int boton = digitalRead(2);
  if(boton==0){
    tone(6,440);
  } else{
    noTone(6);
  }
}
