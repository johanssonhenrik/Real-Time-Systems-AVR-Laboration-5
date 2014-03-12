/*
 * AVRGUI.h
 *
 * Created: 2014-03-10 12:45:12
 *  Author: ehioja-0
 */ 

#ifndef __AVRGUI_H_
#define __AVRGUI_H_
#include "TinyTimber.h"

typedef struct{
	Object super;
}AVRGUI;

//void writeSegment(AVRGUI *this, int northqueue, int southqueue);
void writeChar(AVRGUI *self, int pos, int bokstav);
void update(AVRGUI* self, int numInQueue);
void printat(AVRGUI* self, int pulseActive);

#define initAVRGUI(){initObject()};

#endif __AVRGUI_H_