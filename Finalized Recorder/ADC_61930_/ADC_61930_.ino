#include<SPI.h>
#include<SD.h>

#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


const int chipselect = 10;
String s = "";
char s2[]={};
int len;


void setup() {
  
  #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif


  Serial.begin(9600);
  while (!Serial){
    ;
 }
  if(!SD.begin(chipselect)){
    Serial.println("Card failed or not present !");
    while(1);
  }
 Serial.println("Card initialized.");
 
  File myfile = SD.open("music303.txt",FILE_WRITE);
  unsigned long StartTime = millis();

  
  while(1) {
    int y1=analogRead(A0);
    
    int mapped = map(y1, 0, 1023, 0, 255);
    s.concat(mapped);

    if (mapped<10) {
      char s2[] = {s[0],' '};
      myfile.write(s2,2);
      }
    else if (mapped<100) {
      char s2[] = {s[0],s[1],' '};
      myfile.write(s2,3);
      }
    else {
      char s2[] = {s[0],s[1],s[2],' '};
      myfile.write(s2,4);
      }
      

    unsigned long CurrentTime = millis();
    unsigned long ElapsedTime = CurrentTime - StartTime;
    if (ElapsedTime >10000){
    
      myfile.close();
      break;
      
  }
  s="";
  
}
}

void loop(){}
