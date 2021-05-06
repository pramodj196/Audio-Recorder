#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int RECORD = 0, UP = 1, DOWN = 2, SELECT = 3, BACK = 4;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode (RECORD,INPUT);
  pinMode (UP,INPUT);
  pinMode (DOWN,INPUT);
  pinMode (SELECT,INPUT);
  pinMode (BACK,INPUT);
  lcd.print("Voice Recorder");
  delay(1000);
  Menu();
}

void loop() {
  // put your main code here, to run repeatedly:
  RECval = digitalRead(RECORD);
  UPval = digitalRead(UP);
  DOWNval = digitalRead(DOWN);
  SELval = digitalRead(SELECT);
  BACKval = digitalRead(BACK);
  
  Recording();
  Navigate();
  if (SELval == 1 and Screen == 1 and Row == 1){
    PlayBackAudio();
  }
  if (SELval == 1 and Screen == 1 and Row == 2){
    DeleteAudio();
  }
  PlayClipI();
  PlayClipII();
  DeleteClipI();
  DeleteClipII();
  Back();
}

void Recording(){
    if (RECval == 1){
    lcd.noBlink();
    while (RECval == 1){
      lcd.clear();
      lcd.print("Recording");
      for (int i = 0; i <= 4; i++) {
      lcd.print(".");
      delay(50);
      }
      RECval = digitalRead(RECORD);
      lcd.clear();
    }
    lcd.print("File Saved");
    delay(1000);
    Menu();
    Row = 0;
    Screen = 1;
  }
}

void Navigate(){
  if (UPval == 1){
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
  if (SELval == 1 and Row == 1 and Screen == 2){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("No Effect");
    lcd.setCursor(1,1);
    lcd.print("Effect 1");
    Screen = 4;
    Row =0;
  }
  if (SELval == 1 and Row == 2 and Screen == 2){
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
  if (SELval == 1 and Row == 1 and Screen == 4){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 1");    
  }
  if (SELval == 1 and Row == 2 and Screen == 4){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 1");
    lcd.setCursor(1,1);
    lcd.print("with Effect 1");
  }
  if (SELval == 1 and Row == 1 and Screen == 5){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 2");    
  }
  if (SELval == 1 and Row == 2 and Screen == 5){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Playing Audio 2");
    lcd.setCursor(1,1);
    lcd.print("with Effect 1");
  }
}

void DeleteClipI(){
  if (SELval == 1 and Row != 0 and Screen == 3){
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
  if (SELval == 1 and Screen == 6){
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print("Deleted");
    delay(1000);
    Menu(); 
  } 
}

void Back(){
  if (BACKval == 1 and (Screen == 2 or Screen == 3)){
    Menu();
  }
  if (BACKval == 1 and (Screen == 4 or Screen == 5)){
    PlayBackAudio();
  }
}
