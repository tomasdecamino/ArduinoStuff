#include <Andee.h>
#include <SPI.h>

AndeeHelper displayBoxA;
AndeeHelper displayBoxB;
AndeeHelper displayBoxC;

void setup(){
  Andee.begin();
  Andee.clear();
  
  //In iOS, you can have 3 different types of data displays
  //DATA_OUT, DATA_OUT_CIRCLE, DATA_OUT_TEXT
  
  displayBoxA.setId(0);
  displayBoxA.setType(DATA_OUT);
  displayBoxA.setLocation(0,0, FULL);
  displayBoxA.setTitle("Title");
  displayBoxA.setData("Data");
  displayBoxA.setUnit("Unit");
  
  //Changing colors of Title Background
  //displayBoxA.setTitleColor(MAROON);
  //Changing colors of data and unit text fields
  //displayBoxA.setTitleTextColor(LIGHT_PINK); //or setTextColor();
  //Changing colors of data and unit background
  //displayBoxA.setColor(YELLOW);
  //Changing colors of Data and unit colors
  //displayBoxA.setDataUnitTextColor(BLACK);
  
  displayBoxB.setId(1);
  displayBoxB.setType(DATA_OUT_CIRCLE);
  displayBoxB.setLocation(1,0, FULL);
  displayBoxB.setTitle("Title");
  displayBoxB.setData("Data");
  displayBoxB.setUnit("Unit");
  //Changing colors of circle
  //displayBoxB.setColor(MAROON);
  //Changing colors of data and unit text fields
  //displayBoxB.setDataUnitTextColor(LIGHT_PINK);
  //Changing colors of title
  //displayBoxB.setTitleTextColor(BLACK);
  
  
  displayBoxC.setId(2);
  displayBoxC.setType(DATA_OUT_TEXT);
  displayBoxC.setLocation(2,0, FULL);
  displayBoxC.setTitle("Title");
  displayBoxC.setData("Data - Just text and no backgrounds whatsoever");
  displayBoxC.setUnit("Unit");
  //Changing colors, one function changes all text colors
  //displayBoxC.setTextColor(MAROON);
  
}

void loop(){
  //Calling updates displays your boxes on screen.
  displayBoxA.update();
  displayBoxB.update();
  displayBoxC.update();
  delay(200);
}
