/*
 * TermHandler.h
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_TERMHANDLER_H_
#define SOURCES_TERMHANDLER_H_


#include "UART.h"

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

typedef struct{
	uint8 Term1_RTC :1;
	uint8 Term2_RTC :1;
	uint8 Term1_Memory :1;
	uint8 Term2_Menory :1;
}Term_StateMachineType;





#endif /* SOURCES_TERMHANDLER_H_ */
