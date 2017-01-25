/************************************************************
  [Annikken Andee]
  ================
  Lesson 17
  Using Sliders to Control RGB LEDs
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
AndeeHelper redSlider;
AndeeHelper greenSlider;
AndeeHelper blueSlider;

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
  displayCurrentColour.setTitleColor(TRANSPARENT); // Set title to white
  displayCurrentColour.setTitleTextColor(WHITE); // Set title font to black
  displayCurrentColour.setColor(TRANSPARENT);
  displayCurrentColour.setTextColor(WHITE);
  displayCurrentColour.setData(colour); // Show the RGB colour code.
  displayCurrentColour.setUnit("Values are in hexadecimal format");

  // Draw red slider
  redSlider.setId(1);  
  redSlider.setType(SLIDER_IN); // Set object as a slider
  redSlider.setLocation(1, 0, FULL); // Sliders can only be full size
  redSlider.setTitle("Red Channel");
  redSlider.setSliderMinMax(0, 255);
  redSlider.setSliderInitialValue(r);  
  redSlider.setSliderNumIntervals(256); // Set as discrete slider
  redSlider.setSliderReportMode(ON_VALUE_CHANGE); // Update values as you're moving
  redSlider.setSliderColor(THEME_RED); // Slider bar colour
  redSlider.setColor(THEME_RED_DARK); // Slider background colour  
  
  // Draw green slider
  greenSlider.setId(2);  
  greenSlider.setType(SLIDER_IN); // Set object as a slider
  greenSlider.setLocation(2, 0, FULL); // Sliders can only be full size
  greenSlider.setTitle("Green Channel");
  greenSlider.setSliderMinMax(0, 255);
  greenSlider.setSliderInitialValue(g);  
  greenSlider.setSliderNumIntervals(256); // Set as discrete slider
  greenSlider.setSliderReportMode(ON_VALUE_CHANGE); // Update values as you're moving
  greenSlider.setSliderColor(THEME_GREEN); // Slider bar colour
  greenSlider.setColor(THEME_GREEN_DARK); // Slider background colour  

  // Draw blue slider
  blueSlider.setId(3);  
  blueSlider.setType(SLIDER_IN); // Set object as a slider
  blueSlider.setLocation(3, 0, FULL); // Sliders can only be full size
  blueSlider.setTitle("Blue Channel");
  blueSlider.setSliderMinMax(0, 255);
  blueSlider.setSliderInitialValue(b);  
  blueSlider.setSliderNumIntervals(256); // Set as discrete slider
  blueSlider.setSliderReportMode(ON_VALUE_CHANGE); // Update values as you're moving
  blueSlider.setSliderColor(THEME_BLUE); // Slider bar colour
  blueSlider.setColor(THEME_BLUE_DARK); // Slider background colour    
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{  
  // Get the slider values of each channel colour
  r = redSlider.getSliderValue(INT); // Use INT to retrieve integer values
  g = greenSlider.getSliderValue(INT);
  b = blueSlider.getSliderValue(INT);
  
  // Output each channel value
  analogWrite(pinR, r); 
  analogWrite(pinG, g); 
  analogWrite(pinB, b);   
  
  sprintf(colour, "%02X%02X%02X", r,g,b); // Convert to an ARGB colour code string
  displayCurrentColour.setData(colour); // Show user the ARGB colour code on the smartphone
  
  displayCurrentColour.update(); // Update screen
  redSlider.update();
  greenSlider.update();
  blueSlider.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



