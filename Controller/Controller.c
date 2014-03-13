/*
 * Controller.c
 * Created: 2014-03-07 16:14:02
 *  Author: ehioja-0
 */ 

#include "TinyTimber.h"
#include "Controller.h"

//S-R | S-G | N-R | N-G

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
//-----------------------------------------------------------------------------
	
	if(((this->northqueue)/(this->southqueue))> ){
	}
	
	if((((this->southqueue) == 0) && ((this->northqueue) != 0))){									
		ASYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
		ASYNC(this->gui,updateNorth,this->northqueue);
	}
	
	if((((this->northqueue) - (this->southqueue))>3) && (this->maxiterationNorth) < 5 && (carDecInc < 0)){							
		ASYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
		this->maxiterationNorth += 1;
	}
	if(((this->southqueue) - (this->northqueue)) > 6){
		ASYNC(this->Data,sendtoPC,0x6);						//S-G,N-R
		ASYNC(this->gui,updateSouth,this->southqueue);
		this->maxiterationNorth = 0;
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
	
	if((((this->northqueue) == 0) && ((this->southqueue) != 0))){								
		ASYNC(this->Data,sendtoPC,0x6);						//S-G,N-R
		ASYNC(this->gui,updateSouth,this->southqueue);
	}
	
	if((((this->southqueue) - (this->northqueue))>3) && (this->maxiterationSouth) < 5 && (carDecInc < 0)){		
		ASYNC(this->Data,sendtoPC,0x6);						//S-G,N-R
		this->maxiterationSouth += 1;
	}
	if(((this->southqueue) - (this->northqueue)) > 6){
		ASYNC(this->Data,sendtoPC,0x6);						//S-G,N-R
		ASYNC(this->gui,updateSouth,this->southqueue);
		this->maxiterationNorth = 0;
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





