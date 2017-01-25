void setup() 
{
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() 
{

  float voltage = analogRead(A0);
  Serial.println(voltage); // Print the voltage.
  delay(10); // Delay 1ms
}

