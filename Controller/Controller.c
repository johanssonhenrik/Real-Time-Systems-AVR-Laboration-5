/*
 * Controller.c
 * Created: 2014-03-07 16:14:02
 *  Author: ehioja-0
 */ 

#include "TinyTimber.h"
#include "Controller.h"

//S-R | S-G | N-R | N-G

uint8_t SR,SG,NR,NG;
uint8_t DERP = 0x9;

void northTL(Controller *this, int carDecInc){
	
	if((this->northqueue == 0) && (carDecInc < 0)){		//Can't Decrease if Queue is already zero.
		this->northqueue = 0;
	}
	if(carDecInc < 0){									//Decrease Number of Cars.
		this->northqueue -= carDecInc;
		ASYNC(this->gui,updateNorth,this->northqueue);
	}
	if(carDecInc > 0){									//Increase Number of Cars.
		this->northqueue += carDecInc;
		ASYNC(this->gui,updateNorth,this->northqueue);
	}
//-----------------------------------------------------------------------------------------
	
	if((((this->northqueue) != 0) && ((this->southqueue) == 0))){			//Prioritise northqueue if southqueue == 0.  
		

		SYNC(this->Data,sendtoPC,DERP);						//N-G,S-R
		ASYNC(this->gui,updateNorth,this->northqueue);
		
	}else if(((this->northqueue) - (this->southqueue))<=3 && ((this->northqueue) - (this->southqueue))>0 && ((this->southqueue) == 0)){
		ASYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
		ASYNC(this->gui,updateNorth,this->northqueue);
		
	}else if(((this->northqueue) - (this->southqueue))>3 && (this->maxiterationNorth) == 0 && (this->maxiterationSouth) == 0){
		this->maxiterationNorth = (this->northqueue)/(this->southqueue);
		
	}else if(this->maxiterationNorth != 0 && this->maxiterationSouth == 0){
		//AFTER(MSEC(1000),this->Data,sendtoPC,0x9);				
		ASYNC(this->Data,sendtoPC,0x9);						//N-G,S-R		
		ASYNC(this->gui,updateNorth,this->northqueue);
		this->maxiterationNorth -= 1;
		
		//northTL(this,-1);
	}
}	
	
void southTL(Controller *this, int carDecInc){
	
	if((this->southqueue == 0) && (carDecInc < 0)){		//Can't Decrease if Queue is already zero.
		this->southqueue = 0;
	}
	if(carDecInc < 0){									//Decrease Number of Cars.
		this->southqueue -= carDecInc;
		ASYNC(this->gui,updateSouth,this->southqueue);
	}
	if(carDecInc > 0){									//Increase Number of Cars.
		this->southqueue += carDecInc;
		ASYNC(this->gui,updateSouth,this->southqueue);
	}
	//-----------------------------------------------------------------------------
	
	if((((this->southqueue) != 0) && ((this->northqueue) == 0))){			//Prioritise northqueue if southqueue == 0.
		ASYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
		ASYNC(this->gui,updateSouth,this->southqueue);
		
	}else if( ((this->southqueue) - (this->northqueue))<=3 && ((this->southqueue) - (this->northqueue))>0 && ((this->northqueue) == 0)){
		ASYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
		ASYNC(this->gui,updateSouth,this->southqueue);
		
	}else if(((this->southqueue) - (this->northqueue))>3 && (this->maxiterationSouth) == 0 && (this->maxiterationNorth) == 0){
		this->maxiterationSouth = (this->southqueue)/(this->northqueue);
		
	}else if(this->maxiterationSouth != 0 && this->maxiterationNorth == 0){
		//AFTER(MSEC(1000),this->Data,sendtoPC,0x6);
		ASYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
		ASYNC(this->gui,updateSouth,this->southqueue);
		this->maxiterationSouth -= 1;
		//southTL(this,-1);	
	}
}

void bitwiseUSART(Controller *this, uint8_t Data){		//Calls each method. Good to have when queues are empty the first time.
	
	if((Data & 1) == 1){			//Bit 0. Northbound car arrival sensor activated
		northTL(this, 1);
		writeSegment(this,0);
	}
	if(((Data >> 1) & 1) == 1){		//Bit 1. Northbound bridge entry sensor activated
		northTL(this, -1);
	}
	if(((Data >> 2) & 1) == 1){		//Bit 2. Southbound car arrival sensor activated
		southTL(this, 1);
		writeSegment(this,1);
	}
	if(((Data >> 3) & 1) == 1){		//Bit 3. Southbound bridge entry sensor activated
		southTL(this, -1);
	}
}
void sendtoPC(Controller *this, uint8_t Data){
	UDR0 = Data;
}





