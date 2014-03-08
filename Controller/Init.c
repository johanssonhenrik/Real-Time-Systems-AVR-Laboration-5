/*
 * Init.c
 *
 * Created: 2014-03-08 13:31:59
 *  Author: ehioja-0
 */ 

#define FOSC 1843200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
	 
//USART Interrupt initialization
	//PRR = 0x02;					//"PRUSART0" (PRR) = 0, to enable USART Module.
	
	UBRRH = (unsigned char)(ubrr>>8);
	UBBRL = (unsigned char)ubrr;
	
	UCSRB =(1<<RXEN | 1<<TXEN);		//Enable receiver and transmitter.
	UCSRC = (1|USBS)|(3<<UCSZ0);	//Set frame format: 8data, 2 stop bit.
	
	UDRE AND TXC for interrupt