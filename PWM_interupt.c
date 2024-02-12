#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

 volatile uint8_t pwm = 0x00;
 volatile bool up = true;

 ISR (TIMER0_OVF_vect)
 {
 PORTB=0x20 ; //at overflow turn LED on
 }

 ISR (TIMER0_COMPA_vect)
 {
 PORTB=0x00 ; // at compare level , turn LED off
 }

 int main()
 {

 DDRB=0x20 ; //make LED pin output
 TCCR0A=0; // normal mode
 TCCR0B=0x05 ; // f =16MHz/1024
 sei(); // switch on global interrupt
 while(1)
 {
	 OCR0A=pwm; //50% dutycycle
	  TIMSK0=0x03 ; // enable Over flow and Compare A interrupts
	  TIFR0=0x03 ; // clear flags


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
