/*
 * TermDisplay.h
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_TERMDISPLAY_H_
#define SOURCES_TERMDISPLAY_H_

#include "MCP7940M.h"

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
void TERM_readHourDisp1(UART_ChannelType uartChannel);

void TERM_readDateDisp(UART_ChannelType uartChannel);
void TERM_readDateDisp1(UART_ChannelType uartChannel);

void TERM_communicationDisp(UART_ChannelType uartChannel);

void TERM_lcdDisp(UART_ChannelType uartChannel);

void RTC_newRead();
void RTC_changeFormat(uint8 format);

void Date_Check(RTC_CharArray* struct_char ,RTC_ConfigType* struct_config);
void Hour_Check(RTC_CharArray* struct_char ,RTC_ConfigType* struct_config);

#endif /* SOURCES_TERMDISPLAY_H_ */
