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
	Address_param
}Term_inputParametersType;

typedef void (*ftpr_Disp)(UART_ChannelType);

typedef struct{
	uint8 currentMenu :4;
	uint8 currentMenuParameter;
	uint8 address;
	uint32 data;
}Term_StateMachineType;

typedef struct{
	uint8 param_in;
	uint8 currentState :1;
	uint8 nextState :1;
}Term_StateChangesType;

uint8 TERMHANDLER_init();

uint8 TERM1_init();

uint8 TERM2_init();

void TERM1_upd();

void TERM2_upd();

void TERMHANDLER_upd();

void TERM2_display();

void TERM_menuDisp(UART_ChannelType uartChannel);

void TERM_readI2CDisp(UART_ChannelType uartChannel);

void TERM_writeI2CDisp(UART_ChannelType uartChannel);

void TERM_setHourDisp(UART_ChannelType uartChannel);

void TERM_setDateDisp(UART_ChannelType uartChannel);

void TERM_setHourFormatDisp(UART_ChannelType uartChannel);

void TERM_readHourDisp(UART_ChannelType uartChannel);

void TERM_readDateDisp(UART_ChannelType uartChannel);

void TERM_communicationDisp(UART_ChannelType uartChannel);


#endif /* SOURCES_TERMHANDLER_H_ */
