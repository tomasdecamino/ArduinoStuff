//Tomas de camino Beck

#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>
#include "Adele_Robot.h"

#define SERIALPORT Serial1

String cmd; //stores commands from serial as string



bool slideSwitch;

void setup() {
  //Serial.begin(9600); //Set up Bluetooth
  CircuitPlayground.begin();

  adeleBegin();

  //start lights and sound
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(25 * i));
    CircuitPlayground.playTone(500 + i * 500, 250);
  }
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(128, 0, 128));
  CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(128, 0, 128));
  openGarra();
  SERIALPORT.begin(9600); //Set up Bluetooth
  SERIALPORT.println("Starting...");

}

void loop() {
  if (SERIALPORT.available() > 0) {
    digitalWrite(13, HIGH);
    cmd = SERIALPORT.readStringUntil('\n');//
    SERIALPORT.println(cmd + " recibido...");
    SERIALPORT.flush();
    digitalWrite(13, LOW);
  }
  char inChar;// variable for current command
  for (int i = 0; i < cmd.length(); i++) {
    inChar = cmd[i];//reads command from string
    SERIALPORT.println(inChar);
    switch (inChar) {
      case 'F'://move forward
        forward();
        //  CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(100, 200, 0));
        //  CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(100, 200, 0));
        delay(1000);
        break;
      case 'B'://move backward
        backward();
        delay(1000);
        break;
      case 'L'://move left
        left();
        delay(680);
        break;
      case 'R'://move right
        right();
        delay(680);
        break;
      case 'O'://open claw
        openGarra();
        delay(750);
        break;
      case 'C'://claose claw
        closeGarra();
        delay(750);
        break;
      case 'N'://play tune
        CircuitPlayground.playTone(440, 250);
        CircuitPlayground.playTone(349, 125);
        CircuitPlayground.playTone(523, 250);
        break;
      case 'P':
        for (int i = 0; i < 10; i++) {
          CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(25 * i));
          delay(150);
        }
        CircuitPlayground.clearPixels();
        CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(128, 0, 128));
        CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(128, 0, 128));
        break;
    }
    stopServos();
    delay(300);//waits so it each command are seen as discrete moves
  }
  stopServos();
  SERIALPORT.flush();
  cmd = "";//clears command string to get ready for next
}
