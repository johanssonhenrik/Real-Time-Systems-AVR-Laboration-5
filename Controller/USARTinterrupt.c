/*
 * USARTinterrupt.c
 *
 * Created: 2014-03-07 16:11:18
 *  Author: ehioja-0
 */ 

#include "USARTinterrupt.h"

void receivedUSARTfromPC(USART *self){

	uint8_t TestData = UDR0;
	UDR0 = TestData + 1;	
	//LCDDR17 = 0x10;				//Initial d section lit
	//ASYNC(self->gui,printat,0);
	ASYNC(self->cont,bitwiseUSART,0);
}
void sendUSARTtoPC(USART *self, int datatosend){
	
}

