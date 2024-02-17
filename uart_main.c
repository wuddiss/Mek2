#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

volatile uint8_t pwm = 0x00;

ISR (USART_TX_vect)
{
 char c;
 if (TxBufferReadChar(&c)) //if buff not empty
   UDR0=c; //write the char to UART
}

ISR (TIMER0_OVF_vect)
{
 PORTB=0x20 ; //at overflow turn LED on
}

ISR (TIMER0_COMPA_vect)
{
 PORTB=0x00 ; // at compare level , turn LED off
}

void Delay_ms(unsigned int uiS)
{
  unsigned volatile long ulMax, ulCount;
  ulMax = 380 * (unsigned long) uiS;
  ulCount = 0;
  while(ulCount != ulMax) {
    ulCount++;
  }
}

int main()
{
	DDRB=0x20; //make LED pin output
	TCCR0A=0; // normal mode
	TCCR0B=0x05; // f =16MHz/1024
	OCR0A=255;
  //char teststring[] = "Mec2 is fun \n\r\0";
  Init_Uart();
  //sei();
  asm("sei");
  DDRB=0x20; //LED is output
  while(1)
  {
	char data = rx();
	tx(data);
	OCR0A=data; //50% dutycycle
	TIMSK0=0x03 ; // enable Over flow and Compare A interrupts
	TIFR0=0x03 ; // clear flags
	Delay_ms(50);
  }
  return 0;
}




