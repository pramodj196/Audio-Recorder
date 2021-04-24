void setup() {
  Serial.begin(9600); 
  pinMode(0,OUTPUT);
}

void loop() {
  int y1=analogRead(A0);
  Serial.println(y1);
  int mapped = map(y1, 0, 1023, 0, 255);
  Serial.println(mapped);
  delay(1/44);
  int myInts[10];
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
}
