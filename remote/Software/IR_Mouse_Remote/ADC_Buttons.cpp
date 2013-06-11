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
	if     (odczyt > 241 )	return IR_MOUSE_LEFT;			//naciœniêty S1
	else if(odczyt > 213 )	return IR_MOUSE_DOWN;			//naciœniêty S2
	else if(odczyt > 184 )	return IR_MOUSE_RIGHT;			//naciœniêty S3
	else if(odczyt > 156 )	return IR_MOUSE_SCRL_DOWN;		//naciœniêty S4
	else if(odczyt >  128 ) return IR_MOUSE_SCRL_BUTTON;	//naciœniêty S5
	else if(odczyt >  100 ) return IR_MOUSE_SCRL_UP;		//naciœniêty S6
	else if(odczyt >  71 )	return IR_MOUSE_LEFT_BUTT;		//naciœniêty S7
	else if(odczyt >  43 )	return IR_MOUSE_UP;				//naciœniêty S8
	else if(odczyt >  14 )	return IR_MOUSE_RIGHT_BUTT;		//naciœniêty S9
	else					return IR_MOUSE_NONE;			//¿aden przycisk nie jest naciœniêty
}