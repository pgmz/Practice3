/*
 * TermHandler.c
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"
#include "MCP7940M.h"
#include "M24LC256.h"
#include "TermDisplay.h"

ftpr_Disp ftpr_Disp_Array[16] = {
		&TERM_menuDisp,
		&TERM_readI2CDisp1,
		&TERM_writeI2CDisp1,
		&TERM_setHourDisp1,
		&TERM_setDateDisp1,
		&TERM_setHourFormatDisp,
		&TERM_readHourDisp,
		&TERM_readDateDisp,
		&TERM_communicationDisp,
		&TERM_lcdDisp,
		////

		&TERM_readI2CDisp2,
		&TERM_readI2CDisp3,
		&TERM_writeI2CDisp2,
		&TERM_writeI2CDisp3,
		&TERM_setHourDisp2,
		&TERM_setDateDisp2
		////
};

Term_StateMachineType Term1_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0,
		0,
		0,
		24,
		{{},0,0}
};

Term_StateMachineType Term2_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0,
		0,
		0,
		24,
		{{},0,0}
};

uint8 TERMHANDLER_init(){
	TERM1_init();
	TERM2_init();
	(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0);
	(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4);
}

void TERM_upd(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	if(UART_MailBoxFlag(uartChannel)){
		switch(statemachine->currentMenu){
		case MenuDisp:
			statemachine->data = (UART_MailBoxData(uartChannel)) - '0';

			if((statemachine->data >= 1) && (statemachine->data <= 9)
					&& (statemachine->currentMenuParameter == Option_param)){
				statemachine->currentMenu = statemachine->data;
			}

			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

			break;

		case ReadI2CDisp:

			switch(statemachine->currentMenuParameter){
			case Option_param:
				statemachine->tempdata = ((UART_MailBoxData(uartChannel)) - '0')<<(statemachine->shift_counter);
				statemachine->shift_counter -= 4;
				statemachine->currentMenuParameter = Address_param;
				break;

			case Address_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != -4) && UART_MailBoxData(uartChannel) != 10){

					statemachine->tempdata |= ((UART_MailBoxData(uartChannel)) - '0')<<(statemachine->shift_counter);
					statemachine->shift_counter -= 4;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4) || (UART_MailBoxData(uartChannel) == 10)){

					statemachine->address = statemachine->tempdata;
					statemachine->shift_counter = 24;
					statemachine->currentMenuParameter = Len_param;

					(*ftpr_Disp_Array[10])(uartChannel);
				}
				break;

			case Len_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != -4) && UART_MailBoxData(uartChannel) != 10){
					statemachine->tempdata |= ((UART_MailBoxData(UART_0)) - '0')<<(statemachine->shift_counter);
					statemachine->shift_counter -= 4;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4)|| (UART_MailBoxData(uartChannel) == 10)){
					statemachine->len = statemachine->tempdata;
					statemachine->shift_counter = 24;
					statemachine->currentMenuParameter = Data_param;

					(*ftpr_Disp_Array[11])(uartChannel);
					while(statemachine->len > 0){
						UART_putString(uartChannel, MEM_read(statemachine->address));
						statemachine->len -= 1;
						statemachine->address += 8;
					}
				}

				break;

			case Data_param:
				UART_MailBoxData(uartChannel);
				statemachine->currentMenuParameter = Option_param;
				statemachine->currentMenu = MenuDisp;
				(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

			}
			break;

		case WriteI2CDisp:

			switch(statemachine->currentMenuParameter){
			case Option_param:
				statemachine->tempdata = ((UART_MailBoxData(UART_0)) - '0')<<(statemachine->shift_counter);
				statemachine->shift_counter -= 4;
				statemachine->currentMenuParameter = Address_param;
				break;

			case Address_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != -4)&& UART_MailBoxData(uartChannel) != 10){

					statemachine->tempdata |= ((UART_MailBoxData(uartChannel)) - '0')<<(statemachine->shift_counter);
					statemachine->shift_counter -= 4;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4)|| (UART_MailBoxData(uartChannel) == 10)){

					statemachine->address = statemachine->tempdata;
					statemachine->shift_counter = 24;
					statemachine->currentMenuParameter = Data_param;

					(*ftpr_Disp_Array[12])(uartChannel);
				}
				break;

			case Data_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != -4)&& UART_MailBoxData(uartChannel) != 10){
					statemachine->tempdata |= ((UART_MailBoxData(uartChannel)) - '0')<<(statemachine->shift_counter);
					statemachine->shift_counter -= 4;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4)|| (UART_MailBoxData(uartChannel) == 10)){
					statemachine->data = statemachine->tempdata;
					statemachine->shift_counter = 24;
					statemachine->currentMenuParameter = Len_param;

					(*ftpr_Disp_Array[13])(uartChannel);
					//////Make I2C linking
				}

				break;

			case Len_param:
				UART_MailBoxData(uartChannel);
				statemachine->currentMenuParameter = Option_param;
				statemachine->currentMenu = MenuDisp;
				(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

			}
			break;

			break;

		case SetHourDisp:
			break;

		case SetDateDisp:
			break;

		case SetHourFormatDisp:
			break;

		case ReadHourDisp:
			UART_MailBoxData(uartChannel);
			statemachine->currentMenuParameter = Option_param;
			statemachine->currentMenu = MenuDisp;
			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);
			break;

		case ReadDateDisp:
			UART_MailBoxData(uartChannel);
			statemachine->currentMenuParameter = Option_param;
			statemachine->currentMenu = MenuDisp;
			(*ftpr_Disp_Array[ReadDateDisp])(uartChannel);
			break;

		case CommunicationDisp:
			if((UART_MailBoxData(uartChannel) == 27)){
				UART_putString(uartChannel,"Terminal _ se ha desconectado \r\n");
			} else if ((UART_MailBoxData(uartChannel) == 13) || (UART_MailBoxData(uartChannel) == 10)){

				while(statemachine->f.tail != statemachine->f.head){
					UART_putChar(uartChannel, FIFO_POP(&statemachine->f));
				}
			statemachine->currentMenu = MenuDisp;
			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);
			} else {
				FIFO_PUSH(&statemachine->f,UART_MailBoxData(uartChannel));
			}
			break;
		}

	}
	return;
}


uint8 TERM1_init(){
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOB, BIT16, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT17, &pinControlRegister);

	UART_init(UART_0, SYSTEM_CLOCK, BD_9600, BRFA_19);
	UART0_interruptEnable(UART_0);
	NVIC_enableInterruptAndPriority(UART0_IRQ, PRIORITY_10);

	return TRUE;
}

uint8 TERM2_init(){
	GPIO_clockGating(GPIOC);
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOC, BIT14, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT15, &pinControlRegister);

	UART_init(UART_4, SYSTEM_CLOCK, BD_9600, BRFA_19);
	UART0_interruptEnable(UART_4);
	NVIC_enableInterruptAndPriority(UART4_IRQ, PRIORITY_10);

	return TRUE;
}

void TERMHANDLER_upd(){
	TERM_upd(UART_0, &Term1_StateMachine);
	TERM_upd(UART_4, &Term2_StateMachine);

}
