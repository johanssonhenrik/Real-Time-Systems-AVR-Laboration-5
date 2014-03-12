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
	Controller *cont;
}USART;

void receivedUSARTfromPC(USART *this);
void start(USART *self);

#define initUSARTinterrupt(cont){initObject(),cont};

#endif __USARTINTERRUPT_H_