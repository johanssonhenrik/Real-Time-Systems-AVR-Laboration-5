/*
 * USARTinterrupt.c
 *
 * Created: 2014-03-07 16:11:18
 *  Author: ehioja-0
 */ 

#include "TinyTimber.h"
#include "USARTinterrupt.h"

void receivedUSARTfromPC(USART *self){
	
	//Here we must parse the USART Interrupt from 4 bits.
	//Depending on the bits. Corresponding method must be called.
	
	//ASYNC(self->receivedUSART, Gate, self->whichpulse);
}

