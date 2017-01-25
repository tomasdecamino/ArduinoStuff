// @author Tomas de Camino Beck
// @version 1.0
// Inventoria.org y funcostarica.org

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT); //inicia pin A0
  Serial.begin(9600); //inicia el puerto serial
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(A0);//lee el pin analogo
  float voltage = (float)reading/1024*5.0;// convierte a voltios
  float temperatureC = (voltage - 0.5) * 100 ;//convierte a celsius
  Serial.println(temperatureC);// los manda al puerto serial
  delay(200);
}
