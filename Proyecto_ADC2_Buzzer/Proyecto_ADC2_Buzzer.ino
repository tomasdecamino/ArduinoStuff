boolean isON[15]={true,true,true,true,true,true,true,true,true,true,true,true,true,true,true};

void setup(){
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  // pinMode(13,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  pinMode(2,OUTPUT); 
  noTone(2); 
}

void loop(){
  if((digitalRead(3)==LOW) && (isON[0]==true)){
    tone(2,640);
    isON[0]=false;
    delay(500);
  }
  if((digitalRead(4)==LOW) && (isON[1]==true)){
    tone(2,640);
    isON[1]=false;
    delay(500);
  }
  if((digitalRead(5)==LOW) && (isON[2]==true)){
    tone(2,640);
    isON[2]=false;
    delay(500);
  }
  if((digitalRead(6)==LOW) && (isON[3]==true)){
    tone(2,640);
    isON[3]=false;
    delay(500);
  }
  if((digitalRead(7)==LOW) && (isON[4]==true)){
    tone(2,640);
    isON[4]=false;
    delay(500);
  }
  if((digitalRead(8)==LOW) && (isON[5]==true)){
    tone(2,640);
    isON[5]=false;
    delay(500);
  }
  if((digitalRead(9)==LOW) && (isON[6]==true)){
    tone(2,640);
    isON[6]=false;
    delay(500);
  }
  if((digitalRead(10)==LOW) && (isON[7]==true)){
    tone(2,640);
    isON[7]=false;
    delay(500);
  }
  if((digitalRead(11)==LOW) && (isON[8]==true)){
    tone(2,640);
    isON[8]=false;
    delay(500);
  }
  if((digitalRead(12)==LOW) && (isON[9]==true)){
    tone(2,640);
    isON[9]=false;
    delay(500);
  }
  /*if((digitalRead(13)==LOW) && (isON[10]==true)){
   tone(2,640);
   isON[0]=false;
   delay(500);
   }*/
  if((digitalRead(A0)==LOW) && (isON[10]==true)){
    tone(2,640);
    isON[10]=false;
    delay(500);
  }
  if((digitalRead(A1)==LOW) && (isON[11]==true)){
    tone(2,640);
    isON[11]=false;
    delay(500);
  }
  if((digitalRead(A2)==LOW) && (isON[12]==true)){
    tone(2,640);
    isON[12]=false;
    delay(500);
  }
  if((digitalRead(A3)==LOW) && (isON[13]==true)){
    tone(2,640);
    isON[13]=false;
    delay(500);
  }
  if((digitalRead(A4)==LOW) && (isON[14]==true)){
    tone(2,640);
    isON[14]=false;
    delay(500);
  }
  noTone(2); 

}







