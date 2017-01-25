/************************************************************
  [Annikken Andee]
  ================
  Lesson 3
  Displaying TMP36 Temperature Sensor Reading
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

/* TMP36 Wiring:

Vcc Pin - Connect it to both +3.3V source and AREF Pin of your Arduino
Vout Pin - Connect it to your analog input pin
GND Pin - Connect it to GND */

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll create two display boxes to display temperature in different units
AndeeHelper tempDisplayC; // Temp in deg C
AndeeHelper tempDisplayF; // Temp in deg F

// We'll use Analog Input Pin A0 to read our analog input.
// Change the pin number if you are using another pin.
const int tempInputPin = A0;

// To store the temperature reading
float degC;
float degF;

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  
  analogReference(EXTERNAL); // Tell Arduino that we're using an external analog reference
  // This will help give you a better temperature reading.
  
  setInitialData(); // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Only one display box this time
  tempDisplayC.setId(0);  // Each object must have a unique ID number
  tempDisplayC.setType(DATA_OUT);  // This defines your object as a display box
  tempDisplayC.setLocation(0, 0, FULL); // Sets the location and size of your object
  tempDisplayC.setTitle("Temperature");
  tempDisplayC.setData(""); // We'll update it with new analog data later.
  tempDisplayC.setUnit("deg C");
  
  tempDisplayF.setId(1);  // Each object must have a unique ID number
  tempDisplayF.setType(DATA_OUT);  // This defines your object as a display box
  tempDisplayF.setLocation(1, 0, FULL); // Sets the location and size of your object
  tempDisplayF.setTitle("Temperature");
  tempDisplayF.setData(""); // We'll update it with new analog data later.
  tempDisplayF.setUnit("deg F");  
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // Read value from analog pin and store it in an int variable
  int reading = analogRead(tempInputPin); 
  
  degC = ( (reading * 3.3 / 1024.0) - 0.5 ) * 100; // Multiplying by 3.3V 
  degF = ( degC * 9.0 / 5.0 ) + 32.0;
  
  
  // Update displays with new reading
  tempDisplayC.setData(degC); 
  tempDisplayF.setData(degF); 
  tempDisplayC.update(); 
  tempDisplayF.update(); 
  
  // A short delay is necessary to give Andee time to communicate with the smartphone
  delay(500); 
}


