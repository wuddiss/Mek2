/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: vidar
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

volatile char cDelayDone = 0;

void Delay(char cDelay)
{
	cDelayDone = 0;
	OCR0A = cDelay ; //compare value set
	TCNT0 = 0; // clear the counter
	TIMSK0 = 0x02 ; // turn on compare match A
	while (cDelayDone == 0)
	 ; // wait
	TIMSK0 = 0; // turn off interrupt
}

int main(void) {
    DDRB = 0x20;
    // set up timer 0 to generate interrupt on register A compare
    OCR0A = 0xFF; // compare value
    TCCR0A = 0x00; // output compare pins disconnected
    TCCR0B = 0x05; // f/1024 = 16MHz/1024=15625Hz
    TIFR0 = 0x03; // clear all flags
    TIMSK0 = 0; // disable all counter 0 interrupts
    TIFR0 = 0x03;
    sei(); // enable global interrupts
    
    while (1) {
    	int iDutyCycle = 80;
        PORTB = 0x20;
        _delay_us(iDutyCycle);
        PORTB = 0;
        _delay_us(100 - iDutyCycle);

    }
    return 0;
}
