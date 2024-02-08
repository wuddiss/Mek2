/*
 * main.c
 *
 *  Created on: Jan 18, 2024
 *      Author: vidar
 */
#include<avr/io.h>
#include<util/delay.h>
int main(void){
	DDRB |= (1<<PB5); //setting built-in LED as output
	while(1){
		PORTB |= 0x20; // you can use PORTB |= (1<<PB5)
		_delay_ms(10);
		PORTB &= ~0x20; // you can use PORTB &= ~(1<<PB5)
		_delay_ms(10);
	}
}
