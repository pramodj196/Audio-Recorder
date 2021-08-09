#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<SPI.h>
#include<SD.h>
const int chipselect = 10;
File myfile,myfile_R;
File recFile,lfilter;
String line;
String filename;
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int DOWN = 8, BACK = 9;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;
int filenumber =1;
void setup() {
  DDRD = 225;

  /*Serial.begin(9600);
  while (!Serial){
    ;
 }
  Serial.println("Initializing the SD card...");*/
  if(!SD.begin(chipselect)){
    while(1);
  }
 //Serial.println("Card initialized.");

 
  lcd.begin(16,2);
  pinMode (DOWN,INPUT);
  pinMode (BACK,INPUT);
  lcd.print("Voice Recorder");
  delay(1000);
  Menu();
}

void loop() {
  // put your main code here, to run repeatedly:
  RECval = analogRead(A1);
  UPval = analogRead(A2);
  DOWNval = digitalRead(DOWN);
  SELval = analogRead(A3);
  BACKval = digitalRead(BACK);
  filename =  String("Devindi") + filenumber ;
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
  NEXT();
  PlayClipI();
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
}
void Recording(){
    if (RECval>900){
    lcd.noBlink();
    
    myfile = SD.open(filename,FILE_WRITE);
    while (RECval>900){
      lcd.clear();
      lcd.print("Recording");
      for (int i = 0; i <= 3; i++) {
       lcd.print(".");
       delay(50);
      }
      RECval = analogRead(A1);
      lcd.clear();

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     
    int x = analogRead(A0);
    int sample = map(x,0,1023,0,255);
    myfile.println(sample);
    //Serial.println(sample);
    
    
    }
    myfile.close();
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
void bassfilter_main(){
   recFile = SD.open(filename, FILE_READ);
   lfilter = SD.open("lowpass.txt",FILE_WRITE);
   int list1[1000];
   for (int i = 0; i <= 999; i++){
        int line_=line.toInt();
        list1[i]= line_;
      }
   while(recFile.available()){
      line = recFile.readStringUntil('\n');
      for (int i = 0; i <= 995; i++){
        int y_current = (0.0284064700150113*list1[i] + 0.237008213590703*list1[i+1] + 0.469170632788571*list1[i+2] + 0.237008213590703*list1[i+3] + 0.0284064700150113*list1[i+4]);
        lfilter.println(String(y_current));
      }
   }
   lfilter.close();
   recFile.close();
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
void PlayClipI(){
  if (SELval > 900 and Row == 1 and Screen >= 2 and Screen <=5){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("No Effect");
    lcd.setCursor(1,1);
    lcd.print("Effect 1");
    Screen = 6;
    Row =0;
  }
}

void PlayClipII(){
  if (SELval > 900 and Row == 1 and Screen == 6){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(filename);   
    for (int i = 0; i <= 3; i++) {
       lcd.print(".");
       delay(50);
      }
     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     myfile_R = SD.open(filename,FILE_READ);
     if (myfile_R) {
      while (myfile_R.available()) {
        line=myfile_R.readStringUntil('\n');
        PORTD = line.toInt();
      }
     myfile_R.close();   
    }
    // close the file:
    
    
  }
  if (SELval > 900 and Row == 2 and Screen == 6){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(filename);
    for (int i = 0; i <= 3; i++) {
       lcd.print(".");
       delay(50);
      }
    lcd.setCursor(1,1);
    lcd.print("with Effect 1");
    bassfilter_main();
    myfile_R = SD.open("lowpass.txt",FILE_READ);
     if (myfile_R) {
      while (myfile_R.available()) {
        line=myfile_R.readStringUntil('\n');
        PORTD = line.toInt();
      }
     myfile_R.close();   
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
 
}

void Back(){
  if (BACKval == 1 and ((Screen >= 2 and Screen <= 5) or (Screen >=100 and Screen<=103))){
    Menu();
  }
  if (BACKval == 1 and (Screen ==6)){
    PlayBackAudioI();
  }
}
