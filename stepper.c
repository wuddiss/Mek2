/*
 * stepper.c
 *
 *  Created on: Feb 8, 2024
 *      Author: vidar
 */
#include <stdio.h>
#include "stepper.h"
#include <avr/io.h>
#include <util/delay.h>


void stepper_rs(int speed) {

	  	PORTB &= ~0b00000001; // LED útgangur 8 á
	  	PORTB |= 0b00000010; // LED útgangur 9 af
	  	PORTB &= ~0b00000100; // LED útgangur 10 á
	  	PORTB |= 0b00001000; // LED útgangur 11 af

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB &= ~0b00000001; // LED útgangur 8 af
	  	PORTB |= 0b00000010; // LED útgangur 9 a
	  	PORTB |= 0b00000100; // LED útgangur 10 á
	  	PORTB &= ~0b00001000; // LED útgangur 11 af

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB |= 0b00000001; // LED útgangur 8 af
	  	PORTB &= ~0b00000010; // LED útgangur 9 a
	  	PORTB |= 0b00000100; // LED útgangur 10 af
	  	PORTB &= ~0b00001000; // LED útgangur 11 á

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB |= 0b00000001; // LED útgangur 8 á
	  	PORTB &= ~0b00000010; // LED útgangur 9 af
	  	PORTB &= ~0b00000100; // LED útgangur 10 af
	  	PORTB |= 0b00001000; // LED útgangur 11 á

	  	_delay_ms(speed);  // Denounce töf
	}

void stepper_ws(int speed) {

	  	PORTB &= ~0b00000001; // LED útgangur 8 á
	  	PORTB |= 0b00000010; // LED útgangur 9 af
	  	PORTB &= ~0b00000100; // LED útgangur 10 á
	  	PORTB |= 0b00001000; // LED útgangur 11 af

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB |= 0b00000001; // LED útgangur 8 á
	  	PORTB &= ~0b00000010; // LED útgangur 9 af
	  	PORTB &= ~0b00000100; // LED útgangur 10 af
	    PORTB |= 0b00001000; // LED útgangur 11 á

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB |= 0b00000001; // LED útgangur 8 af
	  	PORTB &= ~0b00000010; // LED útgangur 9 a
	  	PORTB |= 0b00000100; // LED útgangur 10 af
	  	PORTB &= ~0b00001000; // LED útgangur 11 á

	  	_delay_ms(speed);  // Denounce töf

	  	PORTB &= ~0b00000001; // LED útgangur 8 af
	  	PORTB |= 0b00000010; // LED útgangur 9 a
	  	PORTB |= 0b00000100; // LED útgangur 10 á
	  	PORTB &= ~0b00001000; // LED útgangur 11 af

	  	_delay_ms(speed);  // Denounce töf
	}

