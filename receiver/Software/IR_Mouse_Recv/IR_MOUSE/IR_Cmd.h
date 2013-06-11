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
#define SYS_IR_MOUSE 5

#define IR_MOUSE_NONE			0
//Nawigacja
#define IR_MOUSE_UP				1
#define IR_MOUSE_DOWN			2
#define IR_MOUSE_LEFT			3
#define IR_MOUSE_RIGHT			4

//Przyciski
#define IR_MOUSE_LEFT_BUTT		5
#define IR_MOUSE_RIGHT_BUTT		6

//Kolko myszy
#define IR_MOUSE_SCRL_UP		7
#define IR_MOUSE_SCRL_DOWN		8
#define IR_MOUSE_SCRL_BUTTON	9

#endif /* IR_CMD_H_ */