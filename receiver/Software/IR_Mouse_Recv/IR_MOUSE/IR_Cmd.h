/*
 * IR_Cmd.h
 *
 * Created: 2012-12-25 15:49:01
 *  Author: Jedrzej Napierala
 */ 


#ifndef IR_CMD_H_
#define IR_CMD_H_


struct RC5_packet
{
	unsigned cmd		: 6;    // 0..61	(6 bits)
	unsigned sys		: 5;    // 0..31	(5 bits)
	unsigned toggle		: 1;    // 0..1		(1 bits)
	
	unsigned status     : 1;    // 0..1		(1 bits)
};

/************************************************************************/
/*								IR_MOUSE								*/
/************************************************************************/
#define SYS_IR_MOUSE 26

//Nawigacja
#define IR_MOUSE_UP				0
#define IR_MOUSE_DOWN			1
#define IR_MOUSE_LEFT			2
#define IR_MOUSE_RIGHT			3

//Przyciski
#define IR_MOUSE_LEFT_BUTT		4
#define IR_MOUSE_RIGHT_BUTT		5

//Kolko myszy
#define IR_MOUSE_SCRL_UP		6
#define IR_MOUSE_SCRL_DOWN		7
#define IR_MOUSE_SCRL_BUTTON	8

#endif /* IR_CMD_H_ */