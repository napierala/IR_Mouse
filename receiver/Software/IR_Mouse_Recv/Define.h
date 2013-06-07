/*
 * Define.h
 *
 * Created: 2013-04-11 19:59:04
 *  Author: Jedrzej Napierala
 */ 


#ifndef DEFINE_H_
#define DEFINE_H_

#include "Clock_Speed.h"

typedef unsigned char byte ;
typedef  unsigned int  uint ;

typedef struct{
	byte   buttonMask;
	char    dx;
	char    dy;
	char    dWheel;
}report_t;


//Bit = 0
#define Clear_Bit(reg, bit) (reg&=~(1<<bit))
//Bit = 1
#define Set_Bit(reg, bit) (reg|= (1<<bit))

//Pin jako wyjscie
#define Pin_Out(reg, bit) (reg|= (1<<bit))
//Pin jako wejscie
#define Pin_In(reg, bit) (reg&=~(1<<bit))



#endif /* DEFINE_H_ */