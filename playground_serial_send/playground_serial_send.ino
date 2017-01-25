/*Tomas de Camino Beck
www.funcostarica.org
Serial send comma separated all sensors and buttons
data is sent in the following order

cap3,cap2,cap0,cap1,cap12,cap6,cap9,cap10,slide,button_left,button_right,light,sound,X,Y,Z,temp

*/
#include <Adafruit_CircuitPlayground.h>


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}


void loop() {

  /************* CAPTOUCH */
  //Capsense #3
  Serial.print(CircuitPlayground.readCap(3));
  Serial.print(',');
  //Capsense #2
  Serial.print(CircuitPlayground.readCap(2));
  Serial.print(',');
  //Capsense #0
  Serial.print(CircuitPlayground.readCap(0));
  Serial.print(',');
  //Capsense #1
  Serial.print(CircuitPlayground.readCap(1));
  Serial.print(',');
  //Capsense #12
  Serial.print(CircuitPlayground.readCap(12));
  Serial.print(',');
  //Capsense #6
  Serial.print(CircuitPlayground.readCap(6));
  Serial.print(',');
  //Capsense #9
  Serial.print(CircuitPlayground.readCap(9));
  Serial.print(',');
  //"Capsense #10
  Serial.print(CircuitPlayground.readCap(10));
  Serial.print(',');

  /************* SLIDE SWITCH */
  Serial.print(CircuitPlayground.slideSwitch());
  Serial.print(',');

  /************* BUTTONS */
  Serial.print(CircuitPlayground.leftButton());
  Serial.print(',');
  Serial.print(CircuitPlayground.rightButton());
  Serial.print(',');

  /************* LIGHT SENSOR */
  Serial.print(CircuitPlayground.lightSensor());
  Serial.print(',');

  /************* SOUND SENSOR */
  Serial.print(CircuitPlayground.soundSensor());
  Serial.print(',');

  /************* ACCEL */
  // Display the results (acceleration is measured in m/s*s)
  Serial.print(CircuitPlayground.motionX());
  Serial.print(',');
  Serial.print(CircuitPlayground.motionY());
  Serial.print(',');
  Serial.print(CircuitPlayground.motionZ());
  Serial.print(',');

  /*************THERMISTOR */
  Serial.println(CircuitPlayground.temperature());
}
