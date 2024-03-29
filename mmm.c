#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "delay.h"
#include "button.h"

#define LED_PIN PB5

int main()
{
	initButton();
	Init_Uart();
	DDRB |= (1 << PB5);   // Set PB5 as output

	int counter = 0;
	char string[16];
	char t[] = "Button Push nr. #";
	char nl[] = "\n\r";
	// Variable to track button state
	uint8_t button_pressed = 0;
	while(1) {
		if (isButtonPressed()){
			delay_ms(100);
			// Button is pressed
			// Check if the button was not pressed previously
			if (!button_pressed) {
				// Toggle the LED
				PORTB ^= (1 << LED_PIN);
				counter++;
				UART_Transmit_String(t);
				UART_itoa(counter, string);
				UART_Transmit_String(string);
				UART_Transmit_String(nl);
				// Set button state to pressed
				button_pressed = 1;
				}
			}
			else {
				// Button is released
				// Set button state to released
				button_pressed = 0;
		    }
	}
}
