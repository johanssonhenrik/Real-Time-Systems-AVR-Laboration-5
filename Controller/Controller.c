/*
 * Controller.c
 *
 * Created: 2014-03-07 16:14:02
 *  Author: ehioja-0
 */ 

#include "TinyTimber.h"
#include "Controller.h"

int northTL(Controller *this, int carIncrease){
	
	if (this->northqueue == 0){
		return NULL;
	}
	
	this->northqueue += carIncrease;
	
	//if(){
	UDR0 = 0x1;	
	//}
}		
int southTL(Controller *this, int carIncrease){
	
	if (this->southqueue == 0){
		return NULL;
	}
	this->southqueue += carIncrease;
	
	//if(){
	UDR0 = 0x2;
	//}
	
}
void bitwiseUSART(Controller *this, uint8_t Data){
	
	if((Data & 1) == 1){			//Bit 0. Northbound car arrival sensor activated
		northTL(this, 1);
	}
	if(((Data >> 1) & 1) == 1){		//Bit 1. Northbound bridge entry sensor activated
		northTL(this, -1);
	}
	if(((Data >> 2) & 1) == 1){		//Bit 2. Southbound car arrival sensor activated
		southTL(this, 1);
	}
	if(((Data >> 3) & 1) == 1){		//Bit 3. Southbound bridge entry sensor activated
		southTL(this, -1);
	}
}





