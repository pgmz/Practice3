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

/* Enum that define the cases for the state machine  */
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

/* Enum that define what is the data written at the UART */
typedef enum{
	Option_param,
	Hour_param,
	Date_param,
	Address_param,
	Data_param,
	Len_param
}Term_inputParametersType;

/* Type data that define function pointer which the input parameters are the Channel of the UART and arrys of char */
typedef void (*ftpr_Disp)(UART_ChannelType, RTC_CharArray*);

/*Type data that define the information for the state machine to display info in the terminals*/
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

/*Type data that define the information for the state machine to control the behavior of the terminals */
typedef struct{
	uint8 MemBusy :1;
	uint8 RTCBusy :1;
	uint8 Term1Com :1;
	uint8 Term2Com :1;
	uint8 LCDBusy :1;
	char id;
}TermHandler_StateMachineType;

/* Type data that function pointer which the input parameters are the Channel of the UART and the state machine of the terminals */
typedef void (*ftpr_Update)(UART_ChannelType, Term_StateMachineType*);

/*
/*!
 	 \brief		This function enable the interrupt for for the PIT0 and PIT1 and set their prioryties, enable the clockgating and
 				the PIT´s channels. Initializes the terminal 1 (PC-TeraTerm) and terminal 2 (Bluetooth-SenaTerm).

 	 \return 	uint8 return true when the fucntion ends.
 */
uint8 TERMHANDLER_init();

/*
/*!
 	 \brief		This function configure the pins 16 and 17 of the port B, enable the UART Channel 0 and activate the the interruption
 	  	  	  	and set priority

 	 \return 	uint8 return true when the fucntion ends.
 */
uint8 TERM1_init();

/*
/*!
 	 \brief		This function configure the pins 14 and 15 of the port C, enable the UART Channel 4 and activate the the interruption
 	 	 		and set priority

 	 \return 	uint8 return true when the fucntion ends.
 */

uint8 TERM2_init();

/*
/*!
 	 \brief		This function configure the pins 14 and 15 of the port C, enable the UART Channel 4 and activate the the interruption
 	  	  	  	and set priority

 	 \return 	uint8 return true when the fucntion ends.
 */


/*
/*!
 	 \brief		This function refresh the the information of the arrays of char, refresh the the time and date for the dispay

 	 \return 	uint8 return true when the fucntion ends.
 */
uint8 TERM_upd();

/*
/*!
 	 \brief		This function display the menu when the terminals are connected for the first time, also start the refresh of the time
 	  	  	  	and date
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_MenuDisp(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function read the address that user write in the terminals and changes the array of char for a uint16, then serch
 	  	  	  	for address and get the data that is storage there and its size.
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_ReadMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function read the address that user write in the terminals and changes the array of char for a uint16, then serch
 	  	  	  	for address and wait until the user writes what data is going to be saved in address
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what
 	 	 	 	is the next step

 	 \return 	void
*/
static void TERM_WriteMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function read the data that user writes in the terninals validate the information and modify the values of the
 	 	 	 	time
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_WriteHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function read the data that user writes in the terninals validate the information and modify the values of the
 	 	 	 	date
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
*/
static void TERM_WriteDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function read the data that user writes in the terninals validate the information and modify the values of the
 	 	 	 	time
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	  			the next step

 	 \return 	void
 */
static void TERM_WriteFormat(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function send the array of char of time by the UART channel selected
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_ReadHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function send the array of char of date by the UART channel selected
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_ReadDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function make posible the comunication between terminal 1 and terminal 2
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_communication(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function send the data written interminal 1 or 2 to the display
 	 \param[in] uartChannel to configurates the channels of the UART, statemachine to know what position it is the program and what is
 	 	 	 	the next step

 	 \return 	void
 */
static void TERM_LCD(UART_ChannelType uartChannel, Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		This function change the data recived as a string of chars to a uint16
 	 \param[in] statemachine to know what position it is the program and what is the next step

 	 \return 	void
 */
static void Cast_Memory_param(Term_StateMachineType* statemachine);
/*
/*!
 	 \brief		Desactivate the interruption of timer of the channel pit 1

 	 \return 	void
 */
void timeout_Ocurred();
/*
/*!
 	 \brief		Activate the interruption of  the timer of the channel pit 1

 	 \return 	void
 */
void timeout_Enable();
/*
/*!
 	 \brief		Restart the value of the state machine

 	 \return 	void
 */

void timeout_Disable();
/*
/*!
 	 \brief		Activate the interruption of  the timer of the channel pit 1

 	 \return 	uint8 return the value of the macro declared
 */
uint8 timeout_Flag();


#endif /* SOURCES_TERMHANDLER_H_ */
