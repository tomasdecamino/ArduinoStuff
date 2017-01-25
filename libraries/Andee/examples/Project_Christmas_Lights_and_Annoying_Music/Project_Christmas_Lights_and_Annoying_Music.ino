/************************************************************
  [Annikken Andee]
  ================
  Christmas Lights and Annoying Music
  by Jonathan Sim <jonathan@annikken.com>

  Here is a simple project to put you in a Christmas mood!
  It will play some Christmas songs and flash LEDs.
  Feel free to play around and add more complicated patterns
  and melodies!
 
  For video instructions on how to assemble this, 
  please visit http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

#include <Andee.h>
#include <SPI.h>

AndeeHelper displaybox; 
AndeeHelper btnFaster; // Increase speed of music and blinking
AndeeHelper btnSlower; // Decrease speed
AndeeHelper btnSongA; // Select song A
AndeeHelper btnSongB; // Select song B
AndeeHelper btnSongC; // Select song C

// We'll need to store our Christmas melodies and the beats of their respective songs
// in the program memory. Arduino doesn't have much RAM available. So if you store
// all these songs in the RAM, it will cause the Annikken Andee to stop functioning.
// As you can see, we're storing the songs and beats as a string. We'll have some code
// later to convert each character in the string into a note
prog_char header0[] PROGMEM = "eeeeeeegcdefffffeeeeeddedg eeeeeeegcdefffffeeeeggfdc";
prog_char header1[] PROGMEM = "4424424444144444448844442444424424444144444448844441";
prog_char header2[] PROGMEM = "gagegageDDbCCgaaCbagageaaCbagageDDFDbCECgegfdc";
prog_char header3[] PROGMEM = "6843684324324324684684324684684324444334446843";
prog_char header4[] PROGMEM = "CbagfedcgaabbCCCbaggfeC CbaggfeeeeeefgfeddddefedcCagfefedc";
prog_char header5[] PROGMEM = "2683422343434134444468444444684444488388444883884246844221";

// This is a program memory directory that will allow Arduino (and us) to easily locate
// where our songs are stored in the program memory.
PROGMEM const char *string_table[] = 
{
  header0, // Jingle Bells melody
  header1, // Jingle Bells beats
  header2, // Silent night melody
  header3, // Silent night beats
  header4, // Joy to the World melody
  header5  // Joy to the World beats
};

int lengthA = 52;
int lengthB = 46;
int lengthC = 57;

int tempo = 0; // Beats per minute
long quarterLength = 0; 

int nowPlaying_length = -1;
char bufferMelody[60]; // To store the currently playing song
char bufferDuration[60]; // To store the beats of the currently playing song

const int speakerPin = 2; // Buzzer at Pin 2
const int ledTrack1 = 3; // One set of LEDs at Pin 3
const int ledTrack2 = 4; // Another set of LEDs at Pin 4
const int ledTrack3 = 5;
const int ledTrack4 = 6;
int i = 0;

void setup()
{
  Andee.begin();
  Andee.clear();
  setInitialData();
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
  pinMode(ledTrack1, OUTPUT);
  pinMode(ledTrack2, OUTPUT);
  pinMode(ledTrack3, OUTPUT);
  pinMode(ledTrack4, OUTPUT);  
}

void setInitialData()
{
  displaybox.setId(0);
  displaybox.setType(DATA_OUT);
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Christmas Lights and Annoying Music");
  displaybox.setColor(RED);
  displaybox.setTitleColor(RED);
  
  btnFaster.setId(1);
  btnFaster.setType(BUTTON_IN);
  btnFaster.setLocation(1,0,HALF);
  btnFaster.setTitle("Increase Speed");
  btnFaster.setColor("FF44BB44");
  
  btnSlower.setId(2);
  btnSlower.setType(BUTTON_IN);
  btnSlower.setLocation(1,0,HALF);
  btnSlower.setTitle("Decrease Speed");
  btnSlower.setColor("FF44BB44");
  
  btnSongA.setId(3);
  btnSongA.setType(BUTTON_IN);
  btnSongA.setLocation(2,0,ONE_THIRD);
  btnSongA.setTitle("Play Song A");  
  btnSongA.setColor(RED);
  
  btnSongB.setId(4);
  btnSongB.setType(BUTTON_IN);
  btnSongB.setLocation(2,1,ONE_THIRD);
  btnSongB.setTitle("Play Song B"); 
  btnSongB.setColor(RED); 

  btnSongC.setId(5);
  btnSongC.setType(BUTTON_IN);
  btnSongC.setLocation(2,2,ONE_THIRD);
  btnSongC.setTitle("Play Song C"); 
  btnSongC.setColor(RED);  
}

void loop() 
{
  
  if(btnFaster.isPressed())
  {
    btnFaster.ack();
    tempo = tempo + 5;
    if(tempo > 500) tempo = 500;
    quarterLength = 60000 / tempo;
  }
  
  if(btnSlower.isPressed())
  {
    btnSlower.ack();
    tempo = tempo - 5;
    if(tempo < 10) tempo = 5;
    quarterLength = 60000 / tempo;
  }
  
  if(btnSongA.isPressed())
  {
    btnSongA.ack();
    displaybox.setData("Playing: Jingle Bells");
    
    nowPlaying_length = lengthA;
    strcpy_P(bufferMelody, (char*)pgm_read_word(&(string_table[0])));
    strcpy_P(bufferDuration, (char*)pgm_read_word(&(string_table[1])));
    i = 0;
    tempo = 300;
    quarterLength = 60000 / tempo;
  }
  
  if(btnSongB.isPressed())
  {
    btnSongB.ack();
    displaybox.setData("Playing: Silent Night");
    
    nowPlaying_length = lengthB;
    strcpy_P(bufferMelody, (char*)pgm_read_word(&(string_table[2])));
    strcpy_P(bufferDuration, (char*)pgm_read_word(&(string_table[3])));
    i = 0;
    tempo = 250;
    quarterLength = 60000 / tempo;
  }  
  
  if(btnSongC.isPressed())
  {
    btnSongC.ack();
    displaybox.setData("Playing: Joy to the World");
    
    nowPlaying_length = lengthC;
    strcpy_P(bufferMelody, (char*)pgm_read_word(&(string_table[4])));
    strcpy_P(bufferDuration, (char*)pgm_read_word(&(string_table[5])));
    i = 0;
    tempo = 600;
    quarterLength = 60000 / tempo;
  } 

  // Start playing only when a song is pressed
  if(nowPlaying_length != -1)
  {  
    if(i%8 == 0) // Blink LEDs alternately
    {
      digitalWrite(ledTrack1, HIGH);
      digitalWrite(ledTrack2, LOW);
      digitalWrite(ledTrack3, HIGH);
      digitalWrite(ledTrack4, LOW);      
    }
    else if(i%8 == 1)
    {
      digitalWrite(ledTrack1, LOW);
      digitalWrite(ledTrack2, HIGH);
      digitalWrite(ledTrack3, LOW);
      digitalWrite(ledTrack4, HIGH); 
    }
    else if(i%8 == 2)
    {
      digitalWrite(ledTrack1, HIGH);
      digitalWrite(ledTrack2, HIGH);
      digitalWrite(ledTrack3, LOW);
      digitalWrite(ledTrack4, LOW); 
    }
    else if(i%8 == 3)
    {
      digitalWrite(ledTrack1, LOW);
      digitalWrite(ledTrack2, LOW);
      digitalWrite(ledTrack3, HIGH);
      digitalWrite(ledTrack4, HIGH); 
    }
    else if(i%8 == 4)
    {
      digitalWrite(ledTrack1, HIGH);
      digitalWrite(ledTrack2, LOW);
      digitalWrite(ledTrack3, LOW);
      digitalWrite(ledTrack4, HIGH); 
    }
    else if(i%8 == 5)
    {
      digitalWrite(ledTrack1, LOW);
      digitalWrite(ledTrack2, HIGH);
      digitalWrite(ledTrack3, HIGH);
      digitalWrite(ledTrack4, LOW); 
    }
    else if(i%8 == 6)
    {
      digitalWrite(ledTrack1, HIGH);
      digitalWrite(ledTrack2, LOW);
      digitalWrite(ledTrack3, LOW);
      digitalWrite(ledTrack4, HIGH); 
    }
    else
    {
      digitalWrite(ledTrack1, LOW);
      digitalWrite(ledTrack2, LOW);
      digitalWrite(ledTrack3, LOW);
      digitalWrite(ledTrack4, LOW ); 
    }   
    
    
    playNote(bufferMelody[i], bufferDuration[i] ); // Play the current note

    i++;
    if(i == nowPlaying_length) i = 0; // Reset i to 0 to repeat indefinitely
  }
  
  displaybox.update();
  btnFaster.update();
  btnSlower.update();
  btnSongA.update();
  btnSongB.update();
  btnSongC.update();
}

// This function will check the frequency that corresponds to the letter
void playNote(char note, char beat) 
{
  int Beat = beat - '0'; // Convert the beat character into an int value
  int duration;  
  int pitch;
  
  switch(note) // Convert the character of the note into a frequency
  {
    case 'c': pitch = 131; break;
    case 'd': pitch = 147; break;
    case 'e': pitch = 165; break;
    case 'f': pitch = 175; break;
    case 'g': pitch = 196; break;
    case 'a': pitch = 220; break;
    case 'b': pitch = 247; break;
    case 'C': pitch = 262; break;
    case 'D': pitch = 294; break;
    case 'E': pitch = 330; break;
    case 'F': pitch = 349; break;
    case 'G': pitch = 392; break;
    case 'A': pitch = 440; break;    
    case ' ': pitch = 0; break; 
  }
  
  if(pitch != 0) // Don't play if the pitch is a zero, i.e. rest
    tone(speakerPin, pitch); // Play the pitch
    
  switch(Beat)
  {
    case 1: duration = quarterLength * 4; break;
    case 2: duration = quarterLength * 2; break;
    case 3: duration = quarterLength * 3; break;
    case 4: duration = quarterLength; break;
    case 6: duration = quarterLength * 1.5; break;
    case 8: duration = quarterLength * 0.5; break;
  }
  delay(duration); // Let the pitch sound for the length of its note
  
  noTone(speakerPin); // Slight pause between each note
  delay(quarterLength/20000);
}
