/*
 * TermHandler.h
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_TERMHANDLER_H_
#define SOURCES_TERMHANDLER_H_


#include "UART.h"
#include "GPIO.h"
#include "NVIC.h"

//#define SYSTEM_CLOCK 110000000
#define SYSTEM_CLOCK 21000000

typedef enum{
	MenuDisp = 0,
	ReadI2CDisp,
	WriteI2CDisp,
	SetHourDisp,
	SetDateDisp,
	SetHourFormatDisp,
	ReadHourDisp,
	ReadDateDisp,
	CommunicationDisp
}Term_MenuDisplayType;

typedef enum{
	Option_param,
	Hour_param,
	Date_param,
	Address_param,
	Data_param,
	Len_param
}Term_inputParametersType;

typedef void (*ftpr_Disp)(UART_ChannelType);

typedef struct{
	uint8 currentMenu :4;
	uint8 currentMenuParameter;
	uint32 address;
	uint32 data;
	uint32 len;
	uint32 tempdata;
	uint32 shift_counter;
}Term_StateMachineType;


uint8 TERMHANDLER_init();

uint8 TERM1_init();

uint8 TERM2_init();

void TERM_upd(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);

void TERM1_upd();

void TERM2_upd();

void TERMHANDLER_upd();

void TERM2_display();

void TERM_menuDisp(UART_ChannelType uartChannel);

void TERM_readI2CDisp1(UART_ChannelType uartChannel);
void TERM_readI2CDisp2(UART_ChannelType uartChannel);
void TERM_readI2CDisp3(UART_ChannelType uartChannel);

void TERM_writeI2CDisp1(UART_ChannelType uartChannel);
void TERM_writeI2CDisp2(UART_ChannelType uartChannel);
void TERM_writeI2CDisp3(UART_ChannelType uartChannel);

void TERM_setHourDisp1(UART_ChannelType uartChannel);
void TERM_setHourDisp2(UART_ChannelType uartChannel);

void TERM_setDateDisp1(UART_ChannelType uartChannel);
void TERM_setDateDisp2(UART_ChannelType uartChannel);

void TERM_setHourFormatDisp(UART_ChannelType uartChannel);

void TERM_readHourDisp(UART_ChannelType uartChannel);

void TERM_readDateDisp(UART_ChannelType uartChannel);

void TERM_communicationDisp(UART_ChannelType uartChannel);

void TERM_lcdDisp(UART_ChannelType uartChannel);
#endif /* SOURCES_TERMHANDLER_H_ */
