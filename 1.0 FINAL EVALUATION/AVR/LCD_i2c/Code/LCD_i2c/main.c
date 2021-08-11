/*
 * LCD_i2c.c
 *
 * Created: 8/10/2021 1:56:35 PM
 * Author : Bavi
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//#include <stdio.h>
#include "i2c.h"
#include "lcd_i2c.h"
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


int main(void)
{
	DDRD &=~((1<<PIND0)|(1<<PIND1)|(1<<PIND2)|(1<<PIND3)|(1<<PIND4)) ;
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
			PlayBackAudioI();
			filenumber = 1;
		}
		if ((SELval == 8) && (Screen == 1) && (Row == 2)){
			DeleteAudioI();
			filenumber = 1;
		}
		if (SELval == 8 && Screen >=2 && Screen<=5 && Row == 1){
			NPlayClip();
		}
		NEXT();
		PlayClipII();
		DeleteClipI();
		DeleteClipII();
		Back();
		
	}
}

void NEXT(){
	if (SELval ==8 && Screen == 2 && Row == 2){
		PlayBackAudioII();
		filenumber = 2;
	}
	if (SELval == 8  && Screen == 3 && Row == 2){
		PlayBackAudioIII();
		filenumber = 3;
	}
	if (SELval ==8 && Screen == 4 && Row == 2){
		PlayBackAudioIV();
		filenumber = 4;
	}
	if (SELval == 8 && Screen == 100 && Row == 2){
		DeleteAudioII();
		filenumber = 2;
	}
	if (SELval ==8 && Screen == 101 && Row == 2){
		DeleteAudioIII();
		filenumber = 3;
	}
	if (SELval ==8 && Screen == 102 && Row == 2){
		DeleteAudioIV();
		filenumber = 4;
	}
	if (SELval == 8 && Screen == 6 && Row == 2){
		BassClip();
	}
	if (SELval ==8 && Screen == 7 && Row == 2){
		TrebleClip();
	}
}
void Recording(){
	if (RECval ==1){
		
	while ( RECval == 1 )
	{
		lcd_cmd(0x01);
		lcd_msg("Recording...");
		RECval = PIND & (1<<PIND0);
		lcd_cmd(0x01);
	}
	lcd_msg("File Saved");
	filenumber= filenumber+1;
	_delay_ms(1000);
	Menu();
	Row=0;
	Screen=1;
	}
}

void Navigate(){
	
	if (UPval==2)
	{
		lcd_cmd(0x0F);
		lcd_cmd(0x80);
		Row=1;
		
	}
	if (DOWNval==4)
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
	lcd_cmd(0x0C);
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
	
	if ((SELval == 8) && (Row == 1) && (Screen == 6)){
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
		lcd_cmd(0x0C);
		_delay_ms(2000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_cmd(0x14);
		lcd_msg("end");
		lcd_cmd(0x0C);
		_delay_ms(1000);
		Menu();
	}
	if ((SELval == 8) && (Row == 1) && (Screen == 7)){
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
	if ((SELval == 8) && (Row == 1) && (Screen == 8)){
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
	if ((SELval == 8) && (Row != 0) && (Screen >=100 && Screen <=103)){
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
	if ((SELval == 8 ) && (Screen == 104) && (Row ==1)){
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
		lcd_cmd(0x0C);
		_delay_ms(1000);
		Menu();
	}
}
void Back(){
	if ((BACKval == 16) && ((Screen >= 2 && Screen <=5) || (Screen >= 100 && Screen <=103))){
		Menu();
	}
	if ((BACKval == 16) && (Screen >= 6) && (Screen <=8)){
		PlayBackAudioI();
	}
}

