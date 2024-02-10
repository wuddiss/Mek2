/*
 * led.c
 *
 *  Created on: Feb 4, 2024
 *      Author: vidar
 */
#include <stdio.h>
#include "led.h"
#include <avr/io.h>

void initLED() {
	DDRB |= 0b00100000; // Set LED sem útgang 13
}

void LED_off() {
	PORTB &= ~0b00100000; // LED útgangur 13 á
}

void LED_on() {
	PORTB |= 0b00100000; // LED útgangur 13 aff
}
