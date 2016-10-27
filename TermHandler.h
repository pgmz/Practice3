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
	CommunicationDisp,
}Term_MenuDisplayType;

typedef struct{
	void (*ftpr_MenuDisp)(UART_ChannelType);
	void (*ftpr_ReadI2CDisp)(UART_ChannelType);
	void (*ftpr_WriteI2CDisp)(UART_ChannelType);
	void (*ftpr_SetHourDisp)(UART_ChannelType);
	void (*ftpr_SetDateDisp)(UART_ChannelType);
	void (*ftpr_SetHourFormatDisp)(UART_ChannelType);
	void (*ftpr_ReadHourDisp)(UART_ChannelType);
	void (*ftpr_ReadDateDisp)(UART_ChannelType);
	void (*ftpr_CommunicationDisp)(UART_ChannelType);
}Term_MenuDisplayPointerType;

#define TERM1_USE 1
#define TERM2_USE 2

typedef enum{
	Option_param,
	Hour_param,
	Date_param,
	Address_param
}Term_inputParametersType;

typedef struct{
	uint8 currentMenu :2;
	uint8 waitingForParameter :1;
	uint8 curretMenuParameter;
}Term_TXRXStateMachineType;

typedef struct{
	uint8 RTC_access :1;
	uint8 MEM_access :1;
	uint8 LCD_access :1;
	uint8 TERM1_chat :1;
	uint8 TERM2_chat :1;
	uint8 TERM1_comm : 1;
	uint8 TERM2_comm :1;
}Term_StateMachineType;

uint8 TERMHANDLER_init();

uint8 TERM2_init();


void TERM2_display();

void TERM_menuDisp(UART_ChannelType uartChannel);

void TERM_readI2CDisp(UART_ChannelType uartChannel);

void TERM_writeI2CDisp(UART_ChannelType uartChannel);

void TERM_setHourDisp(UART_ChannelType uartChannel);

void TERM_setDateDisp(UART_ChannelType uartChannel);

void TERM_setHourFormatDisp(UART_ChannelType uartChannel);



#endif /* SOURCES_TERMHANDLER_H_ */
