// created by Tomas de Camino Beck
//for hand movement sensor FLora

import processing.serial.*;
Serial port;

// magnitude [0] and angle in radians [1]
float[] coord = new float[3];
String data="0,0,0";
float x, y, antX, antY;


void setup()
{
  size(displayWidth, displayHeight);
  println(Serial.list());
  port = new Serial(this, Serial.list()[5], 9600);
  port.clear();
  port.bufferUntil('\n');
  ellipseMode(CENTER);
  background(255);
  x = width/2;
  y=height/2;
  antX=width/2;
  antY=height/2;
  smooth(8);
}

void draw()
{
  strokeWeight(10);
  float x = width-map(coord[0], -1000, 1000, 0, width);
  float y = height-map(coord[1], -1000, 1000, 0, height);
  if (coord[2]<0) {
    background(255); 
    x = width/2;
    y=height/2;
    antX=width/2;
    antY=height/2;
  }
  else {
    fill(0, 150);
    line(antX, antY, x, y);
    antX= x;
    antY= y;
  }
}


void serialEvent(Serial port) {
  //data = port.readStringUntil('\n');
  data = port.readString();
  coord = float(split(data, ','));
}

