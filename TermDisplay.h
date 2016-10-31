/*
 * TermDisplay.h
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_TERMDISPLAY_H_
#define SOURCES_TERMDISPLAY_H_

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

#endif /* SOURCES_TERMDISPLAY_H_ */
