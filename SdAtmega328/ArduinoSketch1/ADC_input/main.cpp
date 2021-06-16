/*
 * main.cpp
 *
 * Created: 6/16/2021 8:04:37 AM
 *  Author: Bavi
 */ 
#include <avr/io.h>
#include <Arduino.h>
#include <util/delay.h>
//#include <stdio.h>
#include "i2c_b.h"
#include "LCD_i2c.h"
#include <SPI.h>
#include <SD.h>
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define FASTADC 1
#ifdef F_CPU
#undef F_CPU
#define F_CPU 8000000L
#endif
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
String s = "";
char s2[]={};
int len;
File myfile,myfile_R;
const int chipselect = 10;
String line;
String f_name =  "avr3.txt";
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

int main(void)
{
	 DDRD = 225;
	 DDRD &=~((1<<PIND0)|(1<<PIND1)|(1<<PIND2)|(1<<PIND3)|(1<<PIND4)) ;
	 /*Serial.begin(9600);
	 while (!Serial){
		 ;
	 }*/
	 #if FASTADC
	 // set prescale to 16
	 sbi(ADCSRA,ADPS2) ;
	 cbi(ADCSRA,ADPS1) ;
	 cbi(ADCSRA,ADPS0) ;
	 #endif
	 if(!SD.begin(chipselect)){
		 //Serial.println("Card failed or not present !");
		 while(1);
	 }
	 
	
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	lcd_msg("Voice Recorder");
	_delay_ms(50);
	Menu();
	/* Replace with your application code */
	while (1)
	{
		
		RECval = PIND & (1<<PIND0); /*1*/
		UPval = PIND & (1<<PIND1);/*2*/
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
void Recording(){
	if (RECval ==1 ){
		myfile = SD.open(f_name,FILE_WRITE);		
		while ( RECval == 1 )
		{
			lcd_cmd(0x01);
			lcd_msg("Recording");
			for (int i = 0; i <= 4; i++){
				lcd_msg(".");
				_delay_ms(50);
			}
			RECval = PIND & (1<<PIND0);
			lcd_cmd(0x01);
			int y1=analogRead(A0);
		
			int mapped = map(y1, 0, 1023, 0, 255);
			s.concat(mapped);

			if (mapped<10) {
				char s2[] = {s[0],' '};
				myfile.write(s2,2);
			}
			else if (mapped<100) {
				char s2[] = {s[0],s[1],' '};
				myfile.write(s2,3);
			}
			else {
				char s2[] = {s[0],s[1],s[2],' '};
				myfile.write(s2,4);
			}
			s="";
		}
	myfile.close();
	lcd_msg("File Saved");
	_delay_ms(1000);
	Menu();
	Row=0;
	Screen=1;
	}
}
		

void Navigate(){
	if (UPval==2)
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
	lcd_msg("Playback audio");
	lcd_cmd(0xC0);
	lcd_msg("Delete Audio");
	Screen = 1;
	Row = 0;
}
void PlayBackAudio(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Audio 1");
	lcd_cmd(0xC0);
	lcd_msg("Audio 2");
	Screen = 2;
	Row = 0;
}
void DeleteAudio(){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Audio 1");
	lcd_cmd(0xC0);
	lcd_msg("Audio 2");
	Screen = 3;
	Row = 0;
}
void PlayClipI(){
	if ((SELval == 8) && (Row == 1) && (Screen == 2)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("No Effect");
		lcd_cmd(0xC0);
		lcd_msg("Effect 1");
		Screen = 4;
		Row =0;
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 2)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("No Effect");
		lcd_cmd(0xC0);
		lcd_msg("Effect 1");
		Screen = 5;
		Row =0;
	}
}
void PlayClipII(){
	if ((SELval == 8) && (Row == 1) && (Screen == 4)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Playing Audio 1");
		myfile_R = SD.open(f_name,FILE_READ);
		if (myfile_R) {
			while (myfile_R.available()) {
				line=myfile_R.readStringUntil(' ');
				PORTD = line.toInt();
				}
			myfile_R.close();
		}
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 4)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Playing Audio 1");
		lcd_cmd(0xC0);
		lcd_msg("with Effect 1");
	}
	if ((SELval == 8) && (Row == 1) && (Screen == 5)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Playing Audio 2");
	}
	if ((SELval == 8) && (Row == 2) && (Screen == 5)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Playing Audio 2");
		lcd_cmd(0xC0);
		lcd_msg("with Effect 1");
	}
}
void DeleteClipI(){
	if ((SELval == 8) && (Row != 0) && (Screen == 3)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Press Select");
		lcd_cmd(0xC0);
		lcd_msg("to delete");
		Screen = 6;
		Row = 0;
	}
}

void DeleteClipII(){
	if ((SELval == 8 ) && (Screen == 6)){
		lcd_cmd(0x01);
		lcd_cmd(0x80);
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
