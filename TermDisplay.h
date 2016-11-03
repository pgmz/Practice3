/*
 * TermDisplay.h
 *
 *	This file has all the "graphic" part of the UART for sending stuff.
 *	Has the strings in order to display the menus, and do the RTC read
 *	data transformation, for displaying
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_TERMDISPLAY_H_
#define SOURCES_TERMDISPLAY_H_

#include "MCP7940M.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the main menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_menuDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 reading the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readI2CDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 reading the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readI2CDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the third part of
 	 	 reading the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readI2CDisp3(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 writting the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_writeI2CDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 writting the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_writeI2CDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the third part of
 	 	 writting the 12C memory menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_writeI2CDisp3(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 setting an hour in the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_setHourDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 setting an hour in the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_setHourDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 setting a date in the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_setDateDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 setting a date in the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_setDateDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the setting the hour format in the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_setHourFormatDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 reading the hour from the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readHourDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 reading the hour from the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readHourDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the first part of
 	 	 reading the date from the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readDateDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the second part of
 	 	 reading the date from the RTC menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_readDateDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the communication between terminals
 	 menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_communicationDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the LCD display menu
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_lcdDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the error display
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_ErrorDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 Sends to the uartChannel the data corresponding to the busy display
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  RTC_Char, is the struct that contains the date and hour to be
 	 	 written, if needed
 	 \return void
 */
void TERM_BusyDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function read the hour and date in the RTC, and does the transformation
 	 from uint to char arrays.
 	 \param[in]  Struct_RTC, is where the readed data will be
 	 \param[in]  RTC_Char, is the struct that contains the hour and date in char array format
 	 \return void
 */
void RTC_newRead(RTC_ConfigType* Struct_RTC, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function changes the format in the RTC, by writting in the RTC
 	 \param[in]  Struct_RTC, is where the new format param is.
 	 \return void
 */
void RTC_changeFormat(RTC_ConfigType* Struct_RTC);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function checks the RTC_Char's dates values, and
 	 checks that those values are in an valid range, and then writes them in the struct_config.
 	 This function is the link between: Write Date -> check if valid -> writ in RTC
 	 \param[in]  struct_config, is where the 'safe' values will be stored
 	 \param[in]  RTC_Char, is are values that will be checked if valid
 	 \return void
 */
void Date_Check(RTC_CharArray* RTC_Char ,RTC_ConfigType* struct_config);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function checks the RTC_Char's hour values, and
 	 checks that those values are in an valid range, and then writes them in the struct_config.
 	 This function is the link between: Write Hour -> check if valid -> write in RTC
 	 \param[in]  struct_config, is where the 'safe' values will be stored
 	 \param[in]  RTC_Char, is are values that will be checked if valid
 	 \return void
 */
void Hour_Check(RTC_CharArray* RTC_Char ,RTC_ConfigType* struct_config);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function transform the hour values readed from the RTC to char arrays to be
 	 	 written in the UART channels.
 	 	 This function is the link between: Read Hour -> transform to char arrays -> write in UART
 	 \param[in]  RTC_Char, is where the new values will be stored
 	 \param[in]  struct_config, is are values that will be transformed
 	 \return void
 */
void Cast_Time(RTC_ConfigType* configRAW, RTC_CharArray* RTC_Char);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function transform the date values readed from the RTC to char arrays to be
 	 	 written in the UART channels.
 	 	 This function is the link between: Read Date -> transform to char arrays -> write in UART
 	 \param[in]  RTC_Char, is where the new values will be stored
 	 \param[in]  struct_config, is are values that will be transformed
 	 \return void
 */
void Cast_Date(RTC_ConfigType* configRAW, RTC_CharArray* RTC_Char);

#endif /* SOURCES_TERMDISPLAY_H_ */
