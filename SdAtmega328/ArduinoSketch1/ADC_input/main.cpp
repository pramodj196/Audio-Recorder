/*
 * main.cpp
 *
 * Created: 6/16/2021 8:04:37 AM
 *  Author: Bavi
 */ 
#include <avr/io.h>
#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>
//#include <stdio.h>
#include "i2c_b.h"
#include "LCD_i2c.h"
#include <SPI.h>
#include <SD.h>
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define F_CPU 8000000
//int analogPin = PINC0
const int chipselect = 10;
File myfile,myfile_R;
String line;
uint8_t RECval, UPval, DOWNval, SELval, BACKval ;
int Row=0;
int Screen = 1;
void Recording();
void Navigate();
void Menu();
void PlayBackAudio();
void DeleteAudio();
void PlayClipI();
void PlayClipII();
void DeleteClipI();
void DeleteClipII();
void Back();
unsigned int ADC_read(void);

int main(void)
{
	 
	 DDRD = 225;
	 DDRD &=~((1<<PIND5)|(1<<PIND6)|(1<<PIND2)|(1<<PIND3)|(1<<PIND4)) ;
	 Serial.begin(9600);
	 while (!Serial){
		 ;
	 }
	Serial.println("Initializing the SD card...");
	if(!SD.begin(chipselect)){
		//Serial.println("Card failed or not present !");
		
		while(1);
	}
	Serial.println("Card initialized.");
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	lcd_msg("Voice Recorder");
	_delay_ms(50);
	Menu();
	/* Replace with your application code */
	/*ADCSRA = 0x00; //disable adc
	ADMUX  = 0x40;  //select adc input 0, ref:AVCC
	ADCSRA = 0x82; //prescaler:4, single conversion mode
	ADCSRA |= (1<<ADEN);*/
	ADCSRA = ADCSRA | (1 << ADEN);
	ADCSRA = ADCSRA | (1 << ADPS2);
	ADMUX  = ADMUX   | (1 << ADLAR);
	ADCSRA = ADCSRA  | (1 << ADIE);
	sei();
	//ADCSRA = ADCSRA | (1 << ADSC);
	
	while (1)
	{
		
		RECval = PIND & (1<<PIND5); /*32*/
		UPval = PIND & (1<<PIND6);/*64*/
		DOWNval = PIND & (1<<PIND2);//4
		SELval = PIND & (1<<PIND3);//8
		BACKval = PIND & (1<<PIND4); //16
		
		Recording();
		Navigate();
		if ((SELval == 8) && (Screen == 1) && (Row == 1)){
			PlayBackAudio();
		}
		if ((SELval == 8) && (Screen == 1) && (Row == 2)){
			DeleteAudio();
		}
		PlayClipI();
		PlayClipII();
		DeleteClipI();
		DeleteClipII();
		Back();
		
	}
}
ISR(ADC_vect){
	//PORTB = ADCH ;
	char ADCresult[4];
	itoa(ADCH,ADCresult,10);
	int k =  ADCH ;
	myfile.write(ADCresult,4);
	myfile.write('\n');
	//ADCSRA = ADCSRA | (1 << ADSC);
}
void Recording(){
	if (RECval ==32 ){
		 myfile = SD.open("NewAVR05.txt",FILE_WRITE);
		 lcd_cmd(0x01);	
		 lcd_msg("RECORDING");	
		while ( RECval == 32 )
		{
			//lcd_cmd(0x01);
			ADCSRA = ADCSRA | (1 << ADSC);
			
			/*for (int i = 0; i <= 4; i++){
				lcd_msg(".");
				_delay_ms(50);
			}*/
			RECval = PIND & (1<<PIND5);
			//lcd_cmd(0x01);
			//int x = ADC_read();
			//myfile.println(x);
			
		}
	myfile.close();
	lcd_cmd(0x01);
	lcd_msg("File Saved");
	_delay_ms(10);
	Menu();
	Row=0;
	Screen=1;
	}
}
		
/*unsigned int ADC_read(void)
{
	char i;
	unsigned int ADC_temp, ADCH_temp;
	unsigned int ADC_var = 0;
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag active
	ADCSRA|=(1<<ADIF);
	ADC_temp = ADCL;
	int sample = map(ADC_var,0,1023,0,255);
	
	/*for(i=0;i<8;i++)             // do the ADC conversion 8 times for better accuracy
	{
		ADCSRA |= (1<<ADSC);
		while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag active
		ADCSRA|=(1<<ADIF);
		
		ADC_temp = ADCL;         // read out ADCL register
		ADCH_temp = ADCH;        // read out ADCH register
		ADC_temp +=(ADCH_temp << 8);
		ADC_var += ADC_temp;      // accumulate result (8 samples) for later averaging
	}

	ADC_var = ADC_var >> 3;       // average the 8 samples
	int sample = map(ADC_var,0,1023,0,255);
	if(ADC_var > 255) {ADC_var = 255;}
	
	return sample;
}*/

void Navigate(){
	if (UPval==64)
	{
		lcd_cmd(0x80);
		Row=1;
		
	}
	if (DOWNval==4)
	{
		lcd_cmd(0xC0);
		Row=2;
		
	}
}
void Menu(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Playback audio");
	lcd_cmd(0xC0);
	lcd_cmd(0x14);
	lcd_msg("Delete Audio");
	Screen = 1;
	Row = 0;
}
void PlayBackAudio(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 1");
	lcd_cmd(0xC0);
	lcd_cmd(0x14);
	lcd_msg("Audio 2");
	Screen = 2;
	Row = 0;
}
void DeleteAudio(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 1");
	lcd_cmd(0xC0);
	lcd_cmd(0x14);
	lcd_msg("Audio 2");
	Screen = 3;
	Row = 0;
}
void PlayClipI(){
	if ((SELval == 8) && (Row == 1) && (Screen == 2)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("No Effect");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("Effect 1");
		Screen = 4;
		Row =0;
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 2)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("No Effect");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("Effect 1");
		Screen = 5;
		Row =0;
	}
}
void PlayClipII(){
	if ((SELval == 8) && (Row == 1) && (Screen == 4)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Playing Audio 1");
		myfile_R = SD.open("test04.txt",FILE_READ);
		if (myfile_R) {
			while (myfile_R.available()) {
				line=myfile_R.readStringUntil('\n');
				PORTD = line.toInt();
			}
			myfile_R.close();
		}
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 4)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Playing Audio 1");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("with Effect 1");
	}
	if ((SELval == 8) && (Row == 1) && (Screen == 5)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Playing Audio 2");
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 5)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Playing Audio 2");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("with Effect 1");
	}
}
void DeleteClipI(){
	if ((SELval == 8) && (Row != 0) && (Screen == 3)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Press Select");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("to delete");
		Screen = 6;
		Row = 0;
	}
}

void DeleteClipII(){
	if ((SELval == 8 ) && (Screen == 6)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Deleted");
		_delay_ms(1000);
		Menu();
	}
}
void Back(){
	if ((BACKval == 16) && ((Screen == 2) || (Screen == 3))){
		Menu();
	}
	if ((BACKval == 16) && ((Screen == 4) || (Screen == 5))){
		PlayBackAudio();
	}
}
