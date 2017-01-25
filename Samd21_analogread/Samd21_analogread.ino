void setup() 
{

  analogReadResolution(12); // Set analog input resolution to max, 12-bits
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  SerialUSB.begin(9600);
}

void loop() 
{

  int x = analogRead(A0);
  int z = analogRead(A1);
  SerialUSB.print(x);
  SerialUSB.print(",");
  SerialUSB.println(z); // Print the voltage.
  delay(50); // Delay 10ms
}

