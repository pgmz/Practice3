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
#include "FIFO.h"

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
	FIFO_Type f;
}Term_StateMachineType;


uint8 TERMHANDLER_init();

uint8 TERM1_init();

uint8 TERM2_init();

void TERM_upd(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);

void TERM1_upd();

void TERM2_upd();

void TERMHANDLER_upd();

void TERM2_display();

#endif /* SOURCES_TERMHANDLER_H_ */
