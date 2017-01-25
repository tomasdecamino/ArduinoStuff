void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available())
  {
    Serial.print("Decimal value: ");
    Serial.print(Serial.read());
    Serial.println();
  }  
}

