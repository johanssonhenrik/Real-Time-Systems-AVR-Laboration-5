/*
 * USARTinterrupt.h
 *
 * Created: 2014-03-07 16:12:54
 *  Author: ehioja-0
 */ 

#ifndef __USARTINTERRUPT_H_
#define __USARTINTERRUPT_H_

typedef struct{
	Object super;
	int receivedUSART;			//This must be changed when interrupt is received from USART PC.
	//int sendtoAVRGUI;			//Used for sending LCD data to GUI. When receiving or sending USART, the LCD must display segments.
	//int sendtoController;		//Used for sending control data to Controller. Used for creating USART message to be sent.
}USART;

void receivedUSARTfromPC(USART *this);

#define initUSARTinterrupt(receivedUSART){initObject(),receivedUSART}

#endif __USARTINTERRUPT_H_