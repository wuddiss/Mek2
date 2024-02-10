/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: vidar
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

int main (void) {
	DDRB |= _BV(PB1);

	TCCR1A |= _BV(COM1A1) | _BV(WGM10);
	TCCR1B |= _BV(CS10) | _BV(WGM12);

	uint8_t pwm = 0x00;
	bool up = true;
	
	while(1) {

		OCR1A = pwm;

		if(up == true)
			pwm += 1;
		else
			pwm -= 1;
		if (pwm == 0xff)
			up = false;
		else if (pwm == 0x00)
			up = true;

		_delay_ms(20);
	}
}
