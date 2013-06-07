/*
 * IR_MOUSE.h
 *
 * Created: 2013-06-06 00:20:28
 *  Author: Jedrzej Napierala
 */ 


#ifndef IR_MOUSE_H_
#define IR_MOUSE_H_

#include "../Define.h"
#include <avr/io.h>

#include <avr/pgmspace.h>   /* required by usbdrv.h */

#include "IR_Odbiornik.h"

extern IR_ODBIORNIK ir_odbiornik;

class IR_MOUSE{
public:

	report_t		reportBuffer;
	int				sinus;
	int				cosinus;
	byte   idleRate;   /* repeat rate for keyboards, never used for mice */
	byte last_toggle ;
	
	IR_MOUSE(){
		sinus = 7 << 6 ;
		cosinus = 0 ;
		//Cos innego niz 0 lub 1 na poczatek
		last_toggle = 2 ;
	}
	~IR_MOUSE(){}
		
	void advanceCircleByFixedAngle();	
	void TestMouseMove();
	
	void stworz_raport();
	
};




#endif /* IR_MOUSE_H_ */