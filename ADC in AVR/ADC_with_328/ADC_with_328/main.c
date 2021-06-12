/*
 * ADC_with_328.c
 *
 * Created: 5/27/2021 9:46:25 PM
 * Author : GL65
 */ 


#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include "LCD.h"

int main(){
	//DDRB = 0xFF;
	Initialize_SD();
	ADCSRA = ADCSRA | (1 << ADEN);
	ADCSRA = ADCSRA | (1 << ADPS2);
	ADMUX  = ADMUX   | (1 << ADLAR);
	ADCSRA = ADCSRA  | (1 << ADIE);
	sei();
	ADCSRA = ADCSRA | (1 << ADSC);
	
	while(1){}
}

ISR(ADC_vect){
	//PORTB = ADCH ;
	char ADCresult[4];
    itoa(ADCH,ADCresult,10);
	Goto_Location(1,1);
	Send_A_String(ADCresult);
	//Send_A_Command(0x01);
	Send_A_String("  ");
	ADCSRA = ADCSRA | (1 << ADSC);
}