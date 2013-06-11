/*
 * CNC_firmware.cpp
 *
 * Created: 2013-04-09 08:28:30
 *  Author: Jedrzej Napierala
 */ 

#include <avr/io.h>
#include "Define.h"


#include "USB/USB.h"
#include "IR_MOUSE/IR_MOUSE.h"
#include "IR_MOUSE/IR_Odbiornik.h"

USB usb;
IR_MOUSE ir_mouse;
IR_ODBIORNIK ir_odbiornik;

//Przerwanie Timer0 Overflow
ISR(TIMER0_OVF_vect)
{
	sei();
	ir_odbiornik.overflow_interrupt();
}

int __attribute__((noreturn)) main(void)
{
	ir_odbiornik.init_timer();
	
	//Podlaczamy sie do Host
	usb.init();
	usb.reconnect();
	
    while(1){
		//Obslugujemy USB
		usb.Poll(); 
		//Sprawdzamy czy jest prosba o raport
		if(usbInterruptIsReady()){
			/* called after every poll of the interrupt endpoint */
			//ir_mouse.advanceCircleByFixedAngle();
			//ir_mouse.TestMouseMove();
			usbSetInterrupt((void *)&ir_mouse.reportBuffer, sizeof(ir_mouse.reportBuffer));
		}
		
		//Sprawdzamy Odbiornik IR
		ir_odbiornik.detect();
		ir_mouse.stworz_raport();
    }
}