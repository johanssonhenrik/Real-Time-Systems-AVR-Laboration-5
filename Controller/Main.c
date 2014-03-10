/*
 * laboration5D0003E.c
 *
 * Created: 2014-03-07 15:01:17
 *  Author: ehioja-0
 */ 
#include <avr/io.h>
#include "AVRGUI.h"
#include "USARTinterrupt.h"
#include "TinyTimber.h"

USART u = initUSARTinterrupt(0);							//receivedUSART
Controller c = initController(0,0,0,0);						//northqueue,southqueue,timer,receivedUSART
AVRGUI g = initAVRGUI(&sendingUSART,&receivingUSART,0,0);	//sendingUSART, receivingUSART, northqueue, southqueue

int main(void){

	INSTALL(&u, receivedUSARTfromPC, IRQ_USART0_RX);
	return TINYTIMBER(&g, update, 0);						//object, method, variable (pulseActive)
}