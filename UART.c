/*
 * UART.c
 *
 *  Created on: 10/10/2016
 *      Author: Edson
 */

#include "UART.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "DataTypeDefinitions.h"

/*!
 	 \brief	 This is the interrupt services routing (ISR).
 	 \param[in]  void.
 	 \return void
 */


UART_MailBoxType UART0_MailBox = {FALSE,0x0};
UART_MailBoxType UART1_MailBox = {FALSE,0x0};
UART_MailBoxType UART2_MailBox = {FALSE,0x0};
UART_MailBoxType UART3_MailBox = {FALSE,0x0};
UART_MailBoxType UART4_MailBox = {FALSE,0x0};
UART_MailBoxType UART5_MailBox = {FALSE,0x0};

void UART0_RX_TX_IRQHandler(){
	while (!(UART0_S1 & UART_S1_RDRF_MASK));
		UART0_MailBox.flag = TRUE;
		UART0_MailBox.mailBox = UART0_D;
}


void UART1_RX_TX_IRQHandler(){
	while (!(UART1_S1 & UART_S1_RDRF_MASK));
		UART1_MailBox.flag = TRUE;
		UART1_MailBox.mailBox = UART1_D;
}


void UART2_RX_TX_IRQHandler(){
	while (!(UART2_S1 & UART_S1_RDRF_MASK));
		UART2_MailBox.flag = TRUE;
		UART2_MailBox.mailBox = UART2_D;
}


void UART3_RX_TX_IRQHandler(){
	while (!(UART3_S1 & UART_S1_RDRF_MASK));
		UART3_MailBox.flag = TRUE;
		UART3_MailBox.mailBox = UART3_D;
}


void UART4_RX_TX_IRQHandler(){
	while (!(UART4_S1 & UART_S1_RDRF_MASK));
		UART4_MailBox.flag = TRUE;
		UART4_MailBox.mailBox = UART4_D;
}

void UART5_RX_TX_IRQHandler(){
	while (!(UART5_S1 & UART_S1_RDRF_MASK));
		UART5_MailBox.flag = TRUE;
		UART5_MailBox.mailBox = UART5_D;
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
		uint16 IBadrate = (uint16) UARTbaudrate;

		switch(uartChannel){
		case UART_0:
			SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
			UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART0_C1 = 0;
			UART0_BDH = IBadrate>>8;
			UART0_BDL = IBadrate;
			UART0_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;

		case UART_1:
			SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
			UART1_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART1_C1 = 0;
			UART1_BDH = IBadrate>>8;
			UART1_BDL = IBadrate;
			UART1_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;

		case UART_2:
			SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
			UART2_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART2_C1 = 0;
			UART2_BDH = IBadrate>>8;
			UART2_BDL = IBadrate;
			UART2_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;

		case UART_3:
			SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
			UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART3_C1 = 0;
			UART3_BDH = IBadrate>>8;
			UART3_BDL = IBadrate;
			UART3_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;

		case UART_4:
			SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
			UART4_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART4_C1 = 0;
			UART4_BDH = IBadrate>>8;
			UART4_BDL = IBadrate;
			UART4_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;

		case UART_5:
			SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
			UART5_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
			UART5_C1 = 0;
			UART5_BDH = IBadrate>>8;
			UART5_BDL = IBadrate;
			UART5_C2 |= UART_C2_TE_MASK|UART_C2_RE_MASK;
			break;
		}




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
	switch(uartChannel){
	case UART_0:
		UART0_C2 |= UART_C2_RIE_MASK;
		break;

	case UART_1:
		UART1_C2 |= UART_C2_RIE_MASK;
		break;

	case UART_2:
		UART2_C2 |= UART_C2_RIE_MASK;
		break;

	case UART_3:
		UART3_C2 |= UART_C2_RIE_MASK;
		break;

	case UART_4:
		UART4_C2 |= UART_C2_RIE_MASK;
		break;

	case UART_5:
		UART5_C2 |= UART_C2_RIE_MASK;
		break;

	}
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
	switch(uartChannel){
	case UART_0:
		while(!(UART0_S1 & UART_S1_TDRE_MASK));
		UART0_D = (uint8)character;
		break;

	case UART_1:
		while(!(UART1_S1 & UART_S1_TDRE_MASK));
		UART1_D = (uint8)character;
		break;

	case UART_2:
		while(!(UART2_S1 & UART_S1_TDRE_MASK));
		UART2_D = (uint8)character;
		break;

	case UART_3:
		while(!(UART3_S1 & UART_S1_TDRE_MASK));
		UART3_D = (uint8)character;
		break;

	case UART_4:
		while(!(UART4_S1 & UART_S1_TDRE_MASK));
		UART4_D = (uint8)character;
		break;

	case UART_5:
		while(!(UART5_S1 & UART_S1_TDRE_MASK));
		UART5_D = (uint8)character;
		break;
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
		UART_putChar(uartChannel,*string++);
		}
}


