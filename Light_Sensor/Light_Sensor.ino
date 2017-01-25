// @author Tomas de Camino Beck
// inventoria.org & funcostarica.org

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);// inicia el pin A0
  Serial.begin(9600);//inicia el puerto serial a 9600
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);//leer el sensor
  Serial.println(val);//manda el valor a puerto serial
  delay(200);//espera 200 mili-segundos
}
