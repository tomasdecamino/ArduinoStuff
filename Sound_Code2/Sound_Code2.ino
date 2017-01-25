//@author Tomas de Camino Beck
//@version 1.0 Jul/2015

#define TH 50 // loudness time sample
#define MAXV 50 // alias for the loudness threshold
#define AVG 20

/* microphne values are read as 0 for no noise
and from 0 to 512 negative, and 512 to 1023 positive sgnal*/

unsigned long startMillis = millis();
int sensorValue;// stores de sensor value
unsigned int count;//counts the number of times the sensor value is grater than MAXV
unsigned int iter; //counts the number of times the sensor is read
unsigned long sum = 0;
float avg = 0.0;
int maxValue = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}
void loop()
{
  avg=0.0;
  for (int i = 0; i < AVG; i++) {
    sensorValue = 0;
    count = 0;
    iter = 0;
    maxValue=0;
    while (millis() - startMillis < TH)
    {
      sensorValue = analogRead(A0);
      if(sensorValue>maxValue)maxValue=sensorValue;
      count += (sensorValue > MAXV); // counts values above TH
      iter++;//number of measurements
    }
    avg += ((float)count / (float)iter);
    startMillis = millis();

  }
  //writes to serial, milliseconds, p=[0,1]
  //Serial.print(millis());
  //Serial.print(',');
  float p = avg/AVG; //p goes to 1 as loudness is sustained
  Serial.println(p);

}
