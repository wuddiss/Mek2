/*
 * Uart.c
 *
 *  Created on: Feb 17, 2024
 *      Author: vidar
 */
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFERSIZE 32

int TxBuffer[BUFFERSIZE]; //ring buffer
int iIn; //iIn points to next free space in buffer
int iOut; //iOut point to oldest data in buffe r
int cData;

//buffer is empty if iIn==iOut
//buffer is full if next(iIn)==iOut

// increment index and wrap around if at end
int NextIndex(int index)
{
 index++;
 if(index >= BUFFERSIZE)
 index=0;
 return index;
}

//return 1 if buffer is full, else return 0
char TxBufferEmpty()
{
 if(iIn==iOut) return 1;
 else return 0;
}

//return 1 if buffer full, else return 0
char TxBufferFull()
{
 if(NextIndex(iIn)==iOut) return 1;
 else return 0;
}

//return 1 if success, 0 if error
char TxBufferAddChar(char cData)
{
 char retval = 1; //default: success
 if(!TxBufferFull())
 {
   TxBuffer[iIn] = cData;
   iIn = NextIndex(iIn); //advance in-pointer
 }
 else retval=0; //don't touch buffer, indicate error
 return retval;
 }

char TxBufferReadChar(char* pData)
{
 char retval = 1; //default: success
 if(!TxBufferEmpty())
 {
   *pData = TxBuffer[iOut];
   iOut = NextIndex(iOut);
 }
 else retval = 0;
 return retval;
}

//return 1 if succes, O if error
char TxPrintString(char* pChar)
{
 char cSuccess = 1; //default: succes s
 char cData;
 while(*pChar != 0)
 {
   if(TxBufferAddChar(*pChar))
   ; //success, do nothing
   else{
	   cSuccess = 0;//indicate error
       break ; //brake the whileloop
       }
   pChar++;//point to next char
 }
 //manually start the writing by writing the first char
 if(UCSR0A&(1<<UDRE0))
 {
   if(TxBufferReadChar(&cData))
     UDR0=cData;
   else
     cSuccess=0;
 }
 return cSuccess;
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
    // put data into buffer
    UDR0=cData;
}

int rx()
{
   while (!(UCSR0A&(1<<RXC0)));
    //get and return data
   cData= UDR0;

   return cData;
}

int recive_tx()
{
   while (!(UCSR0A&(1<<RXC0)));
    //get and return data
   cData= UDR0;

   while (!(UCSR0A&(1<<UDRE0)));
    // pu t da ta i n t o b u f f e r
    UDR0=cData;


   return cData;
}

void UART_Transmit_Nibble_Hex(unsigned char data)
 {
 unsigned char c;
 c = ' ';
 data = data & 0x0F;
 if ((data >= 0) && (data < 10))
 c = '0' + data;
 if ((data>=10) && (data <= 15))
 c='A'+(data-10);
 tx(c);
 }

void Transmit_Byte_Hex(unsigned char data)
{
  UART_Transmit_Nibble_Hex(data >> 4);
  UART_Transmit_Nibble_Hex(data & 0x0F);
}

void Transmit_int_Hex(unsigned int data)
{
  Transmit_Byte_Hex(data >> 8);
  Transmit_Byte_Hex(data & 0xFF);
}

void Transmit_long_Hex(unsigned long data)
{
  Transmit_int_Hex(data >> 16);
  Transmit_int_Hex(data & 0xFFFFFFFF);
}

void UART_Transmit_Byte_Hex(unsigned char data)
{
	tx('0');
	tx('x');
	Transmit_Byte_Hex(data);
}

void UART_Transmit_int_Hex(unsigned int data)
{
	tx('0');
	tx('x');
	Transmit_int_Hex(data);
}

void UART_Transmit_long_Hex(unsigned long data)
{
	tx('0');
	tx('x');
	Transmit_long_Hex(data);
}

void UART_Transmit_long_Decimal(unsigned long num) {
	unsigned long digit;
	unsigned long reversedNum = 0;

    // Reverse the number
    while (num != 0) {
        digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }

    // Extract digits
    while (reversedNum != 0) {
        digit = reversedNum % 10;
        UART_Transmit_Nibble_Hex(digit);
        reversedNum /= 10;
    }
}

void UART_Transmit_int_Decimal(unsigned int num) {
	unsigned int digit;
	unsigned int reversedNum = 0;

    // Reverse the number
    while (num != 0) {
        digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }

    // Extract digits
    while (reversedNum != 0) {
        digit = reversedNum % 10;
        UART_Transmit_Nibble_Hex(digit);
        reversedNum /= 10;
    }
}

void UART_Transmit_Byte_Decimal(unsigned char num) {
	unsigned char digit;
	unsigned char reversedNum = 0;

    // Reverse the number
    while (num != 0) {
        digit = num % 10;
        reversedNum = reversedNum * 10 + digit;
        num /= 10;
    }

    // Extract digits
    while (reversedNum != 0) {
        digit = reversedNum % 10;
        UART_Transmit_Nibble_Hex(digit);
        reversedNum /= 10;
    }
}

void UART_Transmit_String(char s[]) {
 char cIndex = 0;
 while(s[cIndex] != 0)
 {
    tx(s[cIndex]);
    cIndex++;
 }
}
