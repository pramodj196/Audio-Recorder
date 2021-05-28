#include<SPI.h>
#include<SD.h>

const int chipSelect = 10;
String line;
char array1[256] = {};
unsigned long currentTime;
void setup() {
 
DDRD = 255;
 
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

  File myfile = SD.open("music303.txt");
  if (myfile){
    unsigned long startTime = millis();
    while(myfile.available()){
    
      line=myfile.readStringUntil(' ');

      
      //PORTD = line.toInt();
      
      
      
      Serial.println(line);
   currentTime = millis();
    }
  
  Serial.println(currentTime - startTime);
  myfile.close();
  
  }
  else{
    Serial.println("Error opening file!");
  }
}

void loop() {
 

}
