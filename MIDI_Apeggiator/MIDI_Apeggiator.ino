#include <MIDI.h>
#include <Wire.h>

#define NOTE_B0  35
#define NOTE_C1  36
#define NOTE_CS1 37
#define NOTE_D1  38
#define NOTE_DS1 39
#define NOTE_E1  40
#define NOTE_F1  41
#define NOTE_FS1 42
#define NOTE_G1  43
#define NOTE_GS1 44
#define NOTE_A1  45
#define NOTE_AS1 46
#define NOTE_B1  47
#define NOTE_C2  48
#define NOTE_CS2 49
#define NOTE_D2  50
#define NOTE_DS2 51
#define NOTE_E2  52
#define NOTE_F2  53
#define NOTE_FS2 54
#define NOTE_G2  55
#define NOTE_GS2 56
#define NOTE_A2  57
#define NOTE_AS2 58
#define NOTE_B2  59
#define NOTE_C3  60
#define NOTE_CS3 61
#define NOTE_D3  62
#define NOTE_DS3 63
#define NOTE_E3  64
#define NOTE_F3  65
#define NOTE_FS3 66
#define NOTE_G3  67
#define NOTE_GS3 68
#define NOTE_A3  69
#define NOTE_AS3 70
#define NOTE_B3  71
#define NOTE_C4  72
#define NOTE_CS4 73
#define NOTE_D4  74
#define NOTE_DS4 75
#define NOTE_E4  76
#define NOTE_F4  77
#define NOTE_FS4 78
#define NOTE_G4  79
#define NOTE_GS4 80
#define NOTE_A4  81
#define NOTE_AS4 82
#define NOTE_B4  83
#define NOTE_C5  84
#define NOTE_CS5 85
#define NOTE_D5  86
#define NOTE_DS5 87
#define NOTE_E5  88
#define NOTE_F5  89
#define NOTE_FS5 90
#define NOTE_G5  91
#define NOTE_GS5 92
#define NOTE_A5  93
#define NOTE_AS5 94
#define NOTE_B5  95
#define NOTE_C6  96
#define NOTE_CS6 97
#define NOTE_D6  98
#define NOTE_DS6 99
#define NOTE_E6  100
#define NOTE_F6  101
#define NOTE_FS6 102
#define NOTE_G6  103
#define NOTE_GS6 104
#define NOTE_A6  105
#define NOTE_AS6 106
#define NOTE_B6  107
#define NOTE_C7  108
#define NOTE_CS7 109
#define NOTE_D7  110
#define NOTE_DS7 111
#define NOTE_E7  112
#define NOTE_F7  113
#define NOTE_FS7 114
#define NOTE_G7  115
#define NOTE_GS7 116
#define NOTE_A7  117
#define NOTE_AS7 118
#define NOTE_B7  119
#define NOTE_C8  120
#define NOTE_CS8 121
#define NOTE_D8  122
#define NOTE_DS8 123

static const uint16_t sNotePitches[] = {
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1,
  NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2,
  NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2,
  NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3,
  NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4,
  NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4,
  NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5,
  NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6,
  NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6,
  NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7,
  NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8,
};


MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 6   		    // LED pin on Arduino Uno


void playNote(int t, uint16_t note) {
  MIDI.sendNoteOn(note, 127, 1);
  delay(t);
  MIDI.sendNoteOff(note, 0, 1);
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  MIDI.begin();
  //Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED, LOW);
  int tonic = 8;
  int time = map(analogRead(A0), 0, 1023, 50, 1000);
  int p = map(analogRead(A1),0,1023,0,9);
  pattern(p,time, NOTE_C5);

  digitalWrite(LED, HIGH);
}

void pattern(int n, int time, int note) {
  switch (n) {
    case 0: melody1(time,note); break;
    case 1: melody2(time,note); break;
    case 2: melody3(time,note); break;
    case 3: melody4(time,note); break;
    case 4: melody5(time,note); break;
    case 5: melody6(time,note); break;
    case 6: ninethChord(time,note); break;
    case 7: ninethmChord(time); break;
    case 8: ninethMChord(time); break;
    case 9: sus4Chord(time); break;
  }

}


void melody1(int time, int note) {
  playNote(time * 2, note);
  playNote(time / 2, note - 4);
  playNote(time, note - 7);
  playNote(time / 2, note - 12);
  playNote(time, note - 9);

}

void ninethChord(int time, int note) {
  playNote(time, note );
  playNote(time, note + 4);
  playNote(time, note + 7);
  playNote(time, note + 10);
  playNote(time, note + 14);
}

void ninethmChord(int time) {
  playNote(time, NOTE_C2);
  playNote(time, NOTE_DS2);
  playNote(time, NOTE_G2);
  playNote(time, NOTE_AS2);
  playNote(time, NOTE_D3);
}

void ninethMChord(int time) {
  playNote(time, NOTE_C2);
  playNote(time, NOTE_E2);
  playNote(time, NOTE_G2);
  playNote(time, NOTE_B2);
  playNote(time, NOTE_D3);
}

void sus4Chord(int time) {
  playNote(time, NOTE_C2);
  playNote(time, NOTE_D2);
  playNote(time, NOTE_G2);
}

void melody2(int time, int note) {
  playNote(time, note);
  playNote(time, note + random(-12, 12));
  playNote(time, note + random(-12, 12));
  playNote(time, note + random(-12, 12));

}

void melody3(int time, int note) {
  playNote(time, note);
  playNote(time, note - 12);
  playNote(time, note);
  playNote(time, note - 15);
  playNote(time, note);
  playNote(time, note - 17);
  playNote(time, note);
  playNote(time, note - 19);

}

void melody4(int time, int note) {
  playNote(time, note - 12);
  playNote(time, note - 15);
 // MIDI.sendNoteOn(note, 5, 1);
  playNote(time, note - 17);
  playNote(time, note - 19);
 // MIDI.sendNoteOff(note, 5, 1);

}

void melody5(int time, int note) {
  playNote(time, note - 10);
  playNote(time, note - 15);
 // MIDI.sendNoteOn(note , 5, 1);
  playNote(time, note - 17);
  playNote(time, note - 19);
 // MIDI.sendNoteOff(note, 5, 1);

}

void melody6(int time, int note) {
  playNote(time, note );
  playNote(time, note - 1); 
  playNote(time, note );
//  MIDI.sendNoteOn(note , 5, 1);
  playNote(time, note - 5);
//  MIDI.sendNoteOff(note, 5, 1);

}



