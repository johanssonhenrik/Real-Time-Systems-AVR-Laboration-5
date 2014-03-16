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

	


	if(((this->northqueue)==(this->southqueue)) && ((this->northqueue) != 0) && ((this->southqueue) != 0)){		//If both queues are equal size. Send North.
		SYNC(this->Data,sendtoPC,0x9);
	}
	
	if((((this->northqueue) != 0) && ((this->southqueue) == 0))){			//Prioritise northqueue if southqueue == 0.
		SYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
		
		}else if(((this->northqueue) - (this->southqueue))<=3 && ((this->northqueue) - (this->southqueue))>0 && (this->maxiterationNorth) == 0){
		SYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
	}
	if(((this->northqueue) - (this->southqueue))>3 && (this->maxiterationNorth) == 0 && (this->maxiterationSouth) == 0){
		this->maxiterationNorth = (this->northqueue)/(this->southqueue);
	}
	if(this->maxiterationNorth != 0 && this->maxiterationSouth == 0){
		//AFTER(MSEC(1000),this->Data,sendtoPC,0x9);
		SYNC(this->Data,sendtoPC,0x9);						//N-G,S-R
		this->maxiterationNorth -= 1;
	}
	if((((this->northqueue) == 0) && ((this->southqueue) == 0))){			//If both queues are zero. Set both TL to RED.
		SYNC(this->Data,sendtoPC,0xa);
	}



	if((this->northqueue == 0) && (carDecInc < 0)){		//Can't Decrease if Queue is already zero.
		this->northqueue = 0;
	}
	if(carDecInc < 0){									//Decrease Number of Cars.
		this->northqueue -= carDecInc;
		SYNC(this->gui,updateNorth,this->northqueue);
	}
	if(carDecInc > 0){									//Increase Number of Cars.
		this->northqueue += carDecInc;
		SYNC(this->gui,updateNorth,this->northqueue);
	} // Increase and Decrease Number of Cars in Queue.
//-----------------------------------------------------------------------------------------
	
	
}	
	
void southTL(Controller *this, int carDecInc){

	//if(this->southqueue > this->northqueue){
		//sendtoPC(this,0x6);						//N-R,S-G
	//}
	//if(this->northqueue > this->southqueue){
	//	sendtoPC(this,0x9);
	//}
	if((((this->southqueue) == 0) && ((this->northqueue) == 0))){			//If both queues are zero. Set both TL to RED.
		SYNC(this->Data,sendtoPC,0xa);
	}
	if((((this->southqueue) != 0) && ((this->northqueue) == 0))){			//Prioritise northqueue if southqueue == 0.
		SYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
		
		}else if( ((this->southqueue) - (this->northqueue))<=3 && ((this->southqueue) - (this->northqueue))>=0  && (this->maxiterationSouth) == 0){
		SYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
	}
	if(((this->southqueue) - (this->northqueue))>3 && (this->maxiterationSouth) == 0 && (this->maxiterationNorth) == 0){
		this->maxiterationSouth = (this->southqueue)/(this->northqueue);
		
		}else if(this->maxiterationSouth != 0 && this->maxiterationNorth == 0){
		//AFTER(MSEC(1000),this->Data,sendtoPC,0x6);
		SYNC(this->Data,sendtoPC,0x6);						//N-R,S-G
		this->maxiterationSouth -= 1;
	}
	if((((this->southqueue) == 0) && ((this->northqueue) == 0))){			//If both queues are zero. Set both TL to RED.
		SYNC(this->Data,sendtoPC,0xa);
	}
	
	
	
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
	} //Increase and Decrease Number of Cars in Queue.
	//-----------------------------------------------------------------------------
	
	
	

	
	
}

void bitwiseUSART(Controller *this, uint8_t Data){		//Calls each method. Good to have when queues are empty the first time.
	
	//S-R | S-G | N-R | N-G
	
	//SCE | SCA | NCE | NCA
	
	
	ASYNC(this->gui,updateSouth,Data);
	
	if((Data & 1) == 1){			//Bit 0. Northbound car arrival sensor activated				A
		northTL(this, 1);
		writeSegment(this,0);
	}
	if(((Data >> 1) & 1) == 1){		//Bit 1. Northbound bridge entry sensor activated				B
		northTL(this, -1);
	}
	if(((Data >> 2) & 1) == 1){		//Bit 2. Southbound car arrival sensor activated				A
		southTL(this, 1);
		writeSegment(this,1);
	}
	if(((Data >> 3) & 1) == 1){		//Bit 3. Southbound bridge entry sensor activated				B
		southTL(this, -1);
	}
}
void sendtoPC(Controller *this, uint8_t Data){
	//writeSegment()
	UDR0 = Data;
}





