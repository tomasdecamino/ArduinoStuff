/***************************************************
  Fuzzy Example

  by Tomás de Camino Beck
  www.funcostarica.org

  License:

  This example was created by Tomàs de Camino Beck (tomas@funcostarica.org)
  and is released under an open source MIT license.  See details at:
    http://opensource.org/licenses/MIT



/***************************************************/

/********************************************************/

#include <FuzzyControl.h>

fuzzyDomain light, outC;



void setup() {

  Serial.begin(9600);

  light.nset = 3;
  light.fset = new fuzzyDef[3];

  //creates a standard domain with nset=3 fuzzy sets
  setDomain(&light, 1023);

  //It is possible to define each fuzzy set like this:
  //  light.fset[0].membership = &decreasing;
  //  light.fset[0].mina = 212;
  //  light.fset[0].maxa = 512;

  // creates output control fuzzy domain
  outC.nset = 3;
  outC.fset = new fuzzyDef[3];
  setDomain(&outC, -10,10);

  pinMode(A1, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A1);
  //  long m=micros();
  truthDegree(&light, val);
  setMiu(&outC.fset[0], light.fset[0].miu);
  outC.fset[1].miu = light.fset[1].miu;
  weightedAverage(&outC);
  Serial.println(outC.fset[0].miu);
     // Serial.println(micros()-m);
 
  delay(300);
}
