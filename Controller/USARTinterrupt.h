/*
 * USARTinterrupt.h
 *
 * Created: 2014-03-07 16:12:54
 *  Author: ehioja-0
 */ 

#ifndef __USARTINTERRUPT_H_
#define __USARTINTERRUPT_H_

#include "AVRGUI.h"
#include "Controller.h"
#include "TinyTimber.h"
#include "avr/io.h"

typedef struct{
	Object super;
	AVRGUI *gui;
	Controller *cont;
	//int receivedUSART;			//This must be changed when interrupt is received from USART PC.
	//int sendtoAVRGUI;			//Used for sending LCD data to GUI. When receiving or sending USART, the LCD must display segments.
	//int sendtoController;		//Used for sending control data to Controller. Used for creating USART message to be sent.
}USART;

void receivedUSARTfromPC(USART *this);
void sendUSARTtoPC(USART *self, int datatosend); // behövs ej!

#define initUSARTinterrupt(gui, cont){initObject(),gui,cont};

#endif __USARTINTERRUPT_H_