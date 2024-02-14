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

void initStepper() {
	DDRB |= 0b00001111; // Set útgang 8,9,10,11
}

void steps_wd_fw(int speed, int steps) { // Hringur er 50 step
	for (int i = 0; i < steps; i++) {
		step_wd_fw(speed);
	}
}

void steps_wd_bw(int speed, int steps) { // Hringur er 50 step
	for (int i = 0; i < steps; i++) {
		step_wd_bw(speed);
	}
}

void step_wd_fw(int speed) {
	for (int i = 0; i < 4; i++) {
		wave_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void step_wd_bw(int speed) {
	for (int i = 3; i >= 0; i--) {
		wave_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void step_fsd_fw(int speed) {
	for (int i = 0; i < 4; i++) {
		full_step_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void step_fsd_bw(int speed) {
	for (int i = 3; i >= 0; i--) {
		full_step_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void step_hsd_fw(int speed) {
	for (int i = 0; i < 8; i++) {
		half_step_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void step_hsd_bw(int speed) {
	for (int i = 7; i >= 0; i--) {
		half_step_drive(i);
		_delay_ms(speed);  // Denounce töf
	}
}

void wave_drive(int step) {
	switch (step) {
	  case 0:
		  PORTB |= 0b00000001; // Útgangur 8 - Fasi A - ON
		  PORTB &= ~0b00000010; // Útgangur 9 - Fasi A' - OFF
		  PORTB &= ~0b00000100; // Útgangur 10 - Fasi B - OFF
		  PORTB &= ~0b00001000; // Útgangur 11 - Fasi B' - OFF
	    break;
	  case 1:
		  PORTB &= ~0b00000001; // Útgangur 8 - Fasi A - OFF
		  PORTB &= ~0b00000010; // Útgangur 9 - Fasi A' - OFF
		  PORTB |= 0b00000100; // Útgangur 10 - Fasi B - ON
		  PORTB &= ~0b00001000; // Útgangur 11 - Fasi B' - OFF
	    break;
	  case 2:
		  PORTB &= ~0b00000001; // Útgangur 8 - Fasi A - OFF
		  PORTB |= 0b00000010; // Útgangur 9 - Fasi A' - ON
		  PORTB &= ~0b00000100; // Útgangur 10 - Fasi B - OFF
		  PORTB &= ~0b00001000; // Útgangur 11 - Fasi B' - OFF
	    break;
	  case 3:
		  PORTB &= ~0b00000001; // Útgangur 8 - Fasi A - OFF
		  PORTB &= ~0b00000010; // Útgangur 9 - Fasi A' - OFF
		  PORTB &= ~0b00000100; // Útgangur 10 - Fasi B - OFF
		  PORTB |= 0b00001000; // Útgangur 11 - Fasi B' - ON
	    break;
	}
}

void full_step_drive(int step) {
	switch (step) {
		case 0:
			PORTB |= 0b00000001; // LED útgangur 8 - Fasi A - ON
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB |= 0b00001000; // LED útgangur 11 - Fasi B' - ON
		break;
		case 1:
			PORTB |= 0b00000001; // LED útgangur 8 - Fasi A - ON
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB |= 0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 2:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB |= 0b00000010; // LED útgangur 9 - Fasi A' - ON
			PORTB |= 0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 3:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB |= 0b00000010; // LED útgangur 9 - Fasi A' - ON
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB |= 0b00001000; // LED útgangur 11 - Fasi B' - ON
		break;
	}
}

void half_step_drive(int step) {
	switch (step) {
		case 0:
			PORTB |= 0b00000001; // LED útgangur 8 - Fasi A - ON
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 1:
			PORTB |= 0b00000001; // LED útgangur 8 - Fasi A - ON
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB |= 0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 2:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB |= 0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 3:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB |= 0b00000010; // LED útgangur 9 - Fasi A' - ON
			PORTB |= 0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 4:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB |= 0b00000010; // LED útgangur 9 - Fasi A' - ON
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB &= ~0b00001000; // LED útgangur 11 - Fasi B' - OFF
		break;
		case 5:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB |= 0b00000010; // LED útgangur 9 - Fasi A' - ON
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB |= 0b00001000; // LED útgangur 11 - Fasi B' - ON
		break;
		case 6:
			PORTB &= ~0b00000001; // LED útgangur 8 - Fasi A - OFF
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - ON
			PORTB |= 0b00001000; // LED útgangur 11 - Fasi B' - ON
		break;
		case 7:
			PORTB |= 0b00000001; // LED útgangur 8 - Fasi A - ON
			PORTB &= ~0b00000010; // LED útgangur 9 - Fasi A' - OFF
			PORTB &= ~0b00000100; // LED útgangur 10 - Fasi B - OFF
			PORTB |= 0b00001000; // LED útgangur 11 - Fasi B' - ON
		break;
	}
}
