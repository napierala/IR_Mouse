/*
 * ADC_Buttons.h
 *
 * Created: 2013-06-09 22:11:42
 *  Author: Jedrzej Napierala
 */ 


#ifndef ADC_BUTTONS_H_
#define ADC_BUTTONS_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Define.h"
//Od Odbiornika
#include "../../../receiver/Software/IR_Mouse_Recv/IR_MOUSE/IR_Cmd.h"

class ADC_BUTTONS{
public:
	ADC_BUTTONS(){
		odczyt = 0 ;
	}
	~ADC_BUTTONS(){}
	
	void init();
	
	byte get_przycisk();
		
	//Ostatni Odczyt
	volatile byte odczyt;	
	
};



#endif /* ADC_BUTTONS_H_ */