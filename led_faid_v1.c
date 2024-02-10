#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char cDelayDone = 0;

void Delay(long cDelay)
{
	cDelayDone = 0;
	PORTB &= ~0x20;
	OCR0A = cDelay ; //compare value set
	TCNT0 = 0; // clear the counter
	TIMSK0 = 0x02 ; // turn on compare match A
	//while (cDelayDone == 0)
	 //; // wait
	 //TIMSK0 = 0; // turn off interrupt
}

void init()
{
	// set up timer 0 to generate interrupt on register A compare
	OCR0A = 0xFF; // compare value
	TCCR0A = 0x00; // output compare pins disconnected
	TCCR0B = 0x05; // f/1024 = 16MHz/1024=15625Hz
	TIFR0 = 0x03; // clear all flags
	TIMSK0 = 0; // disable all counter 0 interrupts
	TIFR0 = 0x03;
    sei(); // enable global interrupts
}

ISR(TIMER0_COMPA_vect)
{
 cDelayDone = 1;
 PORTB |= 0x20;
}

int main(void) {
	DDRB |= 0x20;
	DDRB |= 0x10;
	char iDutyCycle = 0;

    while(1) {
    	init();
    	Delay(15000);
    	while(cDelayDone == 0){
    		PORTB |= 0x10;
    		_delay_us(iDutyCycle);
    		PORTB &= ~0x10;
    		_delay_us(100 - iDutyCycle);
    	}
    	if(iDutyCycle < 10)
    		iDutyCycle += 1;

    	else
    		iDutyCycle = 0;

    }
    return 0;
}
