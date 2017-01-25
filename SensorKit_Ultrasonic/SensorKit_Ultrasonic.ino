#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup()
{
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
  lcd.begin(16, 2);
}

void loop()
{
  digitalWrite(A1, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(A1, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(A1, LOW); // Holdoff
  digitalWrite(A2, HIGH); // Turn on pullup resistor
  unsigned long echo = pulseIn(A2, HIGH); //Listen for echo
  float distance = (echo / 58.138); //convert to CM 
  lcd.setCursor(0, 0);
  lcd.print("Distancia (cm):");
  lcd.setCursor(0, 1);
  lcd.print("               ");//clear line
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.display();
  delay(500);
}
