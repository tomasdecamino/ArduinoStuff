#include <math.h>
#include <i2cmaster.h>

int x,y,z,xAnt,yAnt,zAnt;
float mov;

double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
double tempData = 0x0000; // zero out the data
float threshTMP = 26; //**** CAMBIAR ACA LA TEMP****

void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
}

void loop(){
 xAnt = x;
 yAnt = y;
 zAnt = z;
 x = analogRead(A0); 
 y = analogRead(A0); 
 z = analogRead(A0);
 
 readSensor();   
 float celcius = tempData - 273.15;
 
 mov = sqrt(square(x-xAnt)+square(y-yAnt)+square(z-zAnt));
 if(mov>50){
   digitalWrite(8,HIGH);
   delay(500);
 } else {
   digitalWrite(8,LOW);
 } 
 //Serial.println(mov);
 Serial.println(celcius); 
 delay(100);
}

void readSensor(){
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07);
    
    // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();
    
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    int frac; // data past the decimal point
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
    
  
}
