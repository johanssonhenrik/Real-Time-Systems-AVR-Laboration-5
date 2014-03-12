/*
 * USARTinterrupt.c
 *
 * Created: 2014-03-07 16:11:18
 *  Author: ehioja-0
 */ 

#include "USARTinterrupt.h"

void receivedUSARTfromPC(USART *self){

	uint8_t Data = UDR0;	
	//LCDDR17 = 0x10;				//Initial d section lit
	//ASYNC(self->gui,printat,0);
	ASYNC(self->cont,bitwiseUSART,Data);
}


void sendUSARTtoPC(USART *self, int datatosend){
	
}

