/*
 * button.c
 *
 *  Created on: Feb 4, 2024
 *      Author: vidar
 */
#include <stdio.h>
#include "button.h"
#include <avr/io.h>

void initButton(){
	DDRD &= ~0b00000100;  // Set inngang 2 inngagnur fyrir takka
}

int isButtonPressed() {

	int buttonstate = PIND & 0b00000100; // Ath stöðu á inngangi 2

    return buttonstate; // Skila stöðu á pinna 2
}
