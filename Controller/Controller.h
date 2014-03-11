/*
 * Controller.h
 *
 * Created: 2014-03-07 16:13:46
 *  Author: ehioja-0
 */ 

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_



typedef struct{
	Object super;
	int northqueue;				//Keep track of the number of cars in each queue.
	int southqueue;
	int timer;					//Used to send USART interrupt periodically.
	//USART receivedUSART;
}Controller;

void northTL(Controller *this, int northqueue, int southqueue);		//TrafficLight methods. Used for switching between ON/OFF State.
void southTL(Controller *this, int northqueue, int southqueue);
void bitwiseUSART(Controller *this);

#define initController(northqueue,southqueue,timer){initObject(),northqueue,southqueue,timer};

#endif __CONTROLLER_H_
