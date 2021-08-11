#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
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
char buf[4];
  
 
File myfile,myfile_R;
String line;
String f_name =  "devindi.txt";
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int DOWN = 8, REC = 9;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;
int k;

void setup() {
   //pinMode(9,OUTPUT);
  DDRD =255;
   #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif



 // Serial.begin(9600);
//  while (!Serial){
   // ;
// }
  
  if(!SD.begin(chipselect)){
    //Serial.println("Card failed or not present !");
    while(1);
  }
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);

 
 // lcd.begin(16,2);
  pinMode (RECval,INPUT);
  //pinMode (UP,INPUT);
  pinMode (DOWN,INPUT);
  //pinMode (SELECT,INPUT);
  //pinMode (BACK,INPUT);
  lcd.print("Voice Recorder");
  delay(1000);
  Menu();
}

void loop() {
  // put your main code here, to run repeatedly:
  RECval = digitalRead(9);
  UPval = analogRead(A2);
  DOWNval = digitalRead(DOWN);
  SELval = analogRead(A3);
  BACKval = analogRead(A1);
  
  Recording();
  Navigate();
  if (SELval > 900 and Screen == 1 and Row == 1){
    PlayBackAudio();
  }
  if (SELval >900 and Screen == 1 and Row == 2){
    DeleteAudio();
  }
  PlayClipI();
  PlayClipII();
  DeleteClipI();
  DeleteClipII();
  Back();
}

void Recording(){
    if (RECval==1){
    lcd.noBlink();
    myfile = SD.open(f_name,FILE_WRITE);
    lcd.clear();
    lcd.print("RECORDING...");
    
    myfile.print("");
    int x;
    int sample;
    //unsigned long CurrentTime1;
    x = analogRead(A0);
    
    while (RECval == 1){
    RECval = digitalRead(9);
      
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    x = analogRead(A0);
    sample = x/4;
    if (sample < 10){s = "00";s.concat(sample);}
    else if(sample < 100){s = "0";s.concat(sample);}
    else{s = "";s.concat(sample);}
    myfile.print(s);
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    }
    
    myfile.close();
    lcd.clear();
    lcd.print("File Saved");
    delay(1000);
    Menu();
    Row = 0;
    Screen = 1;
  }
}

void Navigate(){
  if (UPval > 900){
    lcd.setCursor(0,0);
    lcd.blink();
    Row = 1;
  }
  
  if (DOWNval == 1){
    lcd.setCursor(0,1);
    lcd.blink();
    Row = 2;
  }
}

void Menu(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("PlayBack Audio");
    lcd.setCursor(1,1);
    lcd.print("Delete Audio");
    Screen = 1;
    Row = 0;
}

void PlayBackAudio(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 1");
    lcd.setCursor(1,1);
    lcd.print("Audio 2");
    Screen = 2;
    Row = 0;  
}

void DeleteAudio(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 1");
    lcd.setCursor(1,1);
    lcd.print("Audio 2");
    Screen = 3;
    Row = 0;
}

void PlayClipI(){
  if (SELval > 900 and Row == 1 and Screen == 2){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("No Effect");
    lcd.setCursor(1,1);
    lcd.print("Effect 1");
    Screen = 4;
    Row =0;
  }
  if (SELval > 900 and Row == 2 and Screen == 2){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("No Effect");
    lcd.setCursor(1,1);
    lcd.print("Effect 1");
    Screen = 5;
    Row =0;
  }
}

void PlayClipII(){
  if (SELval > 900 and Row == 1 and Screen == 4){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 1");   

     //******************************************************************************
     //******************************************************************************
     //******************************************************************************
     unsigned long currenttime;
     myfile_R = SD.open(f_name,FILE_READ);
     if (myfile_R) {
      unsigned long starttime = millis();
      while (myfile_R.available()) {
       myfile_R.read(buf,3);
      buf[4]={'\0'};
      //myfile1.println(buf);
      //Serial.println(buf);
      //myfile1.println(buf);
     // buf[4]={'\0'};
     k=buf[0]*100+buf[1]*10+buf[2];
      PORTD =k;
     delayMicroseconds(93);
      }
     currenttime = millis();
     unsigned long elapsedtime = currenttime - starttime;
     myfile_R.close();
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print("end"); 
     delay(2000);
     lcd.clear();
     lcd.setCursor(1,0);
     lcd.print(elapsedtime); 
     delay(2000);
     Menu();
    }   
    
  }
  if (SELval > 900 and Row == 2 and Screen == 4){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 1");
    lcd.setCursor(1,1);
    lcd.print("with Effect 1");
  }
  if (SELval > 900 and Row == 1 and Screen == 5){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 2");    
  }
  if (SELval > 900 and Row == 2 and Screen == 5){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 2");
    lcd.setCursor(1,1);
    lcd.print("with Effect 1");
  }
}

void DeleteClipI(){
  if (SELval > 900 and Row != 0 and Screen == 3){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Press Select");
    lcd.setCursor(1,1);
    lcd.print("to delete");
    Screen = 6;
    Row = 0;
  }
}

void DeleteClipII(){
  if (SELval < 900 and Screen == 6){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Deleted");
    delay(1000);
    Menu(); 
  } 
}

void Back(){
  if (BACKval > 900 and (Screen == 2 or Screen == 3)){
    Menu();
  }
  if (BACKval > 900 and (Screen == 4 or Screen == 5)){
    PlayBackAudio();
  }
}
