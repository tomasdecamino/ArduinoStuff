
float r;
int motorPin = 9;

void setup()
{
}

void loop()
{
  for (r = 100; r < 256; r += 1)
  {
    analogWrite(motorPin, r);
    delay(150);
  }
  delay(1000);
  for (r = 256; r < 100; r -= 0.1)
  {
    analogWrite(motorPin, r);
    delay(350);
  }
  delay(1000);

}

