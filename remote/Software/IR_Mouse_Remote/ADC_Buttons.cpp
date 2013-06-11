/*
 * ADC_Buttons.cpp
 *
 * Created: 2013-06-09 22:11:56
 *  Author: Jedrzej Napierala
 */ 

#include "ADC_Buttons.h"

void ADC_BUTTONS::init(){
	
	//Poprawka do lewej (Vcc jako reference bo REFS0 = 0), wejsie to ADC2(PB4)
	ADMUX = (1<<ADLAR) | (1<<MUX1);
	//Wlaczamy ADC,start pierwszego pomiaru, wlaczamy przerwanie od adc, auto trigger ,ustawiamy prescaler na 16
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE) | (1<<ADPS2);
	//Free Running Mode bo ADCSRB = 0 
	
	//Wlaczamy przerwania
	sei(); 
}

byte ADC_BUTTONS::get_przycisk(){
	if     (odczyt > 241 )	return IR_MOUSE_LEFT;			//naci�ni�ty S1
	else if(odczyt > 213 )	return IR_MOUSE_DOWN;			//naci�ni�ty S2
	else if(odczyt > 184 )	return IR_MOUSE_RIGHT;			//naci�ni�ty S3
	else if(odczyt > 156 )	return IR_MOUSE_SCRL_DOWN;		//naci�ni�ty S4
	else if(odczyt >  128 ) return IR_MOUSE_SCRL_BUTTON;	//naci�ni�ty S5
	else if(odczyt >  100 ) return IR_MOUSE_SCRL_UP;		//naci�ni�ty S6
	else if(odczyt >  71 )	return IR_MOUSE_LEFT_BUTT;		//naci�ni�ty S7
	else if(odczyt >  43 )	return IR_MOUSE_UP;				//naci�ni�ty S8
	else if(odczyt >  14 )	return IR_MOUSE_RIGHT_BUTT;		//naci�ni�ty S9
	else					return IR_MOUSE_NONE;			//�aden przycisk nie jest naci�ni�ty
}