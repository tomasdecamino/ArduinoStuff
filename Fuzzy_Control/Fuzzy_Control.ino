//#include "CurieIMU.h";

float a = -1;




//We will use a structured data type to create label type def
//in C++ struct is a public object.
struct fuzzyDef {
  String label;
  float mina = 0;
  float minb = 0;
  float maxa = 0;
  float maxb = 0;
  float (*membership)(fuzzyDef, float);//pointer to membership function
};


fuzzyDef tempHot ;

void setup() {
  // put your setup code here, to run once:
  //CurieIMU.begin();
  Serial.begin(9600);

  //define parameters for the fuzzy set, indicating membership function
  tempHot.membership = &increasing;
  tempHot.mina = 0.5;
  tempHot.maxa = 1.5;
  tempHot.label = "HOT";

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(a);
  //  Serial.print(",");
  //  Serial.print(triangle(0.5, 1.5, a));
  //  Serial.print(",");
  //  Serial.print(increasing(0.5, 1.5, a));
  Serial.print(",");
  Serial.println(truthDegree(tempHot, a));
  a += 0.1;
  if (a > 4.0)a = -1;
  delay(5);
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

float trapezoid(fuzzyDef fset, float x) {
  if (x < fset.mina || x > fset.maxb)return 0;
  if (x > fset.maxa && x < fset.minb)return 1;
  if (x >= fset.mina && x <= fset.maxa)return increasing(fset, x);
  if (x >= fset.minb && x <= fset.maxb)return decreasing(fset, x);
}

//function that return the truth of the membership given de parameter v
float truthDegree(fuzzyDef fset, float v) {
  return fset.membership(fset, v);
}


