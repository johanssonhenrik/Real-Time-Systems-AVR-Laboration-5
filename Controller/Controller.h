/*
 * Controller.h
 *
 * Created: 2014-03-07 16:13:46
 *  Author: ehioja-0
 */ 

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_
#include "avr/io.h"
#include "TinyTimber.h"
#include "AVRGUI.h"


typedef struct{
	Object super;
	int northqueue;				//Keep track of the number of cars in each queue.
	int southqueue;
	AVRGUI *gui;
	uint8_t Data;
	int previousqueue;
}Controller;

void trafficlights(Controller *this);		//TrafficLight methods. Used for switching between ON/OFF State.
void southTL(Controller *this, int carDecInc);
void bitwiseUSART(Controller *this, uint8_t Data);
void sendtoPC(Controller *this, uint8_t Data);

#define initController(northqueue,southqueue,gui,Data, previousqueue){initObject(),northqueue,southqueue,gui,Data, previousqueue};

#endif __CONTROLLER_H_
