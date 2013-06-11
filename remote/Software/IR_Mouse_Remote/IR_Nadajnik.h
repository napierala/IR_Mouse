/*
 * IR_Nadajnik.h
 *
 * Created: 2012-12-25 00:32:04
 * Author: Jedrzej Napierala
 */ 

//ATmega8

#ifndef IR_NADAJNIK_H_
#define IR_NADAJNIK_H_


#define IR_PORT PORTB
#define IR_PIN PB1

#define IR_DDR DDRB


#include <util/delay.h>
#include <avr/interrupt.h>

#include "Define.h"
//Od Odbiornika
#include "../../../receiver/Software/IR_Mouse_Recv/IR_MOUSE/IR_Cmd.h"

class IR_NADAJNIK{
public:
	bool toggle ;
	
	IR_NADAJNIK(){
		toggle = false ;
		//Dioda nadawcza podczerwieni (OC0B)
		Pin_Out(IR_DDR,IR_PIN);
	}
	~IR_NADAJNIK(){}
		

	void init_timer();
	void send_cmd(RC5_packet *packet);
};


#endif /* IR_NADAJNIK_H_ */