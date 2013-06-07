/*
 * IR_Odbiornik.h
 *
 * Created: 2012-12-25 00:32:04
 * Author: Jedrzej Napierala
 */ 


#ifndef IR_ODBIORNIK_H_
#define IR_ODBIORNIK_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../Define.h"
#include "IR_Cmd.h"

#define TSOP_DDR DDRD
#define TSOP_PORT PORTD
#define TSOP_PIN PD3
#define TSOP_PINPORT PIND

// Odbiornik podczerwieni TSOP  przylaczona do portu  PB4
#define RC5_IN   (TSOP_PINPORT & (1<<TSOP_PIN))

class IR_ODBIORNIK{
 
public:
	IR_ODBIORNIK(){
		//Odbiornik jako wejscie
		Pin_In(TSOP_DDR,TSOP_PIN);
		pakiet.status = false ;
	}
	~IR_ODBIORNIK(){}
		
	RC5_packet pakiet ;

	volatile byte timerL;
	volatile byte timerH;

	void init_timer();
	void detect();

	void overflow_interrupt();
};


#endif /* IR_ODBIORNIK_H_ */