/************************************************************
  [Annikken Andee]
  ================
  Lesson 20
  Use Bluetooth Signal Strength to Control Things
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

/* You can use this to control relays in your home/office! */

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll have a displaybox to show you the Bluetooth signal strength
AndeeHelper displaybox;

// We'll just light up an LED to demonstrate this
// LED connected to Pin 2
const int outputPin = 2;

char strBuffer[30];
char signalStr[4];
int signalStrength;

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  pinMode(outputPin, OUTPUT); // Configures outputPin for output.
  digitalWrite(outputPin, LOW);
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  displaybox.setId(0);
  displaybox.setType(DATA_OUT);
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Signal Strength");
  displaybox.setUnit("dB");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( Andee.isConnected() ) // Run only when connected
  {
    // Retrieve Bluetooth information from the Andee and store it in strBuffer
    Andee.sendCommand("GET CONNECTED MAC_ID", strBuffer);
    memcpy(signalStr, &strBuffer[18], 4); // Extract signal strength
    signalStrength = atoi(signalStr); // Convert to int value

    displaybox.setData(signalStrength);
    displaybox.update();

    // We're gonna use a double threshold line to prevent light flickering.
    // If you use a single threshold, when you stand at the edge of the threshold
    // line, the signal will fluctuate around that value, causing the LED to
    // flicker. This is very undesirable.
    
    if(signalStrength > -60) // The nearer to zero, the closer you are
    {
      digitalWrite(outputPin, HIGH);
    }

    // Andee will not do anything when you are within the -70db to -60db range.

    if(signalStrength < -70) // When you're very far away
    {
      digitalWrite(outputPin, LOW);
    }    
    
  }
  if( !Andee.isConnected() )
  {
    digitalWrite(outputPin, LOW); // Keep the LED off
  }

  delay(500); // Always leave a short delay for Bluetooth communication
}



