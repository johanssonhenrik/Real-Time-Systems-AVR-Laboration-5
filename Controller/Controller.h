/*
 * Controller.h
 *
 * Created: 2014-03-07 16:13:46
 *  Author: ehioja-0
 */ 

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_
#include "avr/io.h"


typedef struct{
	Object super;
	int northqueue;				//Keep track of the number of cars in each queue.
	int southqueue;
	int timer;					//Used to send USART interrupt periodically.
	//USART receivedUSART;
}Controller;

void northTL(Controller *this, int carIncrease);		//TrafficLight methods. Used for switching between ON/OFF State.
void southTL(Controller *this, int carIncrease);
void bitwiseUSART(Controller *this, uint8_t Data);

#define initController(northqueue,southqueue,timer){initObject(),northqueue,southqueue,timer};

#endif __CONTROLLER_H_
