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

void Info_Display(RTC_CharArray info);
void Eco_Display(UART_ChannelType uartChannel);

#endif /* SOURCES_DISP_H_ */
