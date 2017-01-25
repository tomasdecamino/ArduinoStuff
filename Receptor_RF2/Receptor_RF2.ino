#include <VirtualWire.h> 
//word countNS =0;

void setup()
{
    Serial.begin(9600);    

// Initialise the IO and ISR
    vw_set_ptt_inverted(true);  
    vw_setup(2000);               
    vw_set_rx_pin(5);      
    vw_rx_start();        
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(4,LOW);
    digitalWrite(7,HIGH);
}

void loop()
{
   // uint8_t buf[VW_MAX_MESSAGE_LEN];
   // uint8_t buflen = VW_MAX_MESSAGE_LEN;
    Serial.println("NADA");
   
    if(vw_wait_rx_max(5000)){
       digitalWrite(2,LOW);
         Serial.println("algo");  
     }else{
       digitalWrite(2,HIGH); 
     }
     
}
