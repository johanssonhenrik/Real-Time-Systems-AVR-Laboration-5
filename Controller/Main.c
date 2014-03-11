/*
 * laboration5D0003E.c
 *
 * Created: 2014-03-07 15:01:17
 *  Author: ehioja-0
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "AVRGUI.h"
#include "USARTinterrupt.h"
#include "TinyTimber.h"
#include "Init.h"

Controller c = initController(0,0,0);				//northqueue,southqueue,timer,receivedUSART
AVRGUI g = initAVRGUI();							//northqueue, southqueue
USART u = initUSARTinterrupt(&g, &c);				//receivedUSART

int main(void){

	Init();
	INSTALL(&u, receivedUSARTfromPC, IRQ_USART0_RX);
	sei();
	return TINYTIMBER(&u, sendUSARTtoPC, 0);						//object, method, variable (pulseActive)
}