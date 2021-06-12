/*
 * ADC.c
 *
 * Created: 5/27/2021 3:17:26 PM
 * Author : GL65
 */ 
#ifndef LCD
#define LCD

#include <avr/io.h>
#include<util/delay.h>
#include<stdlib.h>

#define dataPort PORTD
#define dataPort_Direction DDRD
#define controlPort PORTB
#define controlPort_Direction DDRB
#define ReadWrite 1
#define Enable 0
#define RegisterSelect 2
#define CellsPerRow 20

void Check_Busy(void);
void Give_Kick(void);
void Send_A_Command(short Command);
void Send_A_Character(short Character);
void Send_A_String(char *String);
void Goto_Location(char x, char y);
void Initialize_SD(void);

char RowsOfFirstColumn[4] = {0 , 64 };
//char RowsOfFirstColumn[4] = {0 , 64 , CellsPerRow , 64 + CellsPerRow };		

void Initialize_SD(void)
{
	//char Position_String[4];

	controlPort_Direction = controlPort_Direction | (1<<ReadWrite) | (1<<Enable) | (1<<RegisterSelect);
	_delay_ms(15);
	
	Send_A_Command(0x01);
	_delay_ms(2);
	
	Send_A_Command(0x38);
	_delay_us(50);
	
	Send_A_Command(0x0e);
	_delay_us(50); 
	
	
}

void Check_Busy(void){
	
	dataPort_Direction = 0x00;
	controlPort = controlPort & ~(1<<ReadWrite | 1<< RegisterSelect);
	while (dataPort > 0x80) { Give_Kick();}
	dataPort_Direction = 0xFF;
	 
}

void Give_Kick(void){
	controlPort = controlPort | (1<<Enable);
	asm volatile ("nop");
	asm volatile ("nop");
	controlPort = controlPort & ~(1<<Enable);
}

void Send_A_Command(short command){
	Check_Busy();
	dataPort = command;
	controlPort = controlPort & ~(1<<ReadWrite) ;
	controlPort = controlPort & (1<<RegisterSelect);
	Give_Kick();
	dataPort = 0x00;
}

void Send_A_Character(short Character){
	Check_Busy();
	dataPort = Character;
	controlPort = controlPort & ~(1<<ReadWrite);
	controlPort = controlPort | (1<<RegisterSelect);
	Give_Kick();
	dataPort = 0x00;
}

void Send_A_String(char *String){
	while (*String > 0){Send_A_Character(*String++);}	
}

void Goto_Location(char x ,char y){
	Send_A_Command( 0x80 + RowsOfFirstColumn[x-1] + ( y - 1 ));
}


#endif