/************************************************************
  [Annikken Andee]
  ================
  Lesson 16
  Creating Slider Inputs and Outputs
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// There are two types of slider inputs:
// - Discrete slider with fixed intervals (works best for integer values)
// - Continuous sliders (works best for float values)

// You can also use a slider input as a display!

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll create a display and a button to show you how to
// program a button to do something
AndeeHelper buttonResetPosition;
AndeeHelper sliderDiscrete; // Discrete input slider
AndeeHelper sliderContinuous; // Continuous input slider
AndeeHelper sliderDisplay; // Input slider used as an output display

int sliderPosA;
float sliderPosB;
float sliderTotal;

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays

  sliderPosA = 128; // Just some arbitary values for demo purposes
  sliderPosB = 50.0;
  sliderTotal = sliderPosA + sliderPosB;
  
  setInitialData(); // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{  
  // Let's draw a discrete slider! ///////////////////////////////////////
  sliderDiscrete.setId(0);  
  sliderDiscrete.setType(SLIDER_IN); // Set object as a slider
  sliderDiscrete.setLocation(0, 0, FULL); // Sliders can only be full size
  sliderDiscrete.setTitle("Discrete Slider");
  
  // Slider settings:
  sliderDiscrete.setSliderMinMax(0, 255, 0);
  // - setSliderMinMax(minimumValue, maximumValue, numberOfDecimalPlaces)
  // Set numberOfDecimalPlaces to 0 for integer values only.
 
  sliderDiscrete.setSliderInitialValue(sliderPosA);
  // Set slider to position 128
  
  sliderDiscrete.setSliderNumIntervals(256);
  // Set number of intervals in your slider.
  // Set 0 for continuous slider.
  // Set any number greater than 0 for discrete slider

  sliderDiscrete.setSliderReportMode(ON_VALUE_CHANGE);
  // Set when you want the smartphone to update Arduino
  // Options available:
  // - ON_VALUE_CHANGE : Updates Arduino everytime your finger moves the slider
  // - ON_FINGER_UP    : Updates Arduino only after you lift up your finger from the slider
  
  sliderDiscrete.setSliderColor(THEME_GREY_DARK); // Slider bar colour
  sliderDiscrete.setColor(THEME_GREY); // Slider background colour
  
  // Let's draw a continuous slider! ///////////////////////////////////////
  sliderContinuous.setId(1);
  sliderContinuous.setType(SLIDER_IN);
  sliderContinuous.setLocation(1,0,FULL);
  sliderContinuous.setTitle("Continuous Slider");
  sliderContinuous.setSliderMinMax(0, 100, 2); // Display 2 decimal places
  sliderContinuous.setSliderInitialValue(sliderPosB);  // Set slider position to 50
  sliderContinuous.setSliderNumIntervals(0); // Set to 0 for continuous slider
  sliderContinuous.setSliderReportMode(ON_FINGER_UP);
  sliderContinuous.setSliderColor(THEME_MIDNIGHT_DARK);
  sliderContinuous.setColor(THEME_MIDNIGHT);
  
  // Button to reset slider positions 
  buttonResetPosition.setId(2); // Don't forget to assign a unique ID number
  buttonResetPosition.setType(BUTTON_IN); // Defines object as a button
  buttonResetPosition.setLocation(2,0,FULL);
  buttonResetPosition.setTitle("Reset Position");
  buttonResetPosition.setColor(THEME_TURQUOISE);
  buttonResetPosition.setTitleColor(THEME_TURQUOISE_DARK);  
  
  // You can also use sliders to display output ////////////////////////////
  sliderDisplay.setId(3);
  sliderDisplay.setType(SLIDER_IN);
  sliderDisplay.setLocation(3,0,FULL);
  sliderDisplay.setTitle("Sum of the Two Sliders");
  sliderDisplay.setSliderMinMax(0, 355, 2); // Display 2 decimal places
  sliderDisplay.setSliderInitialValue(sliderTotal);  // Set slider position to 178
  sliderDisplay.setSliderNumIntervals(0); // Set to 0 for continuous slider
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( buttonResetPosition.isPressed() )
  {
    buttonResetPosition.ack();
    sliderDiscrete.moveSliderToValue(128);
    sliderContinuous.moveSliderToValue(50);
  }

  sliderPosA = sliderDiscrete.getSliderValue(INT); // Retrieve integer value
  sliderPosB = sliderContinuous.getSliderValue(FLOAT); // Retrieve float value

  sliderTotal = (float)(sliderPosA) + sliderPosB;
  
  // This is how you update the slider as an output display:
  sliderDisplay.moveSliderToValue(sliderTotal, 2);
  // Add the 2  to tell Arduino to slide to a float value.
  
  if(sliderTotal >= 300) // You can even get it to update its colour
  {
    sliderDisplay.setSliderColor(THEME_GREEN_DARK);
    sliderDisplay.setColor(THEME_GREEN);    
  }
  else if(sliderTotal < 100)
  {
    sliderDisplay.setSliderColor(THEME_RED_DARK);
    sliderDisplay.setColor(THEME_RED);      
  }
  else if(sliderTotal < 300)
  {
    sliderDisplay.setSliderColor(THEME_ORANGE_DARK);
    sliderDisplay.setColor(THEME_ORANGE);
  }   
  
  sliderDisplay.update();
  sliderDiscrete.update();
  sliderContinuous.update();
  buttonResetPosition.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}
