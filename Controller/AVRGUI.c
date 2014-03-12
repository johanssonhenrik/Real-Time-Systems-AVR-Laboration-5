/*
 * AVRGUI.c
 *
 * Created: 2014-03-10 12:45:01
 *  Author: ehioja-0
 */ 
#include "TinyTimber.h"
#include "AVRGUI.h"
#include <avr/io.h>
#include <avr/iom169p.h>

int ASCII_TABLE[10] = 
{
		0x1551,		// 0 = 1551, A = 0F51
		0x0110,		// 1
		0x1e11,		// 2
		0x1B11,		// 3
		0x0B50,		// 4
		0x1B41,		// 5
		0x1F41,		// 6
		0x0111,		// 7
		0x1F51,		// 8
		0x0B51		// 9
};

void writeChar(AVRGUI *self, int pos, int bokstav){
	
	char mask;
	int karaktar = 0x0000;
	char nibbles = 0x00;
	int x;
	char lcddr = 0xec;
	
	if (pos & 0x01){
		mask = 0x0F;                /* Position 1, 3, 5 */
	}else{
		mask = 0xF0;                /* Position 0, 2, 4  */
	}
	if(bokstav<= 9 && bokstav >= 0){
		//karaktar = self->pulse1->ASCII_TABLE[(int)bokstav]; // -> samma som : (*g).ASCII_TABLE
		karaktar = ASCII_TABLE[(int)bokstav];
	}else{
		karaktar = 0x0000;
	}
	lcddr  += (pos >>1); /* (0,0,1,1,2,2) (LCDDR0, LCDDR0) (LCDDR1, LCDDR1) (LCDDR2, LCDDR2) */

	for(x = 0; x < 4; x++){
		nibbles = karaktar & 0x000f;
		karaktar = karaktar >> 4;
		if(pos & 0x01){					/* True om 1,3,5 */
			nibbles = nibbles << 4;
		}
		_SFR_MEM8(lcddr) = ((_SFR_MEM8(lcddr) & mask) | nibbles);
		lcddr += 5;
	}
}
void printat(AVRGUI *self, int pulseActive){

	//int num;
	//int pp;
	//if(pulseActive == 0){
		//num = self->northqueue->northqueue;
		//pp = 0;
		//num = (((num % 100)/10));					//(num % 100) / 10 + '0', pp,	'0' = 48.
		//writechar(self, pp, num);					//&self -> address, self -> värde.
		//pp = 1;
		//num = ((self->northqueue->northqueue % 10));			//num % 10 + '0', pp,
		//writechar(self, pp, num);
	//}else{
		//num = self->southqueue->southqueue;
		//pp = 3;
		//num = (((num % 100)/10));					//(num % 100) / 10 + '0', pp,
		//writechar(self, pp, num);
		//pp = 4;
		//num = ((self->southqueue->southqueue % 10));		//num % 10 + '0', pp,
		//writechar(self, pp, num);
	//}
}
void update(AVRGUI* self, int numInQueue){
	writeChar(self, 0, numInQueue);							//pulseActive 0..
	writeChar(self, 1, numInQueue);							//or 1.
	
}

void writeSegment(AVRGUI *self, int northqueue, int southqueue){
	
	//if(self->pulseUsed == 0){							//To check where we are. Move from current pulse to the next.								
		//LCDDR17 = 0x10 | LCDDR17;						//default pulseUsed = 1. (pulse2)
		//LCDDR16 = 0xFE & LCDDR16;
		//self->pulseUsed = 1;
		//
	//}else if(self->pulseUsed == 1){
		//LCDDR17 = 0xEF & LCDDR17;
		//LCDDR16 = 0x01 | LCDDR16;
		//self->pulseUsed = 0;
	//}
}