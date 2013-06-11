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

#define CZULOSC_MOUSE 5
#define CZULOSC_SCRL 2

class IR_MOUSE{
public:

	report_t		reportBuffer;
	byte			idleRate;   /* repeat rate for keyboards, never used for mice */
	byte			last_toggle ;
	
	IR_MOUSE(){
		//Cos innego niz 0 lub 1 na poczatek
		last_toggle = 2 ;
		ostatni_klawisz = IR_MOUSE_NONE;
		ilosc_powtorzen_klawisza = 0 ;
	}
	~IR_MOUSE(){}
	
	void stworz_raport();
	
	void pusty_raport();
	
	//Przyspieszanie ruchu gdy jest caly czas nacisniete
	byte ostatni_klawisz;
	byte ilosc_powtorzen_klawisza;
	byte getMnoznikPowtorzen(byte aktualny_klawisz);
};




#endif /* IR_MOUSE_H_ */