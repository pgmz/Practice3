/*
 * UART.c
 *
 *  Created on: 10/10/2016
 *      Author: Edson
 */

#include "UART.h"
#include "MK64F12.h"
#include "DataTypeDefinitions.h"

/*!
 	 \brief	 This is the interrupt services routing (ISR).
 	 \param[in]  void.
 	 \return void
 */


UART_MailBoxType UART0_MailBox = {0x0,0x0};

void UART0_Status_IRQHandler(void){
	while (!(UART0_S1 & UART_S1_RDRF_MASK)){
		UART0_MailBox.mailBox =UART0_D;
		UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
	}
}

//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the UART to be used
 	 \param[in]  uartChannel indicates which UART will be used.
 	 \param[in]  systemClk indicates the MCU frequency.
 	 \param[in]  baudRate sets the baud rate to transmit.
 	 \return void
 */
void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	float UARTbaudrate = systemClk/(16*baudRate);
	SIM_SCGC4 = SIM_SCGC4_UART0_MASK;
	UART0_C2 &= ~(1 << UART_C2_TE_MASK);
	UART0_C2 &= ~(1 << UART_C2_RE_MASK);
	UART0_BDH |= UART_BDH_SBR(0x1200);
	UART0_BDL |= UART_BDL_SBR(0x0);
	UART0_C4 |= UART_C4_BRFA(0x0);
	UART0_C2 |= 1 << UART_C2_TE_MASK;
	UART0_C2 |= 1 << UART_C2_RE_MASK;
}

void display(){

}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 enables the RX UART interrupt). This function should include the next sentence:
 	 while (!(UART0_S1 & UART_S1_RDRF_MASK)). It is to guaranty that the incoming data is complete
 	 when reception register is read. For more details see chapter 52 in the kinetis reference manual.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \return void
 */
void UART0_interruptEnable(UART_ChannelType uartChannel){
	UART0_C2 = UART_C2_RIE_MASK;
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends one character through the serial port. This function should include the next sentence:
 	 while(!(UART0_S1 & UART_S1_TC_MASK)). It is to guaranty that before to try to transmit a byte, the previous
 	 one was transmitted. In other word, to avoid to transmit data while the UART is busy transmitting information.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  character to be transmitted.
 	 \return void
 */


void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	while (FALSE == UART_S1_TDRE_MASK ){
		UART0_D = character;
	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends a string character through the serial port.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  string pointer to the string to be transmitted.
 	 \return void
 */
void UART_putString(UART_ChannelType uartChannel, sint8* string){
	while (*string){
		UART_putChar(UART_0,*string++);
	}
}


