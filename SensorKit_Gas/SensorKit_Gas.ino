#include <LiquidCrystal.h>


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Lectura");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(A1));
  lcd.display();
  delay(300);
}
