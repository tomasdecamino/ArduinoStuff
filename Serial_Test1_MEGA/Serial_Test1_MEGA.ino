int tesselate[108]= {
  0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5,
  6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 
  24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 
  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
  42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 
  48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 
  54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
  66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71};



//@author> Tomas de Camino

const String hexTable = "0123456789ABCDEF";//to find the base 10 value of Hexadecimal

void setup() 
{ 
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);

} 

void loop() 
{ 
  char serialdata[1727];
  if (Serial.available() > 0) {

    Serial.readBytesUntil('\n', serialdata, 1728);
    Serial.println('~');
    Serial.println(serialdata);
    Serial.println('~');
    /*if(incomingByte =='R'){
     digitalWrite(2,HIGH);
     delay(500);
     }*/
    delay(500);

  }

}

/******************** FUNCTIONS *********************/

int hexToRed(String h){
  return (hexTable.indexOf(h[0]) * 16 + hexTable.indexOf(h[1])) ;

}

int hexToGreen(String h){
  return (hexTable.indexOf(h[2]) * 16 + hexTable.indexOf(h[3])) ;

}

int hexToBlue(String h){
  return (hexTable.indexOf(h[4]) * 16 + hexTable.indexOf(h[5])) ;
}


int reMap(int x,int y){
  return tesselate[12*y+x]; 

}


void setArrayPixel(int x, int y, int r, int g, int b){
  if( y < 9){
    //strip1.setPixel(tesselate[12*y+x],r,g,b);
  } 
  else if(y<18){
    //  strip2.setPixel(tesselate[12*(y-9)+x],r,g,b);
  }
  else if(y<27){
    // strip3.setPixel(tesselate[12*(y-18)+x],r,g,b);
  }
  else if(y<36){
    // strip4.setPixel(tesselate[12*(y-27)+x],r,g,b);
  } 
}

void vLine(int column){
  for(int i = 0; i<12;i++){
    for(int j =0; j<37;j++){
      if(column==i){
        setArrayPixel(i,j,255,0,0);
      }
      else{
        setArrayPixel(i,j,0,0,0);
      }
    }
  } 
  /*strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();*/

}



