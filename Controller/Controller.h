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
	int timer;					//Used to send USART interrupt periodically.
	int maxiterationNorth;
	int maxiterationSouth;
	AVRGUI *gui;
	uint8_t Data;
	//USART receivedUSART;
}Controller;

void northTL(Controller *this, int carDecInc);		//TrafficLight methods. Used for switching between ON/OFF State.
void southTL(Controller *this, int carDecInc);
void bitwiseUSART(Controller *this, uint8_t Data);
void sendtoPC(Controller *this, uint8_t Data);

#define initController(northqueue,southqueue,timer,maxiterationNorth,maxiterationSouth,gui,Data){initObject(),northqueue,southqueue,timer,maxiterationNorth,maxiterationSouth,gui,Data};

#endif __CONTROLLER_H_
