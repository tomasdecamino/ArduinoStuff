#include <VirtualWire.h> 
word countNS =0;

void setup()
{
    //Serial.begin(9600);    

// Initialise the IO and ISR
    vw_set_ptt_inverted(true);  
    vw_setup(2000);               
    vw_set_rx_pin(0);      
    vw_rx_start();        
    pinMode(0,OUTPUT);
}

void loop()
{
   // uint8_t buf[VW_MAX_MESSAGE_LEN];
   // uint8_t buflen = VW_MAX_MESSAGE_LEN;
    //Serial.println(analogRead(1));
    //digitalWrite(13,LOW); 
    if(analogRead(1)>1022){
     // Serial.println("no recibido");
      digitalWrite(0,HIGH);
      //delay(0);
    } else{
      digitalWrite(0,LOW);
      delay(20); 
    }

   delay(2);  
}
