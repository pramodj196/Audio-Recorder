void setup() {
  // put your setup code here, to run once:
  DDRD = B11111111;
}

void loop() {
  int x=analogRead(A0);
  int sample=map(x,0,1023,0,255);
  PORTD=sample;
  
  // put your main code here, to run repeatedly:
  /*PORTD =255;
  delay(1);
  PORTD =0;
  delay(1);
  */
  //for(int i = -255;i<=255;i++){
    //PORTD = abs(i);
  //}
}
