/*
 * AVRGUI.h
 *
 * Created: 2014-03-10 12:45:12
 *  Author: ehioja-0
 */ 

#ifndef __AVRGUI_H_
#define __AVRGUI_H_

#include "USARTinterrupt.h"
#include "Controller.h"

typedef struct{
	Object super;
	USART sendingUSART;					//Used for lighting up segment when sending Interrupt to PC.
	USART receivingUSART;				//Segment when receiving Interrupt.
	Controller *northqueue;				//Display number of cars in queue.
	Controller *southqueue;
}AVRGUI;

void writeSegment(AVRGUI *this, int northqueue, int southqueue);

#define initAVRGUI(sendingUSART, receivingUSART, northqueue, southqueue){initObject(), sendingUSART, receivingUSART, northqueue, southqueue

#endif __AVRGUI_H_