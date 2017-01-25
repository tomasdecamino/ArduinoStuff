/*
 Andee.h - Annikken Andee Library
 Copyright (c) 2014 Piasim Corporation Pte Ltd.  All right reserved.
 Apr 2014
 Build 18 //Support For iOS
 */

#include "Arduino.h"
#include "Andee.h"

#include <time.h>
#include <SPI.h>


AndeeClass Andee;
char incomingBuffer[150]; //150
int spiCS = 8;
AndeeClass::AndeeClass(){
    
}
bool AndeeClass::sendCommand(char* cmd, char* buffer){
    char buf[64];
    int i;
    char rData;
    char len;
    char delayAmount;
    char _link = 0;
    char _id = 99;
    int timeout = 50*3; //milliseconds * 5
    
    sprintf(buf, "%i,%04i#_CMD,%s;",_link,_id, cmd);
    memset(incomingBuffer, 150, 0x00);
    
    rData = spi_transfer('#');
    if(rData != 0x00){
        //_mailbox[AndeeHelperMailboxSize++] = rData;
    }
    delay(2); //delay is needed here because the first char wakes AndeeHelper from sleep. This is to give time for AndeeHelper to react before sending the second char
    //delayMicroseconds(500);
    
    i = 0;
    //Serial.println("before while");
    while(buf[i] != '\0'){
        
        rData = spi_transfer(buf[i++]);
        if(rData != 0x00){
            //_mailbox[AndeeHelperMailboxSize++] = rData;
        }
        //delayMicroseconds(200);
    }
    
    //Serial.println("friendly");
    while(rData != 0x00){
        rData = spi_transfer(0x00);
        //if(rData != 0x00)
        //_mailbox[AndeeHelperMailboxSize++] = rData;
        //delay(20);
    }
    
    len = strlen(buf);
    if(len > 30){
        delayAmount = len/30;
        delayAmount += 15;
        
    }
    else{
        delayAmount = 15;
    }
    
    delay(delayAmount);
    
    //Some commands do not wait for replies
    if(strcmp("_CLR", cmd)==0 || strcmp("_DCN", cmd)==0){
        return true;
    }
    
    for(i=0; i<timeout; i++){
        
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            
            if(strlen(incomingBuffer) >= 8){
                strcpy(buffer, incomingBuffer+8);
                if(incomingBuffer[6]=='S') {
                    //Serial.println("returning true");
                    return true;
                }
                else if(strcmp("OK", incomingBuffer+6) == 0){
                    //Serial.println("ack replied!");
                    return true;
                }
                else {
                    return false;
                }
            }
            else{
                //Serial.println("no reply message");
                buffer[0] = 0x00;
                return false;
            }
        }
    }
    //Serial.println("Time out for sendCommand");
    //strcpy(buffer, "Timeout waiting to reply.");
    //buffer[0] = 0x00;
    return false;
}

bool AndeeClass::sendCommand(char* cmd, char* buffer, int timeout){
    char buf[64];
    int i;
    char rData;
    char len;
    char delayAmount;
    char _link = 0;
    char _id = 99;
    int _timeout; //milliseconds * 5
    
    _timeout = 50*timeout;
    
    sprintf(buf, "%i,%04i#_CMD,%s;",_link,_id, cmd);
    memset(incomingBuffer, 150, 0x00);
    
    rData = spi_transfer('#');
    if(rData != 0x00){
        //_mailbox[AndeeHelperMailboxSize++] = rData;
    }
    delay(2); //delay is needed here because the first char wakes AndeeHelper from sleep. This is to give time for AndeeHelper to react before sending the second char
    //delayMicroseconds(500);
    
    i = 0;
    //Serial.println("before while");
    while(buf[i] != '\0'){
        
        rData = spi_transfer(buf[i++]);
        if(rData != 0x00){
            //_mailbox[AndeeHelperMailboxSize++] = rData;
        }
        //delayMicroseconds(200);
    }
    
    //Serial.println("friendly");
    while(rData != 0x00){
        rData = spi_transfer(0x00);
        //if(rData != 0x00)
        //_mailbox[AndeeHelperMailboxSize++] = rData;
        //delay(20);
    }
    
    len = strlen(buf);
    if(len > 30){
        delayAmount = len/30;
        delayAmount += 15;
        
    }
    else{
        delayAmount = 15;
    }
    
    delay(delayAmount);
    
    //Some commands do not wait for replies
    if(strcmp("_CLR", cmd)==0 || strcmp("_DCN", cmd)==0){
        return true;
    }
    
    for(i=0; i<_timeout; i++){
        
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            
            if(strlen(incomingBuffer) >= 8){
                strcpy(buffer, incomingBuffer+8);
                if(incomingBuffer[6]=='S') {
                    //Serial.println("returning true");
                    return true;
                }
                else if(strcmp("OK", incomingBuffer+6) == 0){
                    //Serial.println("ack replied!");
                    return true;
                }
                else {
                    return false;
                }
            }
            else{
                //Serial.println("no reply message");
                buffer[0] = 0x00;
                return false;
            }
        }
    }
    //Serial.println("Time out for sendCommand");
    //strcpy(buffer, "Timeout waiting to reply.");
    //buffer[0] = 0x00;
    return false;
}

void AndeeClass::clear(){
    
    sendCommand("_CLR", "");
    delay(100);
}

void AndeeClass::disconnect(){
    sendCommand("_DCN", "");
}
void AndeeClass::setScreenOrientation(int orientation){
    sprintf(incomingBuffer, "_SOW,0,%i", orientation);
    sendCommand(incomingBuffer, NULL);
}
void AndeeClass::screenAlwaysOn(bool b){
    if(b)
        sendCommand("_SOW,1,1", NULL);
    else
        sendCommand("_SOW,1,0", NULL);
}
int AndeeClass::readBytesFromSD(char* filename, int offset, char* replyBuffer, int numBytesToRead){
    return SDCommands(filename, offset, replyBuffer, NULL, 1, numBytesToRead);
}

int AndeeClass::readLineFromSD(char* filename, int offset, char* replyBuffer, int maxLen, char* delimiter){
    return SDCommands(filename, offset, replyBuffer, delimiter, 4, maxLen);
}

int AndeeClass::appendSD(char* filename, char* contents, char* errorMsg){
    return SDCommands(filename, 0, errorMsg, contents, 2, 0);
}

int AndeeClass::writeSD(char* filename, char* contents, int offset, char* errorMsg){
    return SDCommands(filename, offset, errorMsg, contents, 3, 0);
}



int AndeeClass::SDCommands(char* filename, int offset, char* replyBuffer, char* contents, char type, int numBytesToRead){
    char buf[256];
    char reply[128];
    bool incoming;
    int timeout = 50*5; //milliseconds * 5
    char i;
    int result;
    char position[10];
    int pos;
    int tmp;
    int errorLen;
    int delayAmount;
    char rData;
    char len;
    
    replaceChars(contents);
    
    if(type == 0)
        sprintf(buf, "%i,%04i#_CMD,SDRL,%i,%s,%i;",0, 99, offset, filename, numBytesToRead);
    else if(type == 1){
        sprintf(buf, "%i,%04i#_CMD,SDRB,%i,%i,%s;",0, 99, offset, numBytesToRead, filename);
        //Serial.println(buf);
    }
    else if(type == 2){
        sprintf(buf, "%i,%04i#_CMD,SDAP,%s,%s;",0, 99, filename, contents);
    }
    else if(type == 3){
        sprintf(buf, "%i,%04i#_CMD,SDWR,%i,%s,%s;",0, 99, offset, filename, contents);
    }
    else if(type == 4){
        sprintf(buf, "%i,%04i#_CMD,SDRD,%i,%s,%i,%s;",0, 99, offset, filename, numBytesToRead, contents);
        //Serial.println(buf);
    }
    
    
    //Serial.println(buf);
    rData = spi_transfer('#');
    if(rData != 0x00){
        //_mailbox[AndeeHelperMailboxSize++] = rData;
    }
    delay(2); //delay is needed here because the first char wakes AndeeHelper from sleep. This is to give time for AndeeHelper to react before sending the second char
    //delayMicroseconds(500);
    
    i = 0;
    //Serial.println("before while");
    while(buf[i] != '\0'){
        
        rData = spi_transfer(buf[i++]);
        if(rData != 0x00){
            //_mailbox[AndeeHelperMailboxSize++] = rData;
        }
        //delayMicroseconds(200);
    }
    
    //Serial.println("friendly");
    while(rData != 0x00){
        rData = spi_transfer(0x00);
        //if(rData != 0x00)
        //_mailbox[AndeeHelperMailboxSize++] = rData;
        //delay(20);
    }
    
    len = strlen(buf);
    if(len > 30){
        delayAmount = len/30;
        delayAmount += 15;
        
    }
    else{
        delayAmount = 15;
    }
    
    delay(delayAmount);
    //delay(delayAmount);
    //delay(100); //waiting for system to get ready
    
    for(i=0; i<timeout; i++){
        
        if(getMessagesFromAndee()){
            //Serial.println("here");
            if(incomingBuffer[6]=='S'){
                
                tmp = strcspn(incomingBuffer, ",");
                strncpy(position, incomingBuffer+8, tmp);
                pos = atoi(position);
                strcpy(replyBuffer, incomingBuffer + tmp + 1);
                //Serial.println(replyBuffer);
                return pos;
            }
            else{
                //Serial.println(incomingBuffer);
                errorLen = strcspn(incomingBuffer, ",");
                tmp = strcspn(incomingBuffer + errorLen + 1, ",");
                strncpy(position, incomingBuffer + errorLen + 1, tmp);
                pos = atoi(position);
                if(tmp != -1){
                    strcpy(replyBuffer, incomingBuffer + errorLen + tmp + 2);
                    incomingBuffer[errorLen] = 0x00;
                }
                strcpy(replyBuffer, incomingBuffer+8);
                //Serial.println("returning -1");
                return -1;
            }
        }
    }
    //Serial.println("AndeeClass SD Timeout");
    strcpy(replyBuffer, "TIMEOUT");
    return -1;
}

void AndeeClass::begin(int pin){
    spiCS = pin;
    begin();
}


#if defined (__arm__)
void AndeeClass::begin(){
    
    pinMode(spiCS, OUTPUT);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(spiCS, 21);
    SPI.begin();
    delay(2500);
}

#else
void AndeeClass::begin(){
    
    pinMode(spiCS, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, INPUT);
    pinMode(13, OUTPUT);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    
    digitalWrite(spiCS, HIGH);
    
    //From source of SPI.begin();
    pinMode(SS, OUTPUT);
    
    // Warning: if the SS pin ever becomes a LOW INPUT then SPI
    // automatically switches to Slave, so the data direction of
    // the SS pin MUST be kept as OUTPUT.
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);
    
    // Set direction register for SCK and MOSI pin.
    // MISO pin automatically overrides to INPUT.
    // By doing this AFTER enabling SPI, we avoid accidentally
    // clocking in a single bit since the lines go directly
    // from "input" to SPI control.
    // http://code.google.com/p/arduino/issues/detail?id=888
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    
    //SPI.begin();
    delay(2500);
}
#endif
char AndeeClass::isConnected(){
    char result[2];
    if(sendCommand("CONNSTAT",result)){
        if(result[0] == 'T'){
            return 1;
        }
        else{
            //Serial.println(result);
            return 0;
        }
    }
    else{
        return -1;
    }
}

char AndeeClass::isConnected(int timeout){
    char result[2];
    if(sendCommand("CONNSTAT",result, timeout)){
        if(result[0] == 'T'){
            return 1;
        }
        else{
            //Serial.println(result);
            return 0;
        }
    }
    else{
        return -1;
    }
}

char AndeeClass::spi_transfer(volatile char data)
{
    unsigned char rtnChar;
    digitalWrite(spiCS, LOW);
    delayMicroseconds(4);
    rtnChar = SPI.transfer(data);
    //SPDR = data;                    // Start the transmission
    //while (!(SPSR & (1<<SPIF))){};     // Wait the end of the transmission{
    digitalWrite(spiCS, HIGH);
    //return SPDR;
    return rtnChar;
}
bool AndeeClass::getMessagesFromAndee(){
    int count;
    char rData;
    //char i;
    
    rData = spi_transfer(0x00);
    //count = getBufferLen(_mailbox, _mailboxLen);
    count = 0;
    delay(2); //wake module
    
    while(rData != 0x00){
        //Serial.print(rData);
        incomingBuffer[count++] = rData;
        
        rData = spi_transfer(0x00);
        //Serial.print(rData);
        //delay(1000);
    }
    //Serial.println("\r\n");
    incomingBuffer[count] = '\0';
    //Serial.println(count);
    //delay(3);
    if(count > 0){
        //Serial.println("REPLIED");
        return true;
    }
    else{
        //Serial.println("no reply yet");
        //delay(10);
        return false;
    }
}

void AndeeClass::replaceChars(char* buffer){
    int len;
    int i;
    
    len = strlen(buffer);
    for(i=0; i<len; i++){
        if(buffer[i] == ';'){
            
            buffer[i] = 0x05;
        }
    }
}

AndeeHelper::AndeeHelper(){
    _id = -1;
}

void AndeeHelper::replaceChars(char* buffer){
    int len;
    int i;
    len = strlen(buffer);
    for(i=0; i<len; i++){
        if(buffer[i] == ';'){
            buffer[i] = 0x05;
        }
    }
}



void AndeeHelper::textAndee(char* cmd, char* buffer){
    char buf[128]; //128
    int i;
    char rData;
    char len;
    char delayAmount;
    int timeout = 50*3; //milliseconds * 5
    //int timeout = 10; //milliseconds * 5
    
    if(_id < 0) return;
    
    
    if(strlen(buffer)==0){
        sprintf(buf, "#%i,%04i#%s,;",_link,_id, cmd);
    }
    else{
        replaceChars(buffer);
        sprintf(buf, "#%i,%04i#%s,%s;",_link,_id, cmd, buffer);
    }
    
    memset(incomingBuffer, 0x00, 150); //sensor report functions are using incomingBuffer as buffer
    
    rData = spi_transfer(buf[0]);
    
    if(rData != 0x00){
        //_mailbox[AndeeHelperMailboxSize++] = rData;
    }
    delay(2); //delay is needed here because the first char wakes AndeeHelper from sleep. This is to give time for AndeeHelper to react before sending the second char
    //delayMicroseconds(500);
    
    i = 1;
    //Serial.println("before while");
    while(buf[i] != '\0'){
        
        rData = spi_transfer(buf[i++]);
        if(rData != 0x00){
            //_mailbox[AndeeHelperMailboxSize++] = rData;
            
        }
        
    }
    
    while(rData != 0x00){
        rData = spi_transfer(0x00);
        
    }
    
    if(strcmp(cmd, "_IPS") != 0 && strcmp(cmd, "_KBM") != 0 &&
       strcmp(cmd, "_DMG") != 0 && strcmp(cmd, "_TMG") != 0 && strcmp(cmd, "_SGV") != 0 &&
       strcmp(cmd, "_PSR") != 0 && strcmp(cmd, "_PGS") != 0 && strcmp(cmd, "_ISR") != 0 &&
       strcmp(cmd, "_SSR") != 0 && strcmp(cmd, "_IPN") != 0 && strcmp(cmd, "_NSR") != 0 ){
        
        for(i=0; i<timeout; i++){
            
            if(getMessagesFromAndee()){
                //Serial.println(incomingBuffer);
                if(strcmp("OK", incomingBuffer+6) == 0){
                    //Serial.print("ok:");
                    //Serial.println(cmd);
                    memset(incomingBuffer, 150, 0x00);
                    return;
                }
                else{
                    //Serial.print("gMFA:");
                    //Serial.println(incomingBuffer);
                }
                
            }
            else{
                //Serial.println("nm");
            }
            
        }
//        Serial.print("timeout:");
//        Serial.print(cmd);
//        Serial.println(i,DEC);
        //Serial.print("buffer:");
        //Serial.println(incomingBuffer);
    }
    else{
        
    }
    
}

void AndeeHelper::setId(char id){
    
    _id = id;
    textAndee("_SID", "");
    delayMicroseconds(500);
    //delay(20);
}

char AndeeHelper::spi_transfer(volatile char data)
{
    unsigned char rtnChar;
    digitalWrite(spiCS, LOW);
    delayMicroseconds(4);
    rtnChar = SPI.transfer(data);
    //SPDR = data;                    // Start the transmission
    //while (!(SPSR & (1<<SPIF))){};     // Wait the end of the transmission{
    digitalWrite(spiCS, HIGH);
    //return SPDR;
    return rtnChar;
}
void AndeeHelper::remove(){
    textAndee("_RMV", "");
}
void AndeeHelper::update(){
    textAndee("_UPD", "");
}
void AndeeHelper::updateData(char* text){
    textAndee("_UPV", text);
}
void AndeeHelper::updateData(int value){
    sprintf(incomingBuffer, "%i", value);
    textAndee("_UPV", incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::updateData(float value, char numDecimalPlaces){
    
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];
    bufTmp[0] = '%';
    bufTmp[1] = 0x30 | numDecimalPlaces;
    bufTmp[2] = 'f';
    bufTmp[3] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee("_UPV", incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::updateData(double value, char numDecimalPlaces){
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];
    bufTmp[0] = '%';
    bufTmp[1] = 0x30 | numDecimalPlaces;
    bufTmp[2] = 'f';
    bufTmp[3] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee("_UPV", incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setTitle(char* title){
    textAndee("_TTL", title);
    delay(20); //this if for long titles
}
void AndeeHelper::setTitle(int value){
    setInt(TITLE, value);
}
void AndeeHelper::setTitle(float value, char numDecimalPlaces){
    setFloat(TITLE, value, numDecimalPlaces);
}
void AndeeHelper::setTitle(double value, char numDecimalPlaces){
    setDouble(TITLE, value, numDecimalPlaces);
}
void AndeeHelper::setData(char* data){
    textAndee("_DAT", data);
}
void AndeeHelper::setData(int value){
    setInt(DATA, value);
}
void AndeeHelper::setData(float value, char numDecimalPlaces){
    setFloat(DATA, value, numDecimalPlaces);
}
void AndeeHelper::setData(double value, char numDecimalPlaces){
    setDouble(DATA, value, numDecimalPlaces);
}
void AndeeHelper::setUnit(char* unit){
    textAndee("_UNT", unit);
}
void AndeeHelper::setUnit(int value){
    setInt(UNIT, value);
}
void AndeeHelper::setUnit(float value, char numDecimalPlaces){
    setFloat(UNIT, value, numDecimalPlaces);
}
void AndeeHelper::setUnit(double value, char numDecimalPlaces){
    setDouble(UNIT, value, numDecimalPlaces);
}
void AndeeHelper::setInt(char* type, int value){
    sprintf(incomingBuffer, "%i", value);
    textAndee(type, incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setFloat(char* type, float value, char numDecimalPlaces){
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];
    bufTmp[0] = '%';
    bufTmp[1] = 0x30 | numDecimalPlaces;
    bufTmp[2] = 'f';
    bufTmp[3] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee(type, incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setDouble(char* type, double value, char numDecimalPlaces){
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];
    bufTmp[0] = '%';
    bufTmp[1] = 0x30 | numDecimalPlaces;
    bufTmp[2] = 'f';
    bufTmp[3] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee(type, incomingBuffer);
    memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setRecipient(char* numString){
    textAndee("_TTL", numString);
}
void AndeeHelper::send(){
    textAndee("_UPD", "");
}
void AndeeHelper::setMessage(char* message){
    textAndee("_DAT", message);
}
void AndeeHelper::setTicker(char* message){
    textAndee("_UNT", message);
}
void AndeeHelper::notify(){
    textAndee("_UPD", "");
}

void AndeeHelper::setRow(char row){
    char cmd[2];
    cmd[0] = 0x30 | row;
    cmd[1] = 0x00;
    textAndee("_ROW", cmd);
}
void AndeeHelper::requireAck(bool b){
    if(b)
        textAndee("_RAK", "0");
    else
        textAndee("_RAK", "1");
}

void AndeeHelper::setType(char type){
    char cmd[2];
    cmd[0] = type;
    cmd[1] = 0x00;
    textAndee("_TYP", cmd);
    
}
void AndeeHelper::setOrder(char order){
    char cmd[2];
    cmd[0] = 0x30 | order;
    cmd[1] = 0x00;
    textAndee("_ODR", cmd);
}
void AndeeHelper::setSpan(char span){
    char cmd[2];
    cmd[0] = 0x30 | span;
    cmd[1] = 0x00;
    textAndee("_SPN", cmd);
}
void AndeeHelper::setLocation(char row, char order, char span){
    char cmd[4];
    cmd[0] = 0x30 | row;
    cmd[1] = 0x30 | order;
    cmd[2] = 0x30 | span;
    cmd[3] = 0x00;
    textAndee("_ROS", cmd);
    //delay(20);
}


void AndeeHelper::setColor(char* color){
    textAndee("_DBC", color);
}
void AndeeHelper::setTitleColor(char* color){
    textAndee("_TBC", color);
}
void AndeeHelper::setSliderColor(char* color){
    textAndee("_TBC", color);
}
void AndeeHelper::setTextColor(char color){
    char cmd[2];
    cmd[0] = color;
    cmd[1] = 0x00;
    textAndee("_DTC", cmd);
}
void AndeeHelper::setTextColor(char* color){
    textAndee("_DTC", color);
}
void AndeeHelper::setTitleTextColor(char color){
    char cmd[2];
    cmd[0] = color;
    cmd[1] = 0x00;
    textAndee("_TTC", cmd);
}
void AndeeHelper::setTitleTextColor(char* color){
    textAndee("_TTC", color);
}
void AndeeHelper::setHintText(char* text){
    textAndee("_HTX", text);
}
void AndeeHelper::setKeyboardType(char keyboardType){
    char cmd[2];
    cmd[0] = keyboardType;
    cmd[1] = 0x00;
    textAndee("_KYT", cmd);
}

void AndeeHelper::ack(){
    textAndee("_ACK", "");
}
bool AndeeHelper::isPressed(){
    int timeout = 10*5; //milliseconds * 5
    int i;
    
    textAndee("_IPS", "");
    //delay(10);
    //Serial.println("DElay here");
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            if(isCorrectId(incomingBuffer)){
                if(strcmp(incomingBuffer + 6, "TRUE") == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else{
            //Serial.println("no message yet");
        }
    }
    //Serial.println("isPressed timeout");
    return false;
}

bool AndeeHelper::isPressed(int timeout){
    int _timeout; //milliseconds * 5
    int i;
    
    _timeout = timeout*10;
    textAndee("_IPS", "");
    //delay(10);
        for(i=0; i<_timeout; i++){
        if(getMessagesFromAndee()){
            if(isCorrectId(incomingBuffer)){
                if(strcmp(incomingBuffer + 6, "TRUE") == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false; //incorrect id
            }
        }
        else{
            //Serial.println("no message yet");
        }
    }
    return false; //timeout
}

bool AndeeHelper::newSliderValueAvailable(){
    int timeout = 10*5; //milliseconds * 5
    int i;
    
    textAndee("_NSR", "");
    //delay(10);
    //Serial.println("DElay here");
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            if(isCorrectId(incomingBuffer)){
                if(strcmp(incomingBuffer + 6, "TRUE") == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else{
            //Serial.println("no message yet");
        }
    }
    //Serial.println("slider timeout");
    return false;
}
int AndeeHelper::getButtonPressCount(){
    int timeout = 10*5; //milliseconds * 5
    int i;
    int count;
    count = -1;
    textAndee("_IPN", "");
    //delay(10);
    //Serial.println("DElay here");
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            if(isCorrectId(incomingBuffer)){
                count = atoi(incomingBuffer+6);
                return count;
            }
        }
        else{
            //Serial.println("no message yet");
        }
    }
    //Serial.println("isPressed timeout");
    return count;
}

void AndeeHelper::getKeyboardMessage(char* buffer){
    int timeout = 10*5; //milliseconds * 5
    int i;
    textAndee("_KBM", "");
    delay(10);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            if(isCorrectId(incomingBuffer)){
                strcpy(buffer, incomingBuffer+6);
            }
        }
    }
    //return false;
}
int AndeeHelper::getSliderValue(int f){
    int timeout = 10*1; //milliseconds * 5
    int i;
    int value;
    int id;
    textAndee("_SGV", "");
    delay(2);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //I should verify ID of message
            //Serial.println(incomingBuffer);
            if(isCorrectId(incomingBuffer)){
                value = atoi(incomingBuffer+6);
                return value;
            }
            else{
                //Serial.print("id no match:");
                //Serial.println(incomingBuffer);
            }
        }
    }
    //Serial.println("GSV timeout");
    //Serial.println(incomingBuffer);
    memset(incomingBuffer, 150, 0x00);
    //return false;
}

float AndeeHelper::getSliderValue(float f){
    int timeout = 10*1; //milliseconds * 5
    int i;
    float value;
    int id;
    textAndee("_SGV", "");
    delay(2);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //I should verify ID of message
            
            if(isCorrectId(incomingBuffer)){
                value = atof(incomingBuffer+6);
                return value;
            }
            else{
                //Serial.print("id no match:");
                //Serial.println(incomingBuffer);
            }
        }
    }
    //Serial.println("GSV timeout");
    //Serial.println(incomingBuffer);
    memset(incomingBuffer, 150, 0x00);
    //return false;
}

bool AndeeHelper::isCorrectId(char* address){
    char iid;
    //Serial.print("checking:");
    //Serial.println(address);
    if(strlen(address) < 6)
        return false;
    if(address[0] =='#' && address[5] =='#'){
        iid = atoi(address+3);
        if(iid == _id){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool AndeeHelper::getMessagesFromAndee(){
    char count;
    char rData;
    char i;
    
    rData = spi_transfer(0x00);
    //count = 0; //16.1
    count = strlen(incomingBuffer);//17.1
    delay(2); //wake module
    
    //if loop added for debugging iOS
    if(rData == 0x00){
        //Serial.println("returning");
        delay(2);
        return false;
    }
    
    while(rData != 0x00){
        //Serial.print(rData);
        
        incomingBuffer[count++] = rData;
        rData = spi_transfer(0x00);
        
        
    }
    incomingBuffer[count] = '\0';
    
    delay(3);
    if(count > 0){
        //Serial.println(incomingBuffer);
        //Serial.println("returning true");
        return true;
    }
    else{
        //Serial.println("no messasge");
        
        //Serial.println("return false");
        return false;
    }
}

void AndeeHelper::setDefaultTime(int hr, int min, int sec){
    char buf[7];
    sprintf(buf, "%02i%02i%02i", hr%24, min%60, sec%60);
    textAndee("_TME", buf);
}

void AndeeHelper::setDefaultDate(int date, int mth, int year){
    char buf[9];
    
    sprintf(buf, "%02i%02i%04i", date%31, mth%12, year);
    
    textAndee("_DTE", buf);
}
void AndeeHelper::getTimeInput(char* buffer, char* format){
    int timeout = 10*5; //milliseconds * 5
    int i;
    textAndee("_TMG", format);
    delay(10);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            strcpy(buffer, incomingBuffer+6);
            
        }
    }
    //return false;
}
void AndeeHelper::getTimeInput(int* h, int* m, int* s){
    int timeout = 10*5; //milliseconds * 5
    int i;
    char buffer[6];
    textAndee("_TMG", "hhmmss");
    delay(10);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            strcpy(buffer, incomingBuffer+6);
            *s = atoi(buffer+4);
            buffer[4] = 0x00;
            *m = atoi(buffer+2);
            buffer[2] = 0x00;
            *h = atoi(buffer);
        }
    }
    //return false;
}
void AndeeHelper::getDateInput(char* buffer, char* format){
    int timeout = 10*5; //milliseconds * 5
    int i;
    textAndee("_DMG", format);
    delay(10);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            
            strcpy(buffer, incomingBuffer+6);
            
        }
    }
    //return false;
}

void AndeeHelper::getDateInput(int* d, int* m, int* y){
    int timeout = 10*5; //milliseconds * 5
    int i;
    char buffer[10];
    textAndee("_DMG", "DDMMYYYY");
    delay(10);
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            
            strcpy(buffer, incomingBuffer+6);
            *y = atoi(buffer+4);
            buffer[4] = 0x00;
            *m = atoi(buffer+2);
            buffer[2] = 0x00;
            *d = atoi(buffer);
        }
    }
    //return false;
}

void AndeeClass::printDeviceTime(char* format, char* reply){
    sprintf(incomingBuffer, "DTIME,%s", format);
    sendCommand(incomingBuffer, reply);
}
void AndeeClass::getDeviceTime(int* h, int* m, int* s){
    char buffer[8];
    sendCommand("DTT", buffer);
    *s = atoi(buffer+4);
    buffer[4] = 0x00;
    *m = atoi(buffer+2);
    buffer[2] = 0x00;
    *h = atoi(buffer);
}
void AndeeClass::getDeviceDate(int* d, int* m, int* y){
    char buffer[10];
    sendCommand("DTD", buffer);
    *y = atoi(buffer+4);
    buffer[4] = 0x00;
    *m = atoi(buffer+2);
    buffer[2] = 0x00;
    *d = atoi(buffer);
}
long AndeeClass::getDeviceTimeStamp(){
    char buffer[12];
    sendCommand("DTS", buffer);
    return atol(buffer);
}



void AndeeHelper::setCamera(char type){
    char cmd[2];
    cmd[0] = type;
    cmd[1] = 0x00;
    textAndee("_PSC", cmd);
}
void AndeeHelper::setAutoFocus(char type){
    char cmd[2];
    if(type == ON){
        cmd[0] = '0';
    }
    else{
        cmd[0] = '1';
    }
    cmd[1] = 0x00;
    textAndee("_PSA", cmd);
}
void AndeeHelper::setFlash(char flashType){
    char cmd[2];
    cmd[0] = flashType;
    cmd[1] = 0x00;
    textAndee("_PSF", cmd);
}
void AndeeHelper::setPhotoFilename(char* text){
    textAndee("_PFN", text);
}
void AndeeHelper::takePhoto(){
    textAndee("_PTK", NULL);
}

void AndeeHelper::setSaveLocation(char loc){
    char cmd[2];
    cmd[0] = loc;
    cmd[1] = 0x00;
    textAndee("_PSL", cmd);
}
void AndeeHelper::setFileOverwrite(char type){
    char cmd[2];
    if(type == ON)
        cmd[0] = '1';
    else
        cmd[0] = '0';
    cmd[1] = 0x00;
    textAndee("_PFO", cmd);
}

bool AndeeHelper::takePhotoResultReady(){
    int timeout = 10*5; //milliseconds * 5
    int i;
    
    textAndee("_PSR", "");
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            if(strcmp(incomingBuffer + 6, "T") == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            //Serial.println("no message yet");
        }
    }
    //Serial.println("isPressed timeout");
    return false;
}
char AndeeHelper::getLastTakePhotoResult(){
    int timeout = 10*5; //milliseconds * 5
    int i;
    char result;
    
    textAndee("_PGS", "");
    for(i=0; i<timeout; i++){
        if(getMessagesFromAndee()){
            //Serial.println(incomingBuffer);
            result = incomingBuffer[6];
            
            switch(result){
                case '0': return 0;
                case '1': return -1; 
                case '2': return -2;
                case '3': return -3; 
                case '4': return -4;
                case '5': return 0;
                case '6': return -5;
            }
            
            return -6;
            
            
        }
        else{
            
        }
    }
    
    return -7;
}


void AndeeHelper::setSliderMinMax(float min, float max, char numDecimalPlaces){
    char len;
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];	
    bufTmp[0] = '%';
    bufTmp[1] = '.';
    bufTmp[2] = 0x30 | numDecimalPlaces;
    bufTmp[3] = 'f';
    bufTmp[4] = 0x00;
    sprintf(incomingBuffer, bufTmp, min);
#else
    dtostrf(min, 3, numDecimalPlaces, incomingBuffer);
#endif
    len = strlen(incomingBuffer);
    incomingBuffer[len] = ',';
    
#if defined (__arm__)	
    sprintf(incomingBuffer + len + 1, bufTmp, max);
#else
    dtostrf(max, 3, numDecimalPlaces, incomingBuffer + len + 1);
#endif
    
    textAndee("_SMM", incomingBuffer);
    //memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setSliderMinMax(int min, int max){
    char len;
    sprintf(incomingBuffer, "%i,%i", min, max);
    textAndee("_SMM", incomingBuffer);
    //memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setSliderInitialValue(float value, char numDecimalPlaces){
    
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];	
    bufTmp[0] = '%';
    bufTmp[1] = '.';
    bufTmp[2] = 0x30 | numDecimalPlaces;
    bufTmp[3] = 'f';
    bufTmp[4] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee("_SLD", incomingBuffer);
    //memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setSliderInitialValue(int value){
    
    sprintf(incomingBuffer, "%i", value);
    textAndee("_SLD", incomingBuffer);
    //memset(incomingBuffer, 64, 0x00);
}
void AndeeHelper::setSliderNumIntervals(int numInterval){
    sprintf(incomingBuffer, "%i", numInterval);
    textAndee("_SIN", incomingBuffer);
}
void AndeeHelper::moveSliderToValue(int value){
    sprintf(incomingBuffer, "%i", value);
    textAndee("_SMV", incomingBuffer);
}
void AndeeHelper::moveSliderToValue(float value, char numDecimalPlaces){
    if(numDecimalPlaces < 1)
        numDecimalPlaces = 1;
#if defined (__arm__)
    char bufTmp[5];	
    bufTmp[0] = '%';
    bufTmp[1] = 0x30 | numDecimalPlaces;
    bufTmp[2] = 'f';
    bufTmp[3] = 0x00;
    sprintf(incomingBuffer, bufTmp, value);
#else
    dtostrf(value, 3, numDecimalPlaces, incomingBuffer);
#endif
    textAndee("_SMV", incomingBuffer);
}

void AndeeHelper::setSliderReportMode(char mode){
    sprintf(incomingBuffer, "%c", mode);
    textAndee("_SRM", incomingBuffer);
}

//Only for iOS, ignored in Android
void AndeeHelper::setAccent(int type){
    setInt("_TAC", type);
}

void AndeeHelper::setUtteranceSpeed(float value){
    setFloat("_TUS", value, 1);
}

void AndeeHelper::setPitch(float value){
    setFloat("_TSP", value, 1);
}


