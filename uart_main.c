#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

ISR (USART_TX_vect)
{
 char c;
 if (TxBufferReadChar(&c)) //if buff not empty
   UDR0=c; //write the char to UART
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
  char teststring[] = "Mec2 is fun \n\r\0";
  Init_Uart();
  //sei();
  asm("sei");
  DDRB=0x20; //LED is output
  //while(1)
  //{
    PORTB=0x20;
    PORTB=0;
    TxPrintString(teststring); //note: we dont test for error, but we could
    Delay_ms(100);
  //}
  return 0;
}
