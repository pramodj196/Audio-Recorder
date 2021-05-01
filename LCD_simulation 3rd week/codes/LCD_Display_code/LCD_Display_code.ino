#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
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
  if (SELval == 1 and Screen == 1 and Row == 0){
    Menu();
  }
  PlayBackAudio();
  SpecialFeatures();
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
    lcd.print("Recorded");
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
    lcd.setCursor(1,0);
    lcd.print("PlayBack Audio");
    lcd.setCursor(1,1);
    lcd.print("Special Features");
    Screen = 1;
}

void PlayBackAudio(){
  if (SELval == 1 and Row == 1 and Screen == 1){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Voice Clip 1");
    lcd.setCursor(1,1);
    lcd.print("Voice Clip 2");
    delay(10);
    Screen = 2;
  }
}

void SpecialFeatures(){
  if (SELval == 1 and Row == 2 and Screen == 1){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Effect 1");
    lcd.setCursor(1,1);
    lcd.print("Effect 2");
    Screen = 3;
  }
}

void Back(){
  if (BACKval == 1 and (Screen == 2 or Screen == 3)){
    Menu();
  }
}
