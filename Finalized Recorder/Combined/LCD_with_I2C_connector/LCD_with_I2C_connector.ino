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

  
 
File myfile,myfile_R;
String line;
String f_name =  "music501.txt";
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int DOWN = 8, BACK = 9;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;

void setup() {
  
   #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  DDRD = 225;

  Serial.begin(9600);
  while (!Serial){
    ;
 }
 // Serial.println("Initializing the SD card...");
 if(!SD.begin(chipselect)){
    //Serial.println("Card failed or not present !");
  while(1);
  }
 //Serial.println("Card initialized.");

 
  //lcd.begin(16,2);
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
    while (RECval == 1){

      RECval = digitalRead(9);
      
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     
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
      s="";
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
     
     myfile_R = SD.open(f_name,FILE_READ);
     if (myfile_R) {
      while (myfile_R.available()) {
        line=myfile_R.readStringUntil(' ');
        PORTD = line.toInt();
      }
     myfile_R.close();   
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
