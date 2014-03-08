/*
 * laboration5D0003E.c
 *
 * Created: 2014-03-07 15:01:17
 *  Author: ehioja-0
 */ 

#include <avr/io.h>
#include "TinyTimber.h"

//Joystick j = initJoy();
Keyboard k = initKey();

int main(void){

	//INSTALL(&j, joystickPORTE, IRQ_USART0_RX);
	INSTALL(&k, keyboard, IRQ_USART0_RX);
	return TINYTIMBER(&g, update, 0);
}