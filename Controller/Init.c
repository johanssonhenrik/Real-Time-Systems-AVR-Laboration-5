/*
 * Init.c
 *
 * Created: 2014-03-08 13:31:59
 *  Author: ehioja-0
 */ 

#define CPUFREQ 8000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((CPUFREQ / (USART_BAUDRATE * 16UL))) - 1)

#include "TinyTimber.h"
#include "Init.h"
#include <avr/io.h>
#include <avr/interrupt.h>
 
void Init(){

//Clock prescaler
	CLKPR = 0x80;
	CLKPR = 0x00;
//LCD
	LCDCRA = 0xC0;			//LCD ENABLE and LOW POWER WAVEFORM
	LCDCRB = 0xB7;			//AsyncClock, 1/3 Bias, 1/4 Duty, 25 Segments 
	LCDFRR = 0x07;			//LCD Clock Divide 32 Hz
	LCDCCR = 0x0F;			//3.35 Volt		
	TCCR1B = 0x0D;			//Clock prescaler set to 1024 and CFC.
//INTERRUPT
	EIFR = 0xc0;			//Interrupt request
	EIMSK = 0xc0;			//Cause an interrupt
//USART	
	UBRR0H = BAUD_PRESCALE>>8;
	UBRR0L = BAUD_PRESCALE;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
}