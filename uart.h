/*
 * uart.h
 *
 *  Created on: Feb 17, 2024
 *      Author: vidar
 */

#ifndef UART_H_
#define UART_H_

int NextIndex(int index);

//return 1 if buffer is full, else return 0
char TxBufferEmpty();

//return 1 if buffer full, else return 0
char TxBufferFull();

//return 1 if success, 0 if error
char TxBufferAddChar(char cData);

char TxBufferReadChar(char* pData);

//return 1 if success, O if error
char TxPrintString(char* pChar);

void Init_Uart();

int recive_tx();

void tx(int cData);

int rx();

void UART_Transmit_Nibble_Hex(unsigned char data);

void Transmit_Byte_Hex(unsigned char data);

void Transmit_int_Hex(unsigned int data);

void Transmit_long_Hex(unsigned long data);

void UART_Transmit_Byte_Hex(unsigned char data);

void UART_Transmit_int_Hex(unsigned int data);

void UART_Transmit_long_Hex(unsigned long data);

void UART_Transmit_long_Decimal(unsigned long num);

void UART_Transmit_int_Decimal(unsigned int num);

void UART_Transmit_Byte_Decimal(unsigned char num);

void UART_Transmit_String(char s[]);

#endif /* UART_H_ */
