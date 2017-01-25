
/*UP FFA05F
  DOWN FFA857
  LEFT FF18E7
  RIGHT FF58A7
  ENTER FF9867
*/  

//este ejemplo prende el led con el bot'on de enter
#include <IRremote.h>

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(13,OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value==16750695){
      digitalWrite(13,HIGH);
      delay(1000); 
    }else{
      digitalWrite(13,LOW);
    }
    irrecv.resume(); // Receive the next value
  }
}

