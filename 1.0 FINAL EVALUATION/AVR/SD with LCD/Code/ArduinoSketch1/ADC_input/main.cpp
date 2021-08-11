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
#define F_CPU 16000000
//int analogPin = PINC0
const int chipselect = 10;
File myfile,myfile_R;
String line;
uint8_t RECval, UPval, DOWNval, SELval, BACKval ;
int Row=0;
int Screen = 1;
int filenumber = 1;
void Recording();
void Navigate();
void Menu();
void PlayBackAudioI();
void DeleteAudioI();
void PlayBackAudioII();
void DeleteAudioII();
void PlayBackAudioIII();
void DeleteAudioIII();
void PlayBackAudioIV();
void DeleteAudioIV();
void NPlayClip();
void BassClip();
void TrebleClip();
void PlayClipII();
void DeleteClipI();
void DeleteClipII();
void Back();
void NEXT();

unsigned int ADC_read(void);

int ReadAnalogPins(uint8_t pin ){
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);
	//single conversion mode
	cli();
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADCH;
}

int main(void)
{
	 
	 DDRD = 255;
	 DDRB &=~((1<<PINB0)|(1<<PINB1));
	if(!SD.begin(chipselect)){
		while(1);
	}
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	lcd_msg("Voice Recorder");
	_delay_ms(50);
	Menu();
	ADCSRA = ADCSRA | (1 << ADEN);
	ADCSRA = ADCSRA | (1 << ADPS2);
	ADMUX  = ADMUX   | (1 << ADLAR);
	ADCSRA = ADCSRA  | (1 << ADIE);
	
	while (1)
	{
		
		RECval = ReadAnalogPins(0b00000001);
		SELval = ReadAnalogPins(0b00000010);
		BACKval = ReadAnalogPins(0b00000101);
		UPval = PINB & (1<<PINB0);/*1*/
		DOWNval = PINB & (1<<PINB1);//2
		Recording();
		Navigate();
		if ((SELval >1 ) && (Screen == 1) && (Row == 1)){
			PlayBackAudioI();
			filenumber = 1;
		}
		if ((SELval >1 ) && (Screen == 1) && (Row == 2)){
			DeleteAudioI();
			filenumber = 1;
		}
		if (SELval >1 && Screen >=2 && Screen<=5 && Row == 1){
			NPlayClip();
		}
		NEXT();
		PlayClipII();
		DeleteClipI();
		DeleteClipII();
		Back();
		
	}
}
ISR(ADC_vect){
	char ADCresult[4];
	itoa(ADCH,ADCresult,10);
	int k =  ADCH ;
	myfile.write(ADCresult,4);
	myfile.write('\n');
}
void NEXT(){
	if (SELval >1 && Screen == 2 && Row == 2){
		PlayBackAudioII();
		filenumber = 2;
	}
	if (SELval >1  && Screen == 3 && Row == 2){
		PlayBackAudioIII();
		filenumber = 3;
	}
	if (SELval >1 && Screen == 4 && Row == 2){
		PlayBackAudioIV();
		filenumber = 4;
	}
	if (SELval >1 && Screen == 100 && Row == 2){
		DeleteAudioII();
		filenumber = 2;
	}
	if (SELval >1 && Screen == 101 && Row == 2){
		DeleteAudioIII();
		filenumber = 3;
	}
	if (SELval >1 && Screen == 102 && Row == 2){
		DeleteAudioIV();
		filenumber = 4;
	}
	if (SELval >1 && Screen == 6 && Row == 2){
		BassClip();
	}
	if (SELval >1 && Screen == 7 && Row == 2){
		TrebleClip();
	}
}

void Recording(){
	
	
	if (RECval > 1  ){
		if (filenumber==1){
			 myfile = SD.open("Audio 1.txt",FILE_WRITE);
		}
		if (filenumber==2){
			myfile = SD.open("Audio 1.txt",FILE_WRITE);
		}
		if (filenumber==3){
			myfile = SD.open("Audio 1.txt",FILE_WRITE);
		}
		if (filenumber==4){
			myfile = SD.open("Audio 1.txt",FILE_WRITE);
		}
		
		 lcd_cmd(0x01);	
		 lcd_msg("RECORDING...");	
		while ( RECval> 1 )
		{
			ADMUX = (ADMUX & 0xF0) | (0b00000000 & 0x0F);
			sei();
			ADCSRA = ADCSRA | (1 << ADSC);
			while( ADCSRA & (1<<ADSC) );
			
			RECval = ReadAnalogPins(0b00000001);
			
		}
	myfile.close();
	lcd_cmd(0x01);
	lcd_msg("File Saved");
	cli();
	_delay_ms(50);
	Menu();
	Row=0;
	Screen=1;
	}
}
void Navigate(){
	if (UPval==1)
	{
		lcd_cmd(0x0F);
		lcd_cmd(0x80);
		Row=1;
		
	}
	if (DOWNval==2)
	{
		lcd_cmd(0x0F);
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
void PlayBackAudioI(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 1");
	lcd_cmd(0x0C);
	Screen = 2;
	Row = 0;
}
void PlayBackAudioII(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 2");
	lcd_cmd(0x0C);
	Screen = 3;
	Row = 0;
}
void PlayBackAudioIII(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 3");
	lcd_cmd(0x0C);
	Screen = 4;
	Row = 0;
}
void PlayBackAudioIV(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 4");
	lcd_cmd(0x0C);
	Screen = 5;
	Row = 0;
}

void DeleteAudioI(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 1");
	lcd_cmd(0x0C);
	Screen = 100;
	Row = 0;
}
void DeleteAudioII(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 2");
	lcd_cmd(0x0C);
	Screen = 101;
	Row = 0;
}
void DeleteAudioIII(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 3");
	lcd_cmd(0x0C);
	Screen = 102;
	Row = 0;
}
void DeleteAudioIV(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Audio 4");
	lcd_cmd(0x0C);
	Screen = 103;
	Row = 0;
}
void NPlayClip(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("No Effect");
	lcd_cmd(0x0C);
	Screen = 6;
	Row =0;
}
void BassClip(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Bass");
	lcd_cmd(0x0C);
	Screen = 7;
	Row =0;
}
void TrebleClip(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x14);
	lcd_msg("Treble");
	lcd_cmd(0x0C);
	Screen = 8;
	Row =0;
}
void PlayClipII(){
	if ((SELval>1) && (Row == 1) && (Screen == 6)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Playing");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		if (filenumber==1){
			lcd_msg("Audio 1");
		}
		if (filenumber==2){
			lcd_msg("Audio 2");
		}
		if (filenumber==3){
			lcd_msg("Audio 3");
		}
		if (filenumber==4){
			lcd_msg("Audio 4");
		}
		
		if (filenumber==1){
			myfile_R = SD.open("Audio 1.txt",FILE_WRITE);
		}
		if (filenumber==2){
			myfile_R = SD.open("Audio 2.txt",FILE_WRITE);
		}
		if (filenumber==3){
			myfile_R= SD.open("Audio 3.txt",FILE_WRITE);
		}
		if (filenumber==4){
			myfile_R= SD.open("Audio 4.txt",FILE_WRITE);
		}
		if (myfile_R) {
			while (myfile_R.available()) {
				line=myfile_R.readStringUntil(' ');
				PORTD = line.toInt();
			}
			myfile_R.close();
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_cmd(0x14);
			lcd_msg("end");
			lcd_cmd(0x0C);
			_delay_ms(1000);
			Menu();
		}
	}
	if ((SELval >1) && (Row == 1) && (Screen == 7)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		if (filenumber==1){
			lcd_msg("Audio 1");
		}
		if (filenumber==2){
			lcd_msg("Audio 2");
		}
		if (filenumber==3){
			lcd_msg("Audio 3");
		}
		if (filenumber==4){
			lcd_msg("Audio 4");
		}
		lcd_cmd(0xC0);
		lcd_msg("with Bass Effect");
		lcd_cmd(0x0C);
		_delay_ms(2000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("end");
		lcd_cmd(0x0C);
		
	}
	if ((SELval >1) && (Row == 1) && (Screen == 8)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		if (filenumber==1){
			lcd_msg("Audio 1");
		}
		if (filenumber==2){
			lcd_msg("Audio 2");
		}
		if (filenumber==3){
			lcd_msg("Audio 3");
		}
		if (filenumber==4){
			lcd_msg("Audio 4");
		}
		lcd_cmd(0xC0);
		lcd_msg("with Treble Effect");
		lcd_cmd(0x0C);
		_delay_ms(2000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("end");
		lcd_cmd(0x0C);
	}
}
void DeleteClipI(){
	if ((SELval >1) && (Row != 0) && (Screen >=100 && Screen <=103)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Confirm");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		lcd_msg("Cancel");
		lcd_cmd(0x0C);
		Screen = 104;
		Row = 0;
	}
}

void DeleteClipII(){
	if ((SELval >1 ) && (Screen == 104) && (Row ==1)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("Deleted");
		lcd_cmd(0xC0);
		lcd_cmd(0x14);
		if (filenumber==1){
			lcd_msg("Audio 1");
		}
		if (filenumber==2){
			lcd_msg("Audio 2");
		}
		if (filenumber==3){
			lcd_msg("Audio 3");
		}
		if (filenumber==4){
			lcd_msg("Audio 4");
		}
		if (filenumber==1){
			SD.remove("Audio 1.txt");
		}
		if (filenumber==2){
			SD.remove("Audio 2.txt");
		}
		if (filenumber==3){
			SD.remove("Audio 3.txt");
		}
		if (filenumber==4){
			SD.remove("Audio 4.txt");
		}
		lcd_cmd(0x0C);
		_delay_ms(1000);
		Menu();
	}
}
void Back(){
	if (BACKval > 1) {
		Menu();
	}
}
