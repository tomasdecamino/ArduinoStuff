/******************** (C) COPYRIGHT 2012 RadioSHack ********************
 * File Name          : strip.pde
 * Author             : TRS
 * Version            : V1.0
 * Date               : 27/04/2012
 * Description        : Main program body
 ********************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, RS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

#include <avr/pgmspace.h>

// ******** DEBUG ==== should auto config to adapt different mother board *********
//#define DATA_1 (PORTF |=  0X01)    // DATA 1    // for ATMEGA
//#define DATA_0 (PORTF &=  0XFE)    // DATA 0    // for ATMEGA
//#define STRIP_PINOUT DDRF=0xFF  // for ATMEGA
#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO



PROGMEM const unsigned long pattern_test_white[12][12]={
  {0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff}
};

PROGMEM  unsigned long pattern_test_off[12]=
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};
  
unsigned long pattern_test_color[12]=
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000};


PROGMEM const unsigned long pattern_test_rainbow[12][12]={
  {0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0x6f00ff,0x8f00ff},
  {0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x6f00ff,0x8f00ff},
  {0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x6f00ff,0x8f00ff},
  {0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x6f00ff,0x8f00ff},
  {0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x6f00ff,0x8f00ff},
  {0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6fffff,0x8f00ff},
  {0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x00ff00,0x8faaff},
  {0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x6f00ff,0x8f0fff},
  {0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0x6f00ff,0xff00ff},
  {0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0x6f00ff,0x0000ff},
  {0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x6f00ff,0x8f00ab},
  {0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x0000ff,0x8fabff}
};


// ***********************************************************************************************************
// *
// *                            Power Up Init.
// *
// *
// ***********************************************************************************************************

int r1,r2;


void setup() {                

  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

  reset_strip();
  //noInterrupts();
  Serial.begin(9600);
}



// ***********************************************************************************************************
// *
// *                            Main Loop 
// *
// *
// ***********************************************************************************************************
void loop() 
{
  r1=(int)random(0,6);
  r2=(int)random(6,12);
 // send_1M_pattern(pattern_test_red, 4, 500);
  //delay(500);
//  send_1M_pattern(pattern_test_blue, 4, 500);
  //delay(500);
//  send_1M_pattern(pattern_test_green, 4, 500);
 // delay(500);
  send_1M_pattern(pattern_test_rainbow, 12, 100);
  delay(50);
  send_1M_patternB(pattern_test_off,1);
  //send_1M_patternC(5000);
  //send_1M_patternB(pattern_test_white[(int)random(12)],5000);
  for(int z=0;z<50;z++){
    send_1M_patternB(pattern_test_white[r1],50);
    send_1M_patternB(pattern_test_white[r2],50);
  }
  //delay(1000);
  
 /* while (1)
  {
    send_1M_pattern(pattern_test_rainbow, 10, 70);
  }*/


  /*
	frame++;
   	if(frame<=10) LEDSTRIP_PATTERN_0();
   	if(10<frame<=20) LEDSTRIP_PATTERN_0();
   	if(20<frame<=30) LEDSTRIP_PATTERN_0();
   	if(frame>30) frame=1;
   */
  //delay(1);
}


/*******************************************************************************
 * Function Name  : send_1M_pattern
 * Description    : Transmit pattern to whole 1 meter strip
 *                  
 * Input          : pointer to ROM pattern; pattern length; frame rate
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_1M_pattern(const unsigned long data[][12], int pattern_no, int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;

  for (i=0;i<pattern_no;i++)
  {
    noInterrupts();
    for (j=0;j<12;j++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();

    delay(frame_rate);

  }




}


void send_1M_patternB(const unsigned long data[12], int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;
    noInterrupts();
    for (j=0;j<12;j++)
    {
      temp_data=pgm_read_dword_near(&data[j]);
      send_strip(temp_data);
    }
    interrupts();
    delay(frame_rate);
}

void send_1M_patternC(int frame_rate)
{
 // int r1=randomPosA[(int)floor(random(7))];
 // int r2=randomPosB[(int)floor(random(7))];
  pattern_test_color[r1]=0xffffff;
  pattern_test_color[r2]=0xffffff;
  uint32_t temp_data;
    noInterrupts();
    for (int j=0;j<12;j++)
    {
      Serial.println(pattern_test_color[j]);
      temp_data=pgm_read_dword_near(&pattern_test_color[j]);
      send_strip(temp_data);
    }
    interrupts();
    delay(frame_rate);
    pattern_test_color[r1]=0x000000;
    pattern_test_color[r2]=0x000000;
}





/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  
 
  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      
/*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");  
      __asm__("nop\n\t");        
/*----------------------------*/      
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;
/*----------------------------*/      
       __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
/*----------------------------*/         
    }

    j>>=1;
  }


  
}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}













