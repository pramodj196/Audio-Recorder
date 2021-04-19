#include <LiquidCrystal.h>

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int RECORD = 0, UP = 1, DOWN = 2;
int RECval, UPval, DOWNval;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode (RECORD,INPUT);
  pinMode (UP,INPUT);
  pinMode (DOWN,INPUT);
  lcd.print("Voice Recorder");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  RECval = digitalRead(RECORD);
  UPval = digitalRead(UP);
  DOWNval = digitalRead(DOWN);

  
  if (RECval == 1){
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
    delay(1000);
    lcd.clear();
  }
  
  if (UPval == 1){
    lcd.setCursor(0,0);
    lcd.blink();
    UPval = 0;
   }
   
  if (DOWNval == 1){
    lcd.setCursor(0,1);
    lcd.blink();
    DOWNval = 0;
  }
}
