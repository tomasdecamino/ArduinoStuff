String s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
        if (Serial.available() > 0) {
                // read the incoming byte:
                s = Serial.readStringUntil('\n');

                // say what you got:
                Serial.print("I received: ");
                Serial.println(getToken(s,',',3));
        }
}

String getToken(String string, char separator, int pos){
 int first=0;
 for(int i=0;i<pos-1;i++){
   first=string.indexOf(separator,first+1);
 }
 int last = string.indexOf(separator,first+1);
 if(last==-1)last=string.length(); 
 return string.substring(first+1,last); 
}
