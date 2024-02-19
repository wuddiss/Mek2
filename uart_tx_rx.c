/*
 * main.c
 *
 *  Created on: Feb 10, 2024
 *      Author: vidar
 */
#include <avr/io.h>

int iIn; //iIn points to next free space in buffer
int iOut; //iOut point to oldest data in buffer
int cData; //Data

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 800; j++) { // Adjust this value depending on your clock frequency
            asm volatile ("nop"); // No operation (1 cycle)
        }
    }
}

void Init_Uart()
{
 //baudrate = 57600
 UBRR0H=0;
 UBRR0L=16;

 //enable receiver and transmitter, Rx complete interrupt enable
 UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<TXCIE0);
 //set frame format
 UCSR0C=(1<<USBS0)|(3<<UCSZ00);
 //UCSR0C=0x06;
 iIn=iOut=0; //Initialize buffer pointers
}

void tx(int cData)
{
   while (!(UCSR0A&(1<<UDRE0)));
   //put data into buffe -r
    UDR0=cData;
}

int rx()
{
   while (!(UCSR0A&(1<<RXC0)));
   //get and return data
   cData= UDR0;

   return cData;
}

int main()
{
  Init_Uart();
  asm("sei");
  while(1)
  {
	char data = rx();
	tx(data+0x01);
	delay_ms(50);
  }
  return 0;
}



