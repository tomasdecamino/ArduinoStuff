/************************************************************
  [Annikken Andee]
  ================
  Lesson 33
  Automatically Take Photos with Smartphone Camera
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

#include <Andee.h>
#include <SPI.h>

// We'll just create a display box to give us updates, and a button
// to trigger the camera.
AndeeHelper displaybox;
AndeeHelper button;
AndeeHelper camera; // This object will handle the smartphone camera

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Let's draw the button!
  displaybox.setId(0); // Don't forget to assign a unique ID number
  displaybox.setType(DATA_OUT); // Defines object as a display box
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Andee Controlled Camera");
  displaybox.setData("Camera Ready");

  button.setId(1);
  button.setType(BUTTON_IN);
  button.setLocation(1,0,FULL);
  button.setTitle("Take Photo Now");

  // Smartphone Camera Properties /////////////////////////////
  camera.setId(2);
  camera.setType(CAMERA); // Set object as a camera
  
  // You can choose which camera you want to use:
  // - DEFAULT  : default camera
  // - FRONT    : front-facing camera
  // - REAR     : rear-facing camera
  camera.setCamera(DEFAULT); 
  
  // Set whether you wish to enable auto focus before each shot
  // Options available:
  // - ON
  // - OFF
  camera.setAutoFocus(ON); // Options: true or false
  
  // Set whether you wish to enable flash at each shot
  // Options available:
  // - ON
  // - OFF
  // - AUTO
  camera.setFlash(ON);
  
  // Set photo filename prefix. Subsequent photos will
  // have a number appended at the end.
  camera.setPhotoFilename("imageName");
  
  // If file overwrite is enabled, the same file will be replaced
  // everytime a new photograph is taken. If disabled, a new photo
  // will be generated and stored on the phone.
  // Options available:
  // - ON
  // - OFF
  camera.setFileOverwrite(OFF);
  
  // Choose storage location to store your photos. The Andee app 
  // will create a folder in that location called, "Annikken_Andee"
  // Options available:
  // - DEFAULT : Save in the default photo location on your phone.
  //             If you have set your default photo location as SD Card,
  //             photos taken will be stored on your SD card.
  // - SDCARD  : Save in external SD Card.
  camera.setSaveLocation(DEFAULT); 
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // You can substitute the button press with a sensor condition instead
  if( button.isPressed() )
  {
    button.ack();
    displaybox.setData("Taking Photo");
    camera.takePhoto(); // Call smartphone camera to take photo
    
    // Give the smartphone time to complete action. It will take
    // the camera at least 2 seconds to complete the entire
    // photo-taking process. This process may take even longer
    // on slower phones.
    delay(3000);
    
    // If the phone is still not ready, wait another 2 seconds more
    // before checking again.
    while( !camera.takePhotoResultReady() )
    {
      delay(2000);
    }
    
    // camera.getLastTakePhotoResult() will produce an error code
    // at the end of the process.
    if(camera.getLastTakePhotoResult() == 0)
    {
      displaybox.setData("Photo Successfully Taken!");
      displaybox.update();
    }
    else
    {
      displaybox.setData("Error!");
      displaybox.update();
      while(true); // Freeze and do not allow user to do anything else
    }
  }
  
  displaybox.update();
  button.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
  
  displaybox.setData("Camera Ready"); // Reset displaybox message
}




