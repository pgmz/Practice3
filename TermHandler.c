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
#include "PIT.h"

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

ftpr_Update ftpr_Update_Array [10]= {
		&TERM_MenuDisp,
		&TERM_ReadMem,
		&TERM_WriteMem,
		&TERM_WriteHour,
		&TERM_WriteDate,
		&TERM_WriteFormat,
		&TERM_ReadHour,
		&TERM_ReadDate,
		&TERM_communication,
		&TERM_LCD
};

Term_StateMachineType Term1_StateMachine = {
		'1',
		MenuDisp,
		Option_param,
		0x0,
		"0x0000",
		0,
		0,
		"0000",
		0,
		0,
		{{},0,0}
};

Term_StateMachineType Term2_StateMachine = {
		'2',
		MenuDisp,
		Option_param,
		0x0,
		"0x0000",
		0,
		0,
		"0000",
		0,
		0,
		{{},0,0}
};

TermHandler_StateMachineType TermHandler_StateMachine = {
		FALSE, FALSE, FALSE, FALSE, FALSE
};

uint8 TERMHANDLER_init(){
	NVIC_enableInterruptAndPriority(PIT_CH0_IRQ, PRIORITY_8);
	EnableInterrupts;


	PIT_clockGating();
	PIT_enable();
	PIT_delay(PIT_0,SYSTEM_CLOCK,2);
	PIT_timerInterruptEnable(PIT_0);
	PIT_timerEnable(PIT_0);

	TERM1_init();
	TERM2_init();
	(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0);
	(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4);
}

void TERM_UGLY_upd(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	if(UART_MailBoxFlag(uartChannel)){
		switch(statemachine->currentMenu){
		case MenuDisp:


			break;


/////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
		case ReadI2CDisp:

			switch(statemachine->currentMenuParameter){
			case Option_param:

				statemachine->tempdata = ((UART_MailBoxData(uartChannel)))<<(statemachine->shift_counter*4);
				statemachine->shift_counter++;
				statemachine->currentMenuParameter = Address_param;
				break;

			case Address_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 5) && UART_MailBoxData(uartChannel) != 10){

					statemachine->tempdata = ((UART_MailBoxData(uartChannel))|(statemachine->tempdata)) << (statemachine->shift_counter*4);
					statemachine->shift_counter++;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4) || (UART_MailBoxData(uartChannel) == 10)){

					statemachine->address = statemachine->tempdata;
					statemachine->tempdata = 0;
					statemachine->shift_counter = 0;
					statemachine->currentMenuParameter = Len_param;
					(*ftpr_Disp_Array[10])(uartChannel);
				}
				break;

			case Len_param:
				if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != -4) && UART_MailBoxData(uartChannel) != 10){
					statemachine->tempdata = ((UART_MailBoxData(uartChannel))|(statemachine->tempdata)) << (statemachine->shift_counter*4);
					statemachine->shift_counter++;

				}
				if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == -4)|| (UART_MailBoxData(uartChannel) == 10)){
					statemachine->len = statemachine->tempdata;
					statemachine->shift_counter = 0;
					statemachine->currentMenuParameter = Data_param;

					(*ftpr_Disp_Array[11])(uartChannel);
					while(statemachine->len > 0){
						UART_putChar(uartChannel, MEM_read(statemachine->address));
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
}
	}
}

uint8 TERM_upd(){
	if(UART_MailBoxFlag(UART_0)){
	(*ftpr_Update_Array[Term1_StateMachine.currentMenu])(UART_0, &Term1_StateMachine);
	}
	if(UART_MailBoxFlag(UART_4)){
	(*ftpr_Update_Array[Term2_StateMachine.currentMenu])(UART_4, &Term2_StateMachine);
	}
	if(PIT_mailBoxFlag(PIT_0) == TRUE){
		RTC_newRead();
		if((Term1_StateMachine.currentMenu == MenuDisp) ||
				(Term1_StateMachine.currentMenu == ReadHourDisp) || (Term1_StateMachine.currentMenu == ReadDateDisp)){
			(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0);
		}
		if((Term2_StateMachine.currentMenu == MenuDisp) ||
				(Term2_StateMachine.currentMenu == ReadHourDisp) || (Term2_StateMachine.currentMenu == ReadDateDisp)){
			(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4);
		}
	}
}

void TERM_ReadMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}
void TERM_WriteMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}
void TERM_WriteHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}
void TERM_WriteDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}
void TERM_WriteFormat(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}
void TERM_LCD(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

}

void TERM_communication(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	//What if [ESC]
	if((UART_MailBoxData(uartChannel) == 27)){

					//go back to Main menu
					statemachine->currentMenu = MenuDisp;
					statemachine->currentMenuParameter = Option_param;
					(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

					//If we are terminal 1 and terminal 2 is on, make ir know that we leave
					if(statemachine->id == '1' && TermHandler_StateMachine.Term2Com == TRUE){
						UART_putString(UART_4, "\r\nLa terminal 1 se ha desconectado ... [ESC] \r\n");
						TermHandler_StateMachine.Term1Com = FALSE;

					//If we are terminal 2 and terminal 1 is on, make it know that we leave
					} else if(statemachine->id == '2' && TermHandler_StateMachine.Term1Com == TRUE){
						UART_putString(UART_0, "\r\nLa terminal 2 se ha desconectado ... [ESC] \r\n");
						TermHandler_StateMachine.Term2Com = FALSE;
					}


	//what if [ENTER]
				} else if ((UART_MailBoxData(uartChannel) == 13)){

					//if both terminals are on, write on them
					if(TermHandler_StateMachine.Term2Com == TRUE && TermHandler_StateMachine.Term1Com == TRUE){
						UART_putString(UART_0, "\r\nTerminal");
						UART_putChar(UART_0, statemachine->id);
						UART_putString(UART_0, ": ");

						UART_putString(UART_4, "\r\nTerminal ");
						UART_putChar(UART_4, statemachine->id);
						UART_putString(UART_4, ": ");

					} else {
						UART_putString(uartChannel, "\r\nTerminal ");
						UART_putChar(uartChannel, statemachine->id);
						UART_putString(uartChannel, ": ");

					}

					while(statemachine->f.tail != statemachine->f.head){

						//save data
						char data = FIFO_POP(&statemachine->f);


						//if both terminals are on, write on them
						if(TermHandler_StateMachine.Term2Com == TRUE && TermHandler_StateMachine.Term1Com == TRUE){
							UART_putChar(UART_0, data);
							UART_putChar(UART_4, data);

						//if not, just write in '''''local'''''
						} else {
							UART_putChar(uartChannel, data);
						}
					}
					UART_putString(uartChannel," [ENTER]\r\n");
					FIFO_restart(&statemachine->f);

	//what if we receive any other type of data
				} else {
					FIFO_PUSH(&statemachine->f,UART_MailBoxData(uartChannel));
				}
}

void TERM_ReadDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;
	(*ftpr_Disp_Array[ReadDateDisp])(uartChannel);
}

void TERM_ReadHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;
	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

}

void TERM_MenuDisp(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	statemachine->data = (UART_MailBoxData(uartChannel)) - '0';
	if((statemachine->data >= 1) && (statemachine->data <= 9)
			&& (statemachine->currentMenuParameter == Option_param)){
		statemachine->currentMenu = statemachine->data;
	}
	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);

	if(statemachine->currentMenu == CommunicationDisp){
	switch(statemachine->id){
				case '1':
					TermHandler_StateMachine.Term1Com = TRUE;
					if(TermHandler_StateMachine.Term2Com){
					UART_putString(UART_4, "\r\nLa terminal 1 se ha conectado ... \r\n");
					UART_putString(UART_0, "\r\nLa terminal 2 está conectada ... \r\n");


					}
					break;

				case '2':
					TermHandler_StateMachine.Term2Com = TRUE;
					if(TermHandler_StateMachine.Term1Com){
					UART_putString(UART_4, "\r\nLa terminal 1 está conectada ... \r\n");
					UART_putString(UART_0, "\r\nLa terminal 2 se ha conectado ... \r\n");
					}
					break;
				}
	}

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



void Cast_Add_Len(){

}
