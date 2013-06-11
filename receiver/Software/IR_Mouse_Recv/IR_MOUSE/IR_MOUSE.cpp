/*
 * IR_MOUSE.cpp
 *
 * Created: 2013-06-06 00:20:37
 *  Author: Jedrzej Napierala
 */ 

#include "IR_MOUSE.h"

void IR_MOUSE::pusty_raport(){
	reportBuffer.dx = 0 ;
	reportBuffer.dy = 0 ;
	reportBuffer.dWheel = 0 ;
	reportBuffer.buttonMask = 0 ;
}
void IR_MOUSE::stworz_raport(){
	//Jak jest odebrany pakiet
	if(ir_odbiornik.pakiet.status){
		
		//Jezeli to do mnie
		if(ir_odbiornik.pakiet.sys == SYS_IR_MOUSE){
			//Jak nacisniety jeszcze raz
			if(ir_odbiornik.pakiet.toggle != last_toggle){
			
			}
			//Nadal ten sam nacisniety
			else{
			
			}
			//reportBuffer.dx = ir_odbiornik.pakiet.cmd * 100 ;
			//if(ir_odbiornik.pakiet.cmd == IR_MOUSE_NONE){
			//	reportBuffer.dx = -5 ;
			//}
			byte mnoznik = getMnoznikPowtorzen(ir_odbiornik.pakiet.cmd);
			
			if(ir_odbiornik.pakiet.cmd == IR_MOUSE_NONE){
				pusty_raport();	
			}				
			//Na podstawie tego co dostaniemy z odbiornika do tworzymy raport
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_LEFT){
				reportBuffer.dx = -(CZULOSC_MOUSE * mnoznik) ;
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_RIGHT){
				reportBuffer.dx = (CZULOSC_MOUSE * mnoznik) ;
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_UP){
				reportBuffer.dy = -(CZULOSC_MOUSE * mnoznik) ;
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_DOWN){
				reportBuffer.dy = (CZULOSC_MOUSE * mnoznik) ;
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_LEFT_BUTT){
				reportBuffer.buttonMask = (1<<Left_Button);
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_RIGHT_BUTT){
				reportBuffer.buttonMask = (1<<Right_Button);
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_SCRL_BUTTON){
				reportBuffer.buttonMask = (1<<Middle_Button);
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_SCRL_UP){
				reportBuffer.dWheel = (CZULOSC_SCRL * mnoznik) ;
			}
			else if(ir_odbiornik.pakiet.cmd == IR_MOUSE_SCRL_DOWN){
				reportBuffer.dWheel = -(CZULOSC_SCRL * mnoznik) ;
			}
		}		
		//Zapisujemy Toggle
		last_toggle = ir_odbiornik.pakiet.toggle; 
	} 
	else{
		pusty_raport();	
	}
}


byte IR_MOUSE::getMnoznikPowtorzen(byte aktualny_klawisz){
byte result ;
	//Powtorzenie
	if(aktualny_klawisz == ostatni_klawisz){
		ilosc_powtorzen_klawisza ++ ;
		//Jak sie przekrecil
		if(!ilosc_powtorzen_klawisza){
			ilosc_powtorzen_klawisza = 254 ;
		}
		if(ilosc_powtorzen_klawisza > 100){
			result = 2 ;
		}
		if(ilosc_powtorzen_klawisza > 250){
			result = 10 ;
		}
		
	}
	//Cos innego
	else{
		ilosc_powtorzen_klawisza = 0 ;	
		result = 1 ;
	}
	ostatni_klawisz = aktualny_klawisz;
	
	return result;
}