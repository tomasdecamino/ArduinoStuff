#include <VirtualWire.h> 
int countNS =0;

void setup()
{
    Serial.begin(9600);    

// Initialise the IO and ISR
    vw_set_ptt_inverted(true);  
    vw_setup(2000);               
    vw_set_rx_pin(4);      
    vw_rx_start();        
    pinMode(10,OUTPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
   // Serial.println("NADA");
    if(countNS>500){
       tone(10,440);  
       Serial.println(countNS); 
     }
    if (vw_get_message(buf, &buflen)) 
    {
      //Serial.print("RANGO, ");
      //Serial.println(countNS);
      countNS = 0;
      noTone(10);
     }else{
      countNS++;
     }

     
}
