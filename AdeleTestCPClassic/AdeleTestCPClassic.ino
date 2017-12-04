#include <Adafruit_Circuit_Playground.h>
#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>

int garraPin = 9;
int motorLpin = 2;
int motorRpin = 12;
int lineLpin = 3;
int lineRpin = 6;

Servo garra;
Servo motorL;
Servo motorR;

bool slideSwitch;

void setup() {
  Serial1.begin(9600); //Set up Bluetooth
  CircuitPlayground.begin();

  pinMode(INPUT, lineLpin);
  pinMode(INPUT, lineRpin);

  garra.attach(garraPin);
  motorL.attach(motorLpin);
  motorR.attach(motorRpin);

  Serial1.println("Starting...");

}

void loop() {
  slideSwitch = CircuitPlayground.slideSwitch();

  if (slideSwitch) {

    motorL.write(90 + 45);
    motorR.write(90 - 45);

  } else {

    motorL.write(90);
    motorR.write(90);

  }

  if (digitalRead(4)) {

    garra.write(150);

  } else {

    garra.write(60);

  }

  if (digitalRead(lineLpin)) {
    Serial1.println("Left");
  }

  if (digitalRead(lineRpin)) {
    Serial1.println("Right");
  }
}
