/*
 * DISP.h
 *
 *  Created on: 06/10/2016
 *      Author: Edson
 */

#ifndef SOURCES_MENU_H_
#define SOURCES_MENU_H_

#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"
#include "MCP7940M.h"
#include "UART.h"

/*
	\brief	This Function clear the Display LCD, write the time and date

	\param[in]	info contains the arrays of char of time and date
	\return	void
 */
void Info_Display(RTC_CharArray info);

/*
	\brief	This Function clear the Display LCD and write the message that was written at the PC terminal or SmartPhone terminal

	\param[in]	uartChannel input value that determine the UART channel that is used to trasmit the message to the LCD
	\return	void
 */
void Eco_Display(UART_ChannelType uartChannel);

#endif /* SOURCES_DISP_H_ */
