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

#endif /* UART_H_ */
