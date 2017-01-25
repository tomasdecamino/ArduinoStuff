int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

int datapin2 = 5; 
int clockpin2 = 6;
int latchpin2 = 7;

int center1 = 362;
int center2 = 362;
int t = 10;

// We'll also declare a global variable for the data we're
// sending to the shift register:

byte data = 0;
byte data2 = 0;

int player1,player2;
int count1,count2,led1,led2;



void setup()
{
  // Set the three SPI pins to be outputs:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);  
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);  
  pinMode(latchpin2, OUTPUT);
  count1=0;
  count2=0;
  led1=-1;
  led2=-1;
}


void loop()
{
  long startMillis =millis();
  count1=0;
  while((millis()-startMillis)<3000){
    player1 = analogRead(A0);
    player2 = analogRead(A1);
    Serial.print(player1);
    Serial.print(",");
        Serial.println(player2);
    delay(100);
    if(player1<(center1+t) && player1>(center1-t)){
      count1++; 
    }
    else{
      count1--; 
    }
    if(player2<(center2+t) && player2>(center2-t)){
      count2++; 
    }
    else{
      count2--; 
    }
  }
  //Serial.println(count1);
  if(count1>0){
    led1++;
  }
  if(count2>0){
    led2++;
  }  

  //  Serial.println(player1); 

  shiftWrite(led1, HIGH);
  shiftWrite2(led2, HIGH);
  delay(200);


}


void shiftWrite(int desiredPin, boolean desiredState)


{


  bitWrite(data,desiredPin,desiredState);


  shiftOut(datapin, clockpin, MSBFIRST, data);


  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void shiftWrite2(int desiredPin, boolean desiredState)


{


  bitWrite(data2,desiredPin,desiredState);


  shiftOut(datapin2, clockpin2, MSBFIRST, data2);


  digitalWrite(latchpin2, HIGH);
  digitalWrite(latchpin2, LOW);
}



