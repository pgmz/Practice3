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
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
}


void UART1_RX_TX_IRQHandler(){
	while (!(UART1_S1 & UART_S1_RDRF_MASK));
		UART1_MailBox.flag = TRUE;
		UART1_MailBox.mailBox = UART1_D;
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
}


void UART2_RX_TX_IRQHandler(){
	while (!(UART2_S1 & UART_S1_RDRF_MASK));
		UART2_MailBox.flag = TRUE;
		UART2_MailBox.mailBox = UART2_D;
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
}


void UART3_RX_TX_IRQHandler(){
	while (!(UART3_S1 & UART_S1_RDRF_MASK));
		UART3_MailBox.flag = TRUE;
		UART3_MailBox.mailBox = UART3_D;
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
}


void UART4_RX_TX_IRQHandler(){
	while (!(UART4_S1 & UART_S1_RDRF_MASK));
		UART4_MailBox.flag = TRUE;
		UART4_MailBox.mailBox = UART4_D;
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
}

void UART5_RX_TX_IRQHandler(){
	while (!(UART5_S1 & UART_S1_RDRF_MASK));
		UART5_MailBox.flag = TRUE;
		UART5_MailBox.mailBox = UART5_D;
		//UART_S1_RDRF_MASK != UART_S1_RDRF_MASK;
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
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
		UART0_C2 &= ~(UART_C2_TE_MASK);
		UART0_C2 &= ~(UART_C2_RE_MASK);
		UART0_C1 = 0;
		//UART0_BDH |= UART_BDH_SBR((IBadrate & 0xFF00)>>8);
		//UART0_BDL |= UART_BDL_SBR(IBadrate & 0x00FF);
		UART0_BDH = IBadrate>>8;
		UART0_BDL = IBadrate;
		//UART0_C4 |= UART_C4_BRFA(0x0);
		UART0_C2 |= UART_C2_TE_MASK;
		UART0_C2 |= UART_C2_RE_MASK;

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
		UART0_C2 |= UART_C2_RIE_MASK;
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
	 while(!(UART0_S1 & UART_S1_TDRE_MASK));
	UART0_D = (uint8)character;
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

/****
 * My UART functions, for TERATERM
 */


