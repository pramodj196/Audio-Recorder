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
File recFile,lfilter,hfilter;
String line;
String filename;
String f;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int DOWN = 8;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;
int k;
int filenumber =1;
int y_pre = 0;

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
  pinMode (9,INPUT);
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
  filename =  String("Audio") + filenumber ;
  filename = String(filename) +".txt";
  Recording();
  Navigate();
  if (SELval > 900 and Screen == 1 and Row == 1){
    PlayBackAudioI();
    filenumber = 1;
  }
  if (SELval >900 and Screen == 1 and Row == 2){
    DeleteAudioI();
    filenumber = 1;
  }
  if (SELval >900 and Screen >=2 and Screen<=5 and Row == 1){
    NPlayClip();
  }
  NEXT();
  PlayClipII();
  DeleteClipI();
  DeleteClipII();
  Back();
}
void NEXT(){
  if (SELval > 900 and Screen == 2 and Row == 2){
    PlayBackAudioII();
     filenumber = 2;
  }
  if (SELval > 900 and Screen == 3 and Row == 2){
    PlayBackAudioIII();
    filenumber = 3;
  }
  if (SELval > 900 and Screen == 4 and Row == 2){
    PlayBackAudioIV();
    filenumber = 4;
  }
  if (SELval >900 and Screen == 100 and Row == 2){
    DeleteAudioII();
    filenumber = 2;
  }
  if (SELval >900 and Screen == 101 and Row == 2){
    DeleteAudioIII();
    filenumber = 3;
  }
  if (SELval >900 and Screen == 102 and Row == 2){
    DeleteAudioIV();
    filenumber = 4;
  }
  if (SELval >900 and Screen == 6 and Row == 2){
    BassClip();
  }
  if (SELval >900 and Screen == 7 and Row == 2){
    TrebleClip();
  }
}
void Recording(){
    if (RECval==1){
    lcd.noBlink();
    myfile = SD.open(filename,FILE_WRITE);
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
    filenumber++;
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
void bassfilter(){
  recFile = SD.open(filename, FILE_READ);
  f =filename + String(" lowpass.txt");
  lfilter = SD.open(f,FILE_WRITE);
  if (recFile) {
      unsigned long starttime = millis();
      while (recFile.available()) {
       recFile.read(buf,3);
      buf[4]={'\0'};
      //myfile1.println(buf);
      //Serial.println(buf);
      //myfile1.println(buf);
     // buf[4]={'\0'};
     k=buf[0]*100+buf[1]*10+buf[2];
     int y_current=(0.42335*y_pre)+(0.8665*k);
      lfilter.println(String(y_current));
      y_pre=y_current;
   }
   lfilter.close();
   recFile.close();
   y_pre=0;
  
}
}
void treblefilter(){
  recFile = SD.open(filename, FILE_READ);
  f =filename + String(" highpass.txt");
  hfilter = SD.open(f,FILE_WRITE);
  if (recFile) {
      unsigned long starttime = millis();
      while (recFile.available()) {
       recFile.read(buf,3);
      buf[4]={'\0'};
      //myfile1.println(buf);
      //Serial.println(buf);
      //myfile1.println(buf);
     // buf[4]={'\0'};
     k=buf[0]*100+buf[1]*10+buf[2];
      int y_current=( -0.41238*y_pre)+(0.803321*k);
      lfilter.println(String(y_current));
      y_pre=y_current;
   }
   hfilter.close();
   recFile.close();
   y_pre=0;
}
}

void PlayBackAudioI(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 1");
    Screen = 2;
    Row = 0;  
}
void PlayBackAudioII(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 2");
    Screen = 3;
    Row = 0;  
}
void PlayBackAudioIII(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 3");
    Screen = 4;
    Row = 0;  
}
void PlayBackAudioIV(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 4");
    Screen = 5;
    Row = 0;  
}
void DeleteAudioI(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 1");
    Screen = 100;
    Row = 0;
}
void DeleteAudioII(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 2");
    Screen = 101;
    Row = 0;
}
void DeleteAudioIII(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 3");
    Screen = 102;
    Row = 0;
}
void DeleteAudioIV(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Audio 4");
    Screen = 103;
    Row = 0;
}

void NPlayClip(){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("No Effect");
    Screen = 6;
    Row =0;
}
void BassClip(){
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(1,0);
  lcd.print("Bass");
  Screen = 7;
  Row=0;
}
void TrebleClip(){
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(1,0);
  lcd.print("Treble");
  Screen = 8;
  Row=0;
}

void PlayClipII(){
  if (SELval > 900 and Row == 1 and Screen == 6){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(filename + String("..."));     

     //******************************************************************************
     //******************************************************************************
     //******************************************************************************
     unsigned long currenttime;
     myfile_R = SD.open(filename,FILE_READ);
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
  if (SELval > 900 and Row == 1 and Screen == 7){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(filename+String("..."));
    lcd.setCursor(1,1);
    lcd.print("with Bass Effect");
    bassfilter();
    f =filename + String("lowpass.txt");
    //******************************************************************************
     //******************************************************************************
     //******************************************************************************
     unsigned long currenttime;
    myfile_R = SD.open(f,FILE_READ);
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
  if (SELval > 900 and Row == 1 and Screen == 8){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(filename+String("..."));
    lcd.setCursor(1,1);
    lcd.print("with Treble Effect");
    bassfilter();
    f =filename + String("highpass.txt");
    //******************************************************************************
     //******************************************************************************
     //******************************************************************************
     unsigned long currenttime;
    myfile_R = SD.open(f,FILE_READ);
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
}
void DeleteClipI(){
  if (SELval > 900 and Row ==1 and Screen >=100 and Screen <=103){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Confirm");
    lcd.setCursor(1,1);
    lcd.print("Cancel");
    Screen = 104;
    Row = 0;
  }
}


void DeleteClipII(){
  if (SELval > 900 and Screen == 104 and Row == 1 ){
    SD.remove(filename);
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(String("Deleted ")+ filename);
    delay(1000);
    Menu(); 
  } 
  if (SELval > 900 and Screen == 104 and Row == 2 ){
    Menu(); 
  } 
 
}

void Back(){
  if (BACKval >900 ){
    Menu();
  }
  /*if (BACKval >900 and (Screen ==6)){
    PlayBackAudioI();
  }*/
}
