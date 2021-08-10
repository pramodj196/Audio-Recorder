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
String k;

void setup() {
  #if FASTADC
    // set prescale to 16
    cbi(ADCSRA,ADPS2) ;
    cbi(ADCSRA,ADPS1) ;
    sbi(ADCSRA,ADPS0) ;
  #endif

  
  Serial.begin(9600);
    while (!Serial){
      ;
    }



  Serial.println("Initializing the SD card...");
  if(!SD.begin(chipselect)){
    Serial.println("Card failed or not present !");
    while(1);
  }
  Serial.println("Card initialized.");
 
  File myfile = SD.open("done35.txt",O_CREAT | O_WRITE);

  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

  int x;
  int sample;
  unsigned long CurrentTime1;
  unsigned long ElapsedTime1;
  x = analogRead(A0);
  myfile.print("");
  
  unsigned long StartTime1 = millis();
  
  while(1){
    
    x = analogRead(A0);
    sample = x/4;
    if (sample < 10){s = "00";s.concat(sample);}
    else if(sample < 100){s = "0";s.concat(sample);}
    else{s = "";s.concat(sample);}

    
    myfile.print(s);
    
    
    CurrentTime1 = millis();
    if ((CurrentTime1 - StartTime1) > 10000 ){
      ElapsedTime1 = CurrentTime1 - StartTime1;
      myfile.seek(0);
      myfile.print(ElapsedTime1);
      myfile.print(" ");
      myfile.close();
      break;
    }
  }
  Serial.println("Accomplished");

}

void loop() {}
