/*
 * Nadajnik.cpp
 *
 * Created: 2012-12-24 21:09:09
 *  Author: Jedrzej Napierala
 */ 

//AtTiny13

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Define.h"
#include "IR_Nadajnik.h"
#include "ADC_Buttons.h"

IR_NADAJNIK ir_nadajnik ;
ADC_BUTTONS adc_buttons;

ISR(ADC_vect)
{
	adc_buttons.odczyt = ADCH ;
}


int main(void){
	
	ir_nadajnik.init_timer();
	//Uwaga odpala sei()
	adc_buttons.init();
	
    while(1){
		RC5_packet pakiet ;
		//pakiet.cmd = 0 ;
	
		pakiet.sys = SYS_IR_MOUSE;
		pakiet.cmd = adc_buttons.get_przycisk();
										
		ir_nadajnik.send_cmd(&pakiet);
		_delay_ms(89); // 50 bitów "ciszy"
	}		
}