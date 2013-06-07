/*
 * USB.cpp
 *
 * Created: 2013-04-09 08:29:30
 *  Author: Jedrzej Napierala
 */ 

#include "USB.h"

void USB::reconnect(){
	usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
	uchar i = 0;
	while(--i)             /* fake USB disconnect for > 250 ms */
		_delay_ms(1);

	usbDeviceConnect();
	//LED_PORT_DDR |= _BV(LED_BIT);   /* make the LED bit an output */
	sei();
}

void USB::init(){
	usbInit();
}

void USB::Poll(){
	usbPoll();
}

