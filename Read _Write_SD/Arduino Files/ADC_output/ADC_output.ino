#include<SPI.h>
#include<SD.h>

const int chipSelect = 10;
String line;

void setup() {
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  //Serial.print("Initalizing SD card");
  if (!SD.begin(chipSelect)){
    //Serial.println("Card failed!");
    while(1);
  }
  //Serial.println("Card Initialized.");

  File myfile = SD.open("music09.txt");
  if (myfile){
    while(myfile.available()){
      line=myfile.readStringUntil('\n');
      //Serial.println(line);
      analogWrite(9,line.toInt());
     
      delay(1/44.1);
    }
  myfile.close();
  }
  else{
    Serial.println("Error opening file!");
  }
}

void loop() {
 

}
