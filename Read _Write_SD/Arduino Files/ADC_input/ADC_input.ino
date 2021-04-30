#include<SPI.h>
#include<SD.h>

const int chipselect = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial){
    ;
 }
  //Serial.println("Initializing the SD card...");
  if(!SD.begin(chipselect)){
    Serial.println("Card failed or not present !");
    while(1);
  }
 // Serial.println("Card initialized.");
  
}

void loop() {
  
  int y1=analogRead(A0);
  int mapped = map(y1, 0, 1023, 0, 255);

  File myfile = SD.open("music09.txt",FILE_WRITE);
  if (myfile){
    myfile.println(mapped);
    myfile.close();
    Serial.println(mapped);
    delay(1/44.1);
  }
  else{
    Serial.println("Error opening the file!");
  }
}
