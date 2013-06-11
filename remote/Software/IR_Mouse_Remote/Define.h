/*
 * define.h
 *
 * Created: 2012-12-24 21:11:03
 *  Author: Jedrzej Napierala
 */ 


#ifndef DEFINE_H_
#define DEFINE_H_


//czestotliwosc zegara
#define F_CPU 1000000L


typedef unsigned char byte ;
typedef  unsigned int  uint ;


//Bit = 0
#define Clear_Bit(reg, bit) (reg&=~(1<<bit))
//Bit = 1
#define Set_Bit(reg, bit) (reg|= (1<<bit))

//Pin jako wyjscie
#define Pin_Out(reg, bit) (reg|= (1<<bit))
//Pin jako wejscie
#define Pin_In(reg, bit) (reg&=~(1<<bit))



#endif /* DEFINE_H_ */