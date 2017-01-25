//@author Tomas de Camino Beck
//@version 1.0 Jul/2015

#define TH 50 // loudness time sample
#define MAXV 50 // alias for the loudness threshold
#define AVG 20
#define HOLD 400 // milliseconds on hold

/* microphne values are read as 0 for no noise
and from 0 to 512 negative, and 512 to 1023 positive sgnal*/

unsigned long startMillis = millis();
unsigned long holdMillis = millis();
int sensorValue;// stores de sensor value
unsigned int count;//counts the number of times the sensor value is grater than MAXV
unsigned int iter; //counts the number of times the sensor is read
unsigned long sum = 0;
float a = 29.52;
float b = 62.55;
int maxValue = 0;
float avg = 0;


void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}
void loop()
{
  if (millis() - holdMillis > HOLD) {
    maxValue = 0;
    holdMillis = millis();
  }
  sensorValue = 0;
  count = 0;
  iter = 0;
  startMillis = millis();
  while (millis() - startMillis < TH)
  {
    sensorValue = analogRead(A0) - 512; //makes reading {-512,512}
    avg += abs(sensorValue);
    if (sensorValue > maxValue)maxValue = abs(sensorValue);
    count += (abs(sensorValue) > MAXV); // counts values above TH
    iter++;//number of measurements
    Serial.print(sensorValue);
    Serial.print(",");
    Serial.println(maxValue);
  }


  //writes to serial, milliseconds, p=[0,1]
  //Serial.print(millis());
  //Serial.print(',');
  float p = (float)count / (float)iter; //p goes to 1 as loudness is sustained
 /* Serial.print(p);
  Serial.print(",");
  //Serial.print(avg/(float)iter);
  //Serial.print(",");
  Serial.println(maxValue);*/


}
