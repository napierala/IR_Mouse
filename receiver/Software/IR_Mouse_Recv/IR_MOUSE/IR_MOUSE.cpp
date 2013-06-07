/*
 * IR_MOUSE.cpp
 *
 * Created: 2013-06-06 00:20:37
 *  Author: Jedrzej Napierala
 */ 

#include "IR_MOUSE.h"


/* The following function advances sin/cos by a fixed angle
 * and stores the difference to the previous coordinates in the report
 * descriptor.
 * The algorithm is the simulation of a second order differential equation.
 */
void IR_MOUSE::advanceCircleByFixedAngle(){
char    d;

#define DIVIDE_BY_64(val)  (val + (val > 0 ? 32 : -32)) >> 6    /* rounding divide */
    reportBuffer.dx = d = DIVIDE_BY_64(cosinus);
    sinus += d;
    reportBuffer.dy = d = DIVIDE_BY_64(sinus);
    cosinus -= d;
}

void IR_MOUSE::TestMouseMove(){
	reportBuffer.dx = 100;
	reportBuffer.dy = 100;
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
		}		
		//Zapisujemy Toggle
		last_toggle = ir_odbiornik.pakiet.toggle; 
	}
}