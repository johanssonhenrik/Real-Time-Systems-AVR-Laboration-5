/*
 * Controller.c
 * Created: 2014-03-07 16:14:02
 *  Author: ehioja-0
 */ 

#include "TinyTimber.h"
#include "Controller.h"

void northTL(Controller *this, int carDecInc){
	
	if((((this->northqueue)-(this->southqueue))>3) && (this->maxiterationNorth)<=4){
		this->Data = 0x81;
		SYNC(this->Data,sendtoPC,0);																	//N-G,S-R
		this->maxiterationNorth += 1;
	}else{
		this->maxiterationNorth = 0;
		
		if((this->northqueue == 0) && (carDecInc < 0)){
			this->northqueue = 0;
		}
		if(carDecInc < 0){
			this->northqueue -= carDecInc;
			ASYNC(this->gui,writeChar,this->northqueue);
		}
		if(carDecInc > 0){
			this->northqueue += carDecInc;
			ASYNC(this->gui,writeChar,this->northqueue);
		}

		if(((this->northqueue)-(this->southqueue)<=3) && (this->northqueue)!=0){
			this->Data = 0x81;
			SYNC(this->Data,sendtoPC,0);																//N-G,S-R
		}else if(this->southqueue != 0){
			AFTER(MSEC(5000),this,southTL,0);
		}else if((this->northqueue==0)&&(this->southqueue==0)){
			this->Data = 0x82;
			SYNC(this->Data,sendtoPC,0);																//N-R,S-R !!
		}
	}	
}		
void southTL(Controller *this, int carDecInc){
	
	if((((this->southqueue)-(this->northqueue))>3) && (this->maxiterationSouth)<=4){
		this->Data = 0x06;
		SYNC(this->Data,sendtoPC,0);
	}else{
		this->maxiterationSouth = 0;
		
		if((this->southqueue == 0) && (carDecInc < 0)){
			this->southqueue = 0;
		}
		if(carDecInc < 0){
			this->southqueue -= carDecInc;
			ASYNC(this->gui,writeChar,this->southqueue);
		}
		if(carDecInc > 0){
			this->southqueue += carDecInc;
			ASYNC(this->gui,writeChar,this->southqueue);
		}

		if(((this->southqueue)-(this->northqueue)<=3) && (this->southqueue)!=0){
			this->Data = 0x06;
			SYNC(this->Data,sendtoPC,0);																//N-R,S-G
		}else if(this->northqueue != 0){
			AFTER(MSEC(5000),this,northTL,0);
		}else if((this->southqueue==0)&&(this->northqueue==0)){
			this->Data = 0x82;
			SYNC(this->Data,sendtoPC,0);																//N-R,S-R !!
		}
	}
}
void bitwiseUSART(Controller *this, uint8_t Data){		//Calls each method. Good to have when queues are empty the first time.
	
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
void sendtoPC(Controller *this){
	UDR0 = this->Data;
}





