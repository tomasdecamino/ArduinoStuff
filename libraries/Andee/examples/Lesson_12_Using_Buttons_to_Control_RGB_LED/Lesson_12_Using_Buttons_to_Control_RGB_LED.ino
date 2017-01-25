/************************************************************
  [Annikken Andee]
  ================
  Lesson 12
  Using Buttons to Control RGB LEDs
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll need 6 buttons to increase/decrease the red, green
// and blue channels of our RGB LED
AndeeHelper displayCurrentColour;
AndeeHelper buttonRup; // Buttons to adjust Red
AndeeHelper buttonRdown;
AndeeHelper buttonGup; // Buttons to adjust Green
AndeeHelper buttonGdown;
AndeeHelper buttonBup; // Buttons to adjust Blue
AndeeHelper buttonBdown;

// To get various colours from the RGB LED, we'll need to connect 
// the LED to pins capable of analog output. On the Arduino Uno,
// pins capable of analog output are Pins 3, 5, 6, 9, 10.
// Do not use Pins 8, 11, 12, 13 (Arduino Uno layout) as Andee 
// is using them. Strange things will happen if you do.
const int pinR = 6; // Red is connected to pin 6
const int pinG = 5; // Green is connected to pin 5
const int pinB = 3; // Blue is connected to pin 3

// We'll need to store the intensity levels of each channel
// Note: Analog output is only capable of producing a range from 0 to 255
int r = 0; // Red channel
int g = 0; // Green channel
int b = 0; // Blue channel

int resolution = 30; // Set the amount to increase/decrease for each button press
char colour[7] = "000000"; // The initial colour of our display

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  pinMode(pinR, OUTPUT); // Set pins to output mode
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  displayCurrentColour.setId(0); // Our display box
  displayCurrentColour.setType(DATA_OUT);
  displayCurrentColour.setLocation(0,0,FULL);
  displayCurrentColour.setTitle("Current Colour");
  displayCurrentColour.setTitleColor(WHITE); // Set title to white
  displayCurrentColour.setTitleTextColor(TEXT_DARK); // Set title font to black
  displayCurrentColour.setColor(WHITE);
  displayCurrentColour.setTextColor(TEXT_DARK);
  displayCurrentColour.setData(colour); // Show the RGB colour code.

  buttonRup.setId(1); // Button to increase red level
  buttonRup.setType(BUTTON_IN);
  buttonRup.setLocation(1,0,ONE_THIRD);
  buttonRup.setTitle("R +");
  buttonRup.setColor(RED); // Set button to red
  buttonRup.requireAck(false); // You need this line to allow for multiple button presses

  buttonRdown.setId(2); // Button to decrease red level
  buttonRdown.setType(BUTTON_IN);
  buttonRdown.setLocation(2,0,ONE_THIRD);
  buttonRdown.setTitle("R -");
  buttonRdown.setColor(RED); // Set button to red
  buttonRdown.requireAck(false); // You need this line to allow for multiple button presses

  buttonGup.setId(3); // Button to increase green level
  buttonGup.setType(BUTTON_IN);
  buttonGup.setLocation(1,1,ONE_THIRD);
  buttonGup.setTitle("G +");
  buttonGup.setColor(GREEN); // Set button to green
  buttonGup.requireAck(false); // You need this line to allow for multiple button presses

  buttonGdown.setId(4); // Button to decrease green level
  buttonGdown.setType(BUTTON_IN);
  buttonGdown.setLocation(2,1,ONE_THIRD);
  buttonGdown.setTitle("G -");
  buttonGdown.setColor(GREEN); // Set button to green
  buttonGdown.requireAck(false); // You need this line to allow for multiple button presses

  buttonBup.setId(5); // Button to increase blue level
  buttonBup.setType(BUTTON_IN);
  buttonBup.setLocation(1,2,ONE_THIRD);
  buttonBup.setTitle("B +");
  buttonBup.setColor(BLUE); // Set button to blue
  buttonBup.requireAck(false); // You need this line to allow for multiple button presses

  buttonBdown.setId(6); // Button to decrease blue level
  buttonBdown.setType(BUTTON_IN);
  buttonBdown.setLocation(2,2,ONE_THIRD);
  buttonBdown.setTitle("B -");
  buttonBdown.setColor(BLUE);  // Set button to blue 
  buttonBdown.requireAck(false); // You need this line to allow for multiple button presses
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{  
  // This is the most important chunk of code. Each analogWrite() statement sets the intensity
  // of each colour channel.
  analogWrite(pinR, r); 
  analogWrite(pinG, g); 
  analogWrite(pinB, b); 

  // Buttons used to adjust the colour channel intensity. We will employ
  // the press-and-hold button method to control the RGB LEDs
  if( buttonRup.getButtonPressCount() > 0 ) // Red button up will increase red intensity
  {
    r = r+resolution; // Increase the intensity by a fixed amount (specified above)
    if(r>255) r = 255; // 255 is the max value. If it goes beyond that, set the value to 255.  
  }  
  if( buttonRdown.getButtonPressCount() > 0 ) // Red button down will decrease red intensity
  {
    r = r-resolution; // Decrease the intensity by a fixed amount (specified above)
    if(r<1) r = 0; // 0 is the min value. If it goes under that, set the value to 0.     
  }
  if( buttonGup.getButtonPressCount() > 0 ) // Green button up will increase green intensity
  {
    g = g+resolution;
    if(g>255) g = 255;   
  }  
  if( buttonGdown.getButtonPressCount() > 0 ) // Green button down will decrease green intensity
  {
    g = g-resolution;
    if(g<1) g = 0;      
  }
  if( buttonBup.getButtonPressCount() > 0 ) // Blue button up will increase blue intensity
  {
    b = b+resolution;
    if(b>255) b = 255;
  }
  if( buttonBdown.getButtonPressCount() > 0 ) // Blue button down will decrease blue intensity
  {
    b = b-resolution;
    if(b<1) b = 0;
  }  
  
  sprintf(colour, "%02X%02X%02X", r,g,b); // Convert to an ARGB colour code string
  displayCurrentColour.setData(colour); // Show user the ARGB colour code on the smartphone
  
  displayCurrentColour.update(); // Update screen
  buttonRup.update();
  buttonRdown.update();
  buttonGup.update();
  buttonGdown.update();
  buttonBup.update();
  buttonBdown.update();  
  
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



