/*
 * USARTinterrupt.c
 *
 * Created: 2014-03-07 16:11:18
 *  Author: ehioja-0
 */ 

#include "USARTinterrupt.h"

void receivedUSARTfromPC(USART *self){

	uint8_t Data = UDR0;	
	ASYNC(self->cont,bitwiseUSART,Data);
}
void start(USART *self){
	
}

