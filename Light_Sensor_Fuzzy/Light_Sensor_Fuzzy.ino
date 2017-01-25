/***************************************************
  Fuzzy Example

  by Tomás de Camino Beck
  www.funcostarica.org

  License:

  This example was created by Tomàs de Camino Beck (tomas@funcostarica.org)
  and is released under an open source MIT license.  See details at:
    http://opensource.org/licenses/MIT

 ****************************************************/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//We will use a structured data type to create label type def
//in C++ struct is a public object.
struct fuzzyDef {
  float mina = 0;
  float minb = 0;
  float maxa = 0;
  float maxb = 0;
  float (*membership)(fuzzyDef, float);//pointer to membership function
  float miu=0.0;//to store current membership or fuzzy weight for defuzzification
};
 
//to create the entire domain of discourse for a fuzzy variable
struct fuzzyDomain {
  fuzzyDef* fset ;
};


fuzzyDomain light;



void setup() {

  Serial.begin(9600);

  light.fset = new fuzzyDef[3];

  //Define linguistic variavles (fuzzy sets)
  // 0 is High, 1 is Med and 2 is Low
  //HIGH fuzzy set 0
  light.fset[0].membership = &decreasing;
  light.fset[0].mina = 212;
  light.fset[0].maxa = 512;

  //MEDIUM fuzzy set 1
  light.fset[1].membership = &triangle;
  light.fset[1].mina = 212;
  light.fset[1].maxa = 912;

  //LOW fuzzy set 2
  light.fset[2].membership = &increasing;
  light.fset[2].mina = 512;
  light.fset[2].maxa = 912;


  lcd.begin(16, 2);
  pinMode(A1, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A1);
  truthDegree(&light.fset[0], val);
  truthDegree(&light.fset[1], val);
  truthDegree(&light.fset[2], val);   
  lcd.setCursor(0, 0);
  lcd.print("Alta");
  lcd.setCursor(0, 1);
  lcd.print(light.fset[0].miu);
  lcd.setCursor(6, 0);
  lcd.print("Med");
  lcd.setCursor(6, 1);
  lcd.print(light.fset[1].miu);
  lcd.display();
  lcd.setCursor(11, 0);
  lcd.print("Baja");
  lcd.setCursor(11, 1);
  lcd.print(light.fset[2].miu);
  lcd.display();
  //delay(300);
}

/*****fuzzy membership functions*****/
/* they receibe the fuzzyDef as argument to get parameters */

float triangle(float t) {
  //creates a triangle from -1 to 1
  return max(1 - abs(t), 0);
}

float triangle(fuzzyDef fset, float x) {
  //triangle function between a min and max
  float mid = (fset.maxa - fset.mina) / 2;
  if (x < fset.mina) return 0;
  if (x > fset.maxa) return 0;
  return triangle((x - mid) / (fset.maxa - fset.mina) * 2 - 1);
}


float increasing(fuzzyDef fset, float x) {
  if (x < fset.mina)return 0;
  if (x > fset.maxa)return 1;
  return (x - fset.mina) / (fset.maxa - fset.mina);
}

float decreasing(fuzzyDef fset, float x) {
  if (x < fset.mina)return 1;
  if (x > fset.maxa)return 0;
  return (fset.maxa - x) / (fset.maxa - fset.mina);
}



/************ Fuzzy Operations ****************/
/**********************************************/

//function that return the truth of the membership given de parameter v
//is stores de value in miu for use in other functions
float truthDegree(fuzzyDef *fset, float v) {
  return fset->miu = fset->membership(*fset, v);;
  
}

