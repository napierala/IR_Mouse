/*
 * USB.h
 *
 * Created: 2013-04-09 08:29:19
 *  Author: Jedrzej Napierala
 */ 


#ifndef USB_H_
#define USB_H_

#include "../Define.h"

#include <avr/io.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */

//#include "usbconfig.h"		//Config VUSB

//Extern poniewaz biblioteka jest napisana w c
extern "C" {
	#include "usbdrv/usbdrv.h"
}

class USB{
public:
	USB(){}
	
	void init();
	
	//Uwaga funkcja wywolywuje sei();
	void reconnect();
	
	void Poll();
};



#endif /* USB_H_ */