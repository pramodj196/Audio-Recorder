#include<SPI.h>
#include<SD.h>

const int chipSelect = 10;
String playTime;
char buf[4];

void setup() {
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  while (!Serial){;}
  Serial.println("Initalizing SD card");
  if (!SD.begin(chipSelect)){
    Serial.println("Card failed!");
    while(1);
  }
  Serial.println("Card Initialized.");

  File myfile = SD.open("done35.txt",FILE_READ);
  
  unsigned int CurrentTime1;
  unsigned int StartTime1;

  if (myfile){
    playTime = myfile.readStringUntil(' ');
    //playTime.toInt();
    Serial.println(playTime.toInt());
    
    StartTime1 = millis();
    
    while(myfile.available()){
      
      myfile.read(buf,3);
      buf[4]={'\0'};
      //Serial.println(buf);
      //myfile1.println(buf);
      analogWrite(9,buf);
      //delayMicroseconds(55);
     

    }
  CurrentTime1 = millis();
  myfile.close();
  File myfile1 = SD.open("datalog1.txt",FILE_WRITE);
  unsigned int ElapsedTime1 = CurrentTime1 - StartTime1;
  myfile1.print("##########");
  myfile1.print(ElapsedTime1);
  
  myfile1.close();
  Serial.println("Accomplished");
  }
  else{
    Serial.println("Error opening file!");
  }
}

void loop() {}
