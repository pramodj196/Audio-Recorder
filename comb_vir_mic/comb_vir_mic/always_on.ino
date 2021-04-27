#define MIC A0
int sample=0;
void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(1,OUTPUT);
 

}

void loop() {
  sample=analogRead(MIC);
  Serial.println(sample);
  if(sample>1){
    digitalWrite(11,HIGH);
  }
  else{digitalWrite(11,LOW);}
  int mapped = map(sample, 0, 1023, 0, 255);
  Serial.println(mapped);
  delay(1/44);
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
 


}
