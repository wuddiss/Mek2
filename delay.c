/*
 * main.c
 *
 *  Created on: Jan 18, 2024
 *      Author: vidar
 */
#include<avr/io.h>
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 800; j++) { // Adjust this value depending on your clock frequency
            asm volatile ("nop"); // No operation (1 cycle)
        }
    }
}

void delay_s(unsigned int s) {
	unsigned int sek = s * 1000;
	delay_ms(sek);
}

int main() {
    // Your main code here
	DDRB |= (1<<PB5); //setting built-in LED as output
    while(1) {
        // Example usage of delay_ms function
    	PORTB |= 0x20; // you can use PORTB |= (1<<PB5)
        delay_s(2); // Delay for 1000 milliseconds (1 second)
        PORTB &= ~0x20; // you can use PORTB &= ~(1<<PB5)
        delay_s(2); // Delay for 1000 milliseconds (1 second)
        // Your main code continues here
    }

    return 0;
}
