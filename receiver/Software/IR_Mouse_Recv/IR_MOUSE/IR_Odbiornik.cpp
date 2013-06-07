/*
 * IR_Odbiornik.cpp
 *
 * Created: 2012-12-25 00:32:15
 *  Author: Jedrzej Napierala
 */ 

#include "IR_Odbiornik.h"


void IR_ODBIORNIK::overflow_interrupt(){
	volatile static byte inttemp;
	volatile static byte fix16mhz;
	
	//Fix dla 16 MHz(kod byl przewidziany na 8MHz wiec dzielimy na 2(co drugie przerwanie)
	fix16mhz = !fix16mhz ;
	if(fix16mhz){
		// zmienna timerL zwieksza sie co 32us
		timerL++;

		// zmienna timerH  zwieksza sie co 8.192ms (32us*256)
		inttemp++;
		if(!inttemp ) timerH++;
	}
}	

void IR_ODBIORNIK::init_timer(){
	
	TCCR0 = (1<<CS00);  // wlacza Timer0 no prescaler
	TIMSK = (1<<TOIE0); // wlacza przerwanie "Timer0 Overflow"

	sei();
}

//---------------------------------------------------------------
// Funkcja wykrywa i dekoduje komend? pilota RC5
//---------------------------------------------------------------
void IR_ODBIORNIK::detect()
{
	byte temp;
	byte ref1;
	byte ref2;

	timerH  = 0;
	timerL  = 0;
	
	pakiet.status = true ;
	
	// Czeka na okres ciszy na linii wej?cia uC trwaj?cy  3.5ms
	// Je?li nie wykryje takiego okresu ciszy w ci?gu 131ms,
	// to ko?czy dzia?anie funkcji z b??dem
	while( timerL<110){
		
		if(timerH>=2){ //Bylo 16
			pakiet.status = false ; 
			return ;
		}

		if(!RC5_IN) timerL = 0;
	}

	// Czeka na  pierwszy bit startowy.
	// Je?li nie wykryje bitu startowego w ci?gu 131ms,
	// to ko?czy dzia?anie funkcji z b??dem
	while(RC5_IN){
		if(timerH>=2){ //Bylo 16
			pakiet.status = false ;
			return ;
		}
	}		

	// Pomiar czasu trwani niskiego poziom sygan?u
	// w pierwszym bicie startowym.
	// Je?li nie wykryje rosn?cego zbocza sygna?u w ci?gu
	// 1ms, to ko?czy dzia?anie funkcji z b??dem
	timerL = 0;
	while(!RC5_IN){
		if(timerL>34){ 
			pakiet.status = false ;
			return ;
		}			
	}
	//
	temp = timerL;
	timerL = 0;

	// ref1 - oblicza  3/4 czasu trwania bitu
	ref1 =temp+(temp>>1);

	// ref2 - oblicza 5/4 czasu trwania bitu
	ref2 =(temp<<1)+(temp>>1);

	
	// Oczekuje na zbocze opadaj?ce sygna?u w ?rodku drugiego
	// bitu startowego.
	// Je?li nie wykryje zbocza w ci?gu 3/4 czasu trwania
	// bitu, to ko?czy dzia?anie funkcji z b??dem
	while(RC5_IN){
		if(timerL > ref1){ 
			pakiet.status = false ;
			return ;
		}			
	}	

	// W momencie wykrycia zbocza sygna?u, synchronizuje
	// zmien? timerL dla próbkowania  bitu toggle
	timerL = 0;
	//TOOGLE
	// Czeka 3/4 czasu trwania bitu od momentu wykrycia
	// zbocza sygna?u w po?owie poprzedniego bitu
	while(timerL < ref1) {};
	// Próbkuje - odczytuje port we  uC
	if(!RC5_IN){
		pakiet.toggle = 1 ;

		// Oczekuje na zbocze rosn?ce sygna?u w ?rodku bitu.
		// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
		// bitu, to ko?czy dzia?anie funkcji z b??dem
		while(!RC5_IN){
			if(timerL > ref2){
				pakiet.status = false ;
				return ;
			}				
		}			
	}
	else{
		pakiet.toggle = 0 ;

		// Oczekuje na zbocze opadaj?ce sygna?u w ?rodku bitu.
		// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
		// bitu, to ko?czy dzia?anie funkcji z b??dem
		while(RC5_IN){
			if(timerL > ref2){ 
				pakiet.status = false ;
				return ;
			}			
		}		
		
		
	}

	// W momencie wykrycia zbocza sygna?u, synchronizuje
	// zmien? timerL dla próbkowania kolejnego bitu
	timerL = 0;
			
	//SYS
	pakiet.sys = 0 ;
	for(int i = 0 ; i<5 ; i++){
		// Czeka 3/4 czasu trwania bitu od momentu wykrycia
		// zbocza sygna?u w po?owie poprzedniego bitu
		while(timerL < ref1) {};
		// Próbkuje - odczytuje port we  uC
		if(!RC5_IN){
			pakiet.sys <<= 1 ;

			// Oczekuje na zbocze rosn?ce sygna?u w ?rodku bitu.
			// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
			// bitu, to ko?czy dzia?anie funkcji z b??dem
			while(!RC5_IN){
				if(timerL > ref2){
					pakiet.status = false ;
					return ;
				}
			}
		}
		else{
			pakiet.sys = (pakiet.sys <<1 ) | 0x01;

			// Oczekuje na zbocze opadaj?ce sygna?u w ?rodku bitu.
			// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
			// bitu, to ko?czy dzia?anie funkcji z b??dem
			while(RC5_IN){
				if(timerL > ref2){
					pakiet.status = false ;
					return ;
				}
			}
		
		
		}

		// W momencie wykrycia zbocza sygna?u, synchronizuje
		// zmien? timerL dla próbkowania kolejnego bitu
		timerL = 0;
	}
	
	
	//CMD
	pakiet.cmd = 0 ;
	for(int i = 0 ; i<6 ; i++){
		// Czeka 3/4 czasu trwania bitu od momentu wykrycia
		// zbocza sygna?u w po?owie poprzedniego bitu
		while(timerL < ref1) {};
		// Próbkuje - odczytuje port we  uC
		if(!RC5_IN){
			pakiet.cmd <<= 1 ;

			// Oczekuje na zbocze rosn?ce sygna?u w ?rodku bitu.
			// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
			// bitu, to ko?czy dzia?anie funkcji z b??dem
			while(!RC5_IN){
				if(timerL > ref2){
					pakiet.status = false ;
					return ;
				}
			}
		}
		else{
			pakiet.cmd = (pakiet.cmd <<1 ) | 0x01;

			// Oczekuje na zbocze opadaj?ce sygna?u w ?rodku bitu.
			// Je?li nie wykryje zbocza w ci?gu 5/4 czasu trwania
			// bitu, to ko?czy dzia?anie funkcji z b??dem
			while(RC5_IN){
				if(timerL > ref2){
					pakiet.status = false ;
					return ;
				}
			}
		
		
		}
		// W momencie wykrycia zbocza sygna?u, synchronizuje
		// zmien? timerL dla próbkowania kolejnego bitu
		timerL = 0;
	}
}
