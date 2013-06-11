/*
 * IR_Nadajnik.cpp
 *
 * Created: 2012-12-25 00:32:15
 *  Author: Jedrzej Napierala
 */ 

#include "IR_Nadajnik.h"

void IR_NADAJNIK::init_timer(){
	 // Timer2, CTC mode, no prescaling ,Toggle OC2 on compare match
	 // TCCR2= (1<<WGM21)|(1<<COM20)|(1<<CS20);
	 // OCR0A - 36 KHz ( tak naprawde 35.714 )
	 OCR0A = 13 ; 
	 //OCR2 = 13;
}


/*

TCCR0A =  0;
TCCR0B = (1<<CS00) | (1<<WGM02);

TCNT0 = 0; //inicjalizacja wartosci timera

TIMSK0 = (1<<OCIE0A); // wlacza przerwanie Match A
*/

inline void IR_1(){
	// Dioda nadawcza  nie swieci
	//Clear OCRB on compare match
	TCCR0A = (1<<COM0B1);
	TCCR0B = (1<<FOC0B)|(1<<CS00);
	_delay_ms(0.89); // czas trwania polowy bitu
	
	// swieci
	//Toggle OCRB on compare match
	//CTC Mode
	TCCR0A = (1<<COM0B0)|(1<<WGM01);
	//Uaktywniamy wave na B oraz zegar bez prescalera
	TCCR0B = (1<<FOC0B)|(1<<CS00);
	_delay_ms(0.89);
}

inline void IR_0(){
	// swieci
	//Toggle OCRB on compare match
	//CTC Mode
	TCCR0A = (1<<COM0B0)|(1<<WGM01);
	//Uaktywniamy wave na B oraz zegar bez prescalera
	TCCR0B = (1<<FOC0B)|(1<<CS00);
	_delay_ms(0.89);
	
	// Dioda nadawcza  nie swieci
	//Clear OCRB on compare match
	TCCR0A = (1<<COM0B1);
	TCCR0B = (1<<FOC0B)|(1<<CS00);
	_delay_ms(0.89); // czas trwania polowy bitu	
}

//---------------------------------------------------------------
// Funkcja wysyla komende  RC5
//---------------------------------------------------------------
void IR_NADAJNIK::send_cmd(RC5_packet *packet){
	
	toggle = !toggle;
	
	//START
	IR_1();
	IR_1();
	
	//TOOGLE
	if(toggle & 1) IR_1(); else IR_0();
	
	//SYS
	for(byte i = 16 ; i >= 1; i >>= 1){
		if(packet->sys & i) IR_1(); else IR_0();
	}
	
	//CMD
	for(byte i = 32 ; i >= 1; i >>= 1){
		if(packet->cmd & i) IR_1(); else IR_0();
	}			
	
	// wylaczamy LED i Timer
	TCCR0A = (1<<COM0A1);
	TCCR0B = (1<<FOC0A)|(1<<CS00);
	TCCR0A = 0 ;
	TCCR0B = 0 ;
	
}