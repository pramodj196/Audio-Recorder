#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int RECORD = 2, UP = 3, DOWN = 4, SELECT = 5, BACK = 6;
int RECval, UPval, DOWNval, SELval, BACKval;
int Row = 0, Screen = 1;
const int microphonePin = 0;
const int threshold=1;

void setup() {
  Serial.begin(9600); 
  pinMode(1,OUTPUT);
  lcd.begin(16,2);
  pinMode (RECORD,INPUT);
  pinMode (UP,INPUT);
  pinMode (DOWN,INPUT);
  pinMode (SELECT,INPUT);
  pinMode (BACK,INPUT);
  lcd.print("Voice Recorder");
}

void loop() {
  int y1=analogRead(microphonePin);
  Serial.println(y1);
  int mapped = map(y1, 0, 1023, 0, 255);
  Serial.println(mapped);
  delay(1000);
  //int myInts[10];
  /*Serial.print("10 bit: ");
  for (int i = 0; i < 10; i = i + 1) {
    int remainder;
    remainder=y1%2;
    y1=y1/2;
    myInts[9-i]=remainder;
  }
  for (int i = 0; i < 10; i = i + 1) {
    Serial.print(myInts[i]);
  }
  Serial.println();*/

  Serial.print("8 bit: ");
  int myInts2[8];
  for (int i = 0; i < 8; i = i + 1) {
    int remainder2;
    remainder2=mapped%2;
    mapped/=2;
    myInts2[7-i]=remainder2;
  }
  for (int i = 0; i < 8; i = i + 1) {
    Serial.print(myInts2[i]);
  }
  Serial.println(); 
  //digitalWrite(ledPin,LOW);

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
