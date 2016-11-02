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
#include "MCP7940M.h"
#include <setjmp.h>

//#define SYSTEM_CLOCK 110000000
//#define SYSTEM_CLOCK 21000000
#define SYSTEM_CLOCK 60000000


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
	LCDDisp
}Term_MenuDisplayType;

typedef enum{
	Option_param,
	Hour_param,
	Date_param,
	Address_param,
	Data_param,
	Len_param
}Term_inputParametersType;

typedef void (*ftpr_Disp)(UART_ChannelType, RTC_CharArray*);

typedef struct{
	char id;
	uint8 currentMenu :4;
	uint8 currentMenuParameter;
	uint16 address;
	char char_address [4];
	uint32 data;
	uint32 len;
	char char_len [2];
	uint32 tempdata;
	uint32 shift_counter;
	FIFO_Type f;
}Term_StateMachineType;

typedef struct{
	uint8 MemBusy :1;
	uint8 RTCBusy :1;
	uint8 Term1Com :1;
	uint8 Term2Com :1;
	uint8 LCDBusy :1;
	char id;
}TermHandler_StateMachineType;

typedef void (*ftpr_Update)(UART_ChannelType, Term_StateMachineType*);

uint8 TERMHANDLER_init();

uint8 TERM1_init();

uint8 TERM2_init();

void TERM_UGLY_upd(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);

uint8 TERM_upd();

static void TERM_MenuDisp(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_ReadMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_WriteMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_WriteHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_WriteDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_WriteFormat(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_ReadHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_ReadDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_communication(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
static void TERM_LCD(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);

static void Cast_Memory_param(Term_StateMachineType* statemachine);


void timeout_Ocurred();

void timeout_Enable();

void timeout_Disable();

uint8 timeout_Flag();

void Button_Hour();
#endif /* SOURCES_TERMHANDLER_H_ */
