#define PLAY_E 3 // pin 3 is used for playback-edge trigger
#define REC 2 // pin 2 is used for recording
#define FT 5 // pin 5 is used for feed through
// and will NOT record
#define recordTime 5000 // recording time 5 seconds can be extended upto 10 seconds
#define playTime 8000 // playback time 8 seconds

void setup() 
{
 pinMode(PLAY_E,OUTPUT);// set the PLAY_e pin as output
 pinMode(REC,OUTPUT);// set the REC pin as output
 pinMode(FT,OUTPUT);// set the FT pin as output  
 Serial.begin(9600);// set up Serial monitor   
}
void loop() {
   while (Serial.available() > 0) {
         char inChar = (char)Serial.read();
           if(inChar =='p' || inChar =='P'){
           digitalWrite(PLAY_E, HIGH);
           delay(50);
           digitalWrite(PLAY_E, LOW);  
             Serial.println("Started playback");  
           delay(playTime);
             Serial.println("Ended playback");
           break; 
           }       
           else if(inChar =='r' || inChar =='R'){
             digitalWrite(REC, HIGH);
             Serial.println("Started recording");
             delay(recordTime);
             digitalWrite(REC, LOW);
             Serial.println("Stopped recording");              
           } 
                         
     Serial.println("###Serial Monitor Exited");      
   }
Serial.println("### Enter r to record, p to play");
 delay(500);
}
