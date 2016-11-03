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
#include "DISP.h"
#include "LCDNokia5110.h"

/*Set the value for Time and Date to write */
RTC_ConfigType Struct_RTC_W = {
		6,
		41,
		17,
		22,
		1,
		18,
		17,
		16
};
/*Set the value for Time and Date to read */
RTC_ConfigType Struct_RTC_R = {
		6,
		41,
		17,
		22,
		1,
		18,
		17,
		16
};
/*Set the value of the string of char for time and date to write*/
RTC_CharArray Struct_Char_W = {
		"00:00:00 AM",
		"\0",
		"01/01/2000",
		"\0",
		1
};
/*Set the value of the string of char for time and date to read*/
RTC_CharArray Struct_Char_R = {
		"00:00:00 AM",
		"\0",
		"01/01/2000",
		"\0",
		1
};
/*Set array of function pointer that prints information for the UART*/
ftpr_Disp ftpr_Disp_Array[20] = {
								//////
		&TERM_menuDisp,			//0 //
		&TERM_readI2CDisp1,		//1 //
		&TERM_writeI2CDisp1,	//2 //
		&TERM_setHourDisp1,		//3 //
		&TERM_setDateDisp1,		//4 //
		&TERM_setHourFormatDisp,//5 //
		&TERM_readHourDisp,		//6 //
		&TERM_readDateDisp,		//7 //
		&TERM_communicationDisp,//8 //
		&TERM_lcdDisp,			//9 //

		&TERM_readI2CDisp2,		//10//
		&TERM_readI2CDisp3,		//11//
		&TERM_writeI2CDisp2,	//12//
		&TERM_writeI2CDisp3,	//13//
		&TERM_setHourDisp2,		//14//
		&TERM_setDateDisp2,		//15//

		&TERM_readHourDisp1,	//16//
		&TERM_readDateDisp1,	//17//

		&TERM_ErrorDisp,		//18//
		&TERM_BusyDisp			//19//
								//////
};
/*Set array of function pointer that modify the information*/
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
/* Set the value to start the state machine for terminal 1*/
Term_StateMachineType Term1_StateMachine = {
		'1',
		MenuDisp,
		Option_param,
		0x0,
		"0000",
		0,
		0,
		"00",
		0,
		0,
		{{},0,0}
};
/* Set the value to start the state machine for terminal 2*/
Term_StateMachineType Term2_StateMachine = {
		'2',
		MenuDisp,
		Option_param,
		0x0,
		"0000",
		0,
		0,
		"00",
		0,
		0,
		{{},0,0}
};

/* Set the value to start the state machine for the terminal handler*/
TermHandler_StateMachineType TermHandler_StateMachine = {
		FALSE, FALSE, FALSE, FALSE, FALSE
};

/* Set the value of the flag*/
static uint8 timeout_flag = FALSE;
/* Set the value ofn the flag*/
static uint8 timeout_notification = FALSE;

uint8 TERM_upd(){
	/* Verify the flag of the mailbox of the channel 0 of the UART*/
	if(UART_MailBoxFlag(UART_0)){
	TermHandler_StateMachine.id = '1';
	(*ftpr_Update_Array[Term1_StateMachine.currentMenu])(UART_0, &Term1_StateMachine);

	}
	/* Verify the flag of the mailbox of the channel 4 of the UART*/
	if(UART_MailBoxFlag(UART_4)){
	TermHandler_StateMachine.id = '2';
	(*ftpr_Update_Array[Term2_StateMachine.currentMenu])(UART_4, &Term2_StateMachine);
	}

	TermHandler_StateMachine.id = '0';

	/* Verify the flag of the mailbox of the channel 0 of the PIT*/
	if(PIT_mailBoxFlag(PIT_0) == TRUE){

		timeout_Enable();
		/* Wait until the bus of the channel 0 of the I2C is busy*/
		while(I2C_busy(I2C_0) == TRUE);
		RTC_newRead(&Struct_RTC_R, &Struct_Char_R);
		timeout_Disable();
		/* Verify the position of the state machine of the terminal 1*/
		if((Term1_StateMachine.currentMenu == ReadHourDisp)){
			/*Read the value of the time*/
			(*ftpr_Disp_Array[16])(UART_0, &Struct_Char_R);
			/* Verify the position of the state machine of the terminal 1*/
		} else if((Term1_StateMachine.currentMenu == ReadDateDisp)){
			/*Read the value of the date*/
			(*ftpr_Disp_Array[17])(UART_0, &Struct_Char_R);
		}
		/* Verify the position of the state machine of the terminal 2*/
		if((Term2_StateMachine.currentMenu == ReadHourDisp)){
			/*Read the value of the time*/
			(*ftpr_Disp_Array[16])(UART_4, &Struct_Char_R);
			/* Verify the position of the state machine of the terminal 2*/
		} else if((Term2_StateMachine.currentMenu == ReadDateDisp)){
			/*Read the value of the date*/
			(*ftpr_Disp_Array[17])(UART_4, &Struct_Char_R);
		}

		if(TermHandler_StateMachine.LCDBusy == FALSE){
		Info_Display(&Struct_Char_R);
		}
	}
}

/*Read the data of the addres*/
void TERM_ReadMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	/* Read what the user write and decide what to do */
	switch(statemachine->currentMenuParameter){
	case Option_param:

		statemachine->char_address[0] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;
		statemachine->currentMenuParameter = Address_param;
		break;

	case Address_param:
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 4)){

			statemachine->char_address[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 4)){
			statemachine->shift_counter = 0;
			statemachine->currentMenuParameter = Len_param;
			(*ftpr_Disp_Array[10])(uartChannel, &Struct_Char_R);
		}
		break;

	case Len_param:
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 2)){
			statemachine->char_len[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 2)){
			statemachine->shift_counter = 0;
			statemachine->currentMenuParameter = Data_param;

			(*ftpr_Disp_Array[11])(uartChannel, &Struct_Char_R);

			Cast_Memory_param(statemachine);

			while(statemachine->len > 0){

				timeout_Enable();
				UART_putChar(uartChannel, MEM_read(statemachine->address));
				timeout_Disable();
				statemachine->len -= 1;
				statemachine->address += 8;
			}

			statemachine->address = 0;

			UART_putString(uartChannel, "\r\nPresione cualquier tecla para continuar... ");
		}

		break;

	case Data_param:
		UART_MailBoxData(uartChannel);
		statemachine->currentMenuParameter = Option_param;
		statemachine->currentMenu = MenuDisp;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.MemBusy = FALSE;

		break;
	}
}

/*Write the data of the address selected */
void TERM_WriteMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	/* Decide what to do depending of the positionof the state machine*/
	switch(statemachine->currentMenuParameter){
	case Option_param:

		statemachine->char_address[0] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;
		statemachine->currentMenuParameter = Address_param;
		break;

	case Address_param:
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 4) && UART_MailBoxData(uartChannel) != 10){

			statemachine->char_address[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 4) || (UART_MailBoxData(uartChannel) == 10)){
			statemachine->shift_counter = 0;
			statemachine->currentMenuParameter = Data_param;
			(*ftpr_Disp_Array[12])(uartChannel, &Struct_Char_R);
		}
		break;

	case Data_param:

		if ((UART_MailBoxData(uartChannel) == 13)){
			UART_putString(uartChannel, "\r\n[Enter]");
			UART_putString(uartChannel, "\r\nSu texto ha sido guardado!\r\nPresione cualquier tecla para continuar");
			statemachine->currentMenuParameter = Len_param;
			statemachine->address = 0;
		//what if we receive any other type of data
			} else {
				////

				if(statemachine->address < 0x7FFF){
				timeout_Enable();
				MEM_write(statemachine->address, UART_MailBoxData(uartChannel));
				timeout_Disable();
				statemachine->address += 8;
				}
			}

		break;

	case Len_param:
		UART_MailBoxData(uartChannel);
		statemachine->currentMenuParameter = Option_param;
		statemachine->currentMenu = MenuDisp;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.MemBusy = FALSE;

		break;
	}
}
/*Save the Time that the user write in the terminals*/
void TERM_WriteHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	if(statemachine->shift_counter < 8){
		Struct_Char_W.Time_Char[statemachine->shift_counter] =
				(((UART_MailBoxData(uartChannel) - '0') >= 0)
						&& ((UART_MailBoxData(uartChannel) - '0') <= 9) )?
								((UART_MailBoxData(uartChannel))):((UART_MailBoxData(uartChannel) == ':')?
										(':'):('1'));
		statemachine->shift_counter++;
	} else if((UART_MailBoxData(uartChannel) == 13) && (statemachine->shift_counter == 8)){
		UART_MailBoxData(uartChannel);
		Struct_Char_W.Time_Char[2] = ':';
		Struct_Char_W.Time_Char[5] = ':';
		Hour_Check(&Struct_Char_W ,&Struct_RTC_W);

		timeout_Enable();
		RTC_writeHour(&Struct_RTC_W);
		timeout_Disable();

		(*ftpr_Disp_Array[14])(uartChannel, &Struct_Char_R);

		statemachine->currentMenuParameter = Len_param;

		return;
	} else if(statemachine->currentMenuParameter == Len_param){
		UART_MailBoxData(uartChannel);
		statemachine->shift_counter = 0;
		statemachine->currentMenu = MenuDisp;
		statemachine->currentMenuParameter = Option_param;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.RTCBusy = FALSE;

	} else {
		UART_putString(uartChannel, "\r\nSe ha excedido del numero de caracteres,\r\n");
		UART_putString(uartChannel, "se ignorara el utimo caracter ... (Presione ENTER)");
	}
}

/*Save the Date that the user write in the terminals*/
void TERM_WriteDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	if(statemachine->shift_counter < 10){
			Struct_Char_W.Date_Char[statemachine->shift_counter] =
					(((UART_MailBoxData(uartChannel) - '0') >= 0)
							&& ((UART_MailBoxData(uartChannel) - '0') <= 9) )?
									((UART_MailBoxData(uartChannel))):((UART_MailBoxData(uartChannel) == '/')?
											('/'):('1'));
			statemachine->shift_counter++;

		} else if((UART_MailBoxData(uartChannel) == 13) && (statemachine->shift_counter == 10)){
			UART_MailBoxData(uartChannel);
			Struct_Char_W.Date_Char[2] = '/';
			Struct_Char_W.Date_Char[5] = '/';
			Date_Check(&Struct_Char_W ,&Struct_RTC_W);

			timeout_Enable();
			RTC_writeDate(&Struct_RTC_W);
			timeout_Disable();

			Struct_Char_R.Date_Char[6] = Struct_Char_W.Date_Char[6];
			Struct_Char_R.Date_Char[7] = Struct_Char_W.Date_Char[7];

			(*ftpr_Disp_Array[15])(uartChannel, &Struct_Char_R);

			statemachine->currentMenuParameter = Len_param;

			return;
		} else if(statemachine->currentMenuParameter == Len_param){
			UART_MailBoxData(uartChannel);
			statemachine->shift_counter = 0;
			statemachine->currentMenu = MenuDisp;
			statemachine->currentMenuParameter = Option_param;
			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
			TermHandler_StateMachine.RTCBusy = FALSE;

		} else {
			UART_putString(uartChannel, "\r\nSe ha excedido del numero de caracteres,\r\n");
			UART_putString(uartChannel, "se ignorara el utimo caracter ... (Presione ENTER)");
		}

}
/*Change the format of the time to be displayed*/
void TERM_WriteFormat(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	if((UART_MailBoxData(uartChannel) == 13)){

		statemachine->currentMenu = MenuDisp;
		statemachine->currentMenuParameter = Option_param;
		statemachine->shift_counter = 0;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.RTCBusy = FALSE;


	} else if(statemachine->shift_counter <= 1){
		statemachine->char_len[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;

	if(statemachine->shift_counter == 2){
		if((((statemachine->char_len[0] == 'S'))&&((statemachine->char_len[1] == 'i')))
				||(((statemachine->char_len[0] == 's'))&&((statemachine->char_len[1] == 'i')))
				||(((statemachine->char_len[0] == 'S'))&&((statemachine->char_len[1] == 'I')))){


			Struct_RTC_W.format = (Struct_RTC_W.format == 1)?(FALSE):(TRUE);
			RTC_changeFormat(&Struct_RTC_W);

			timeout_Enable();
		    RTC_readHour(&Struct_RTC_R);
		    timeout_Disable();

			UART_putString(uartChannel, "\r\nSe ha cambiado el formato, presione ENTER para continuar... \r\n");

		} else if((((statemachine->char_len[0] == 'N'))&&((statemachine->char_len[1] == 'o')))
				||(((statemachine->char_len[0] == 'n'))&&((statemachine->char_len[1] == 'o')))
				||(((statemachine->char_len[0] == 'N'))&&((statemachine->char_len[1] == 'O')))){

			UART_putString(uartChannel, "\r\n No se ha cambiado el formato, presione ENTER para continuar... \r\n");

		}

		}
	}
}
/*Prints the date and time in the LCD*/
void TERM_LCD(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	//What if [ESC]
	if((UART_MailBoxData(uartChannel) == 27)){

					//go back to Main menu
					statemachine->currentMenu = MenuDisp;
					statemachine->currentMenuParameter = Option_param;
					TermHandler_StateMachine.LCDBusy = FALSE;
					(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);


	//what if [ENTER]
				} else if ((UART_MailBoxData(uartChannel) == 13)){

					LCDNokia_clear();

					while(statemachine->f.tail != statemachine->f.head){

						Eco_Display(FIFO_POP(&statemachine->f));

					}
					UART_putString(uartChannel,"\r\n... Presione ESC para salir\r\n");
					FIFO_restart(&statemachine->f);

	//what if we receive any other type of data
				} else {
					FIFO_PUSH(&statemachine->f,UART_MailBoxData(uartChannel));
				}

}
/*Enable the comunication between terminals or alone*/
void TERM_communication(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	//What if [ESC]
	if((UART_MailBoxData(uartChannel) == 27)){

					//go back to Main menu
					statemachine->currentMenu = MenuDisp;
					statemachine->currentMenuParameter = Option_param;
					(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);

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
					UART_putString(uartChannel,"\r\n[ENTER]\r\n");
					FIFO_restart(&statemachine->f);

	//what if we receive any other type of data
				} else {
					FIFO_PUSH(&statemachine->f,UART_MailBoxData(uartChannel));
				}
}
/*read the value of the date */
void TERM_ReadDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;
	(*ftpr_Disp_Array[MenuDisp])(uartChannel, &Struct_Char_R);
	TermHandler_StateMachine.RTCBusy = FALSE;


}
/*read the value of the time */
void TERM_ReadHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;

	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
	TermHandler_StateMachine.RTCBusy = FALSE;

}
/*Prints the menu at both terminals*/
void TERM_MenuDisp(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	statemachine->data = (UART_MailBoxData(uartChannel)) - '0';
	if((statemachine->data >= 1) && (statemachine->data <= 9)
			&& (statemachine->currentMenuParameter == Option_param)){
		statemachine->currentMenu = statemachine->data;
	}

	if(((TermHandler_StateMachine.RTCBusy == TRUE)
			&& (statemachine->currentMenu >= SetHourDisp
					&& statemachine->currentMenu <= ReadDateDisp))
			||((TermHandler_StateMachine.MemBusy == TRUE)
					&& (statemachine->currentMenu >= ReadI2CDisp
							&& statemachine->currentMenu <= WriteI2CDisp))
							||((TermHandler_StateMachine.LCDBusy == TRUE)
									&& (statemachine->currentMenu == LCDDisp)) ){

		statemachine->currentMenu = MenuDisp;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		(*ftpr_Disp_Array[19])(uartChannel, &Struct_Char_R);

		return;
	}

	if(((statemachine->currentMenu >= SetHourDisp
						&& statemachine->currentMenu <= ReadDateDisp))){

		TermHandler_StateMachine.RTCBusy = TRUE;

	}

	if(((statemachine->currentMenu >= ReadI2CDisp
							&& statemachine->currentMenu <= WriteI2CDisp))){

			TermHandler_StateMachine.MemBusy = TRUE;
			}

	if((statemachine->currentMenu == LCDDisp)){

			TermHandler_StateMachine.LCDBusy = TRUE;
			}

	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);

	if(statemachine->currentMenu == CommunicationDisp){
	switch(statemachine->id){
				case '1':
					TermHandler_StateMachine.Term1Com = TRUE;
					if(TermHandler_StateMachine.Term2Com){
					UART_putString(UART_4, "\r\nLa terminal 1 se ha conectado ... \r\n");
					UART_putString(UART_0, "\r\nLa terminal 2 est� conectada ... \r\n");


					}
					break;

				case '2':
					TermHandler_StateMachine.Term2Com = TRUE;
					if(TermHandler_StateMachine.Term1Com){
					UART_putString(UART_4, "\r\nLa terminal 1 est� conectada ... \r\n");
					UART_putString(UART_0, "\r\nLa terminal 2 se ha conectado ... \r\n");
					}
					break;
				}
	}

}
/*inizilate the terminal 1 and return true when the function finish*/
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
/*inizilate the terminal 2 and return true when the function finish*/
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
/*Change the value of char into uint16*/
void Cast_Memory_param(Term_StateMachineType* statemachine){
	statemachine->address = 0;
	for(uint8 i=0;i<4;i++){
	statemachine->address |= ((((statemachine->char_address[i] - '0')>= 0) &&
			((statemachine->char_address[i] - '0') <= 9))?
					((statemachine->char_address[i] - '0'))
					:((((statemachine->char_address[i] - 'A')>= 0xA) &&
							((statemachine->char_address[i] - 'A') <= 0xF))?
									((statemachine->char_address[i] - 'A')):(0))) << (3-i)*4;

	}

	statemachine->len = 0;
	for(uint8 i=0;i<2;i++){
		statemachine->len |= ((((statemachine->char_len[i] - '0')>= 0) &&
				((statemachine->char_len[i] - '0') <= 9))?((statemachine->char_len[i] - '0')):(0)) << ((1-i)*4);
	}


}
/*Enable the interrupts for the terminals */
uint8 TERMHANDLER_init(){

	NVIC_enableInterruptAndPriority(PIT_CH0_IRQ, PRIORITY_11);

	NVIC_enableInterruptAndPriority(PIT_CH1_IRQ, PRIORITY_12);

	EnableInterrupts;


	PIT_clockGating();
	PIT_enable();
	PIT_delay(PIT_0,SYSTEM_CLOCK,2);
	PIT_timerInterruptEnable(PIT_0);
	PIT_timerEnable(PIT_0);

	TERM1_init();
	TERM2_init();

	timeout_Enable();
	RTC_write(0,0x80);
	timeout_Disable();

	(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);
	(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4, &Struct_Char_W);
}

/*Function called when a time out occurs, sets the flag and disables PIT1*/
void timeout_Ocurred(){
	timeout_flag = TRUE;
	PIT_timerInterruptDisable(PIT_1);
	PIT_timerDisable(PIT_1);
}

/** Function called before using I2C, to set a timer */
void timeout_Enable(){
	PIT_delay(PIT_1,SYSTEM_CLOCK,0.5);
	PIT_timerInterruptEnable(PIT_1);
	PIT_timerEnable(PIT_1);
}

/** Function called after using I2C, to disable the timer*/
void timeout_Disable(){

	//Check is timeout occured
	if(timeout_flag == TRUE){
		timeout_flag = FALSE;

		/** If si, notify users*/
		if(((Term1_StateMachine.currentMenu != CommunicationDisp)
				&&(Term1_StateMachine.currentMenu != LCDDisp))){
			Term1_StateMachine.currentMenu = MenuDisp;
			Term1_StateMachine.currentMenuParameter = Option_param;

			(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);
			(*ftpr_Disp_Array[18])(UART_0, &Struct_Char_W);

		}

		if(((Term2_StateMachine.currentMenu != CommunicationDisp)
				&&(Term2_StateMachine.currentMenu != LCDDisp))){
			Term2_StateMachine.currentMenu = MenuDisp;
			Term2_StateMachine.currentMenuParameter = Option_param;

			(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4, &Struct_Char_W);
			(*ftpr_Disp_Array[18])(UART_4, &Struct_Char_W);
		}

		timeout_notification = TRUE;

	}

	/** If not, continue*/
	if((Term1_StateMachine.currentMenu == MenuDisp) && (timeout_notification == FALSE)){
				(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);

			}

			if((Term2_StateMachine.currentMenu == MenuDisp) && (timeout_notification == FALSE)){

				(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4, &Struct_Char_W);

				timeout_notification = TRUE;

			}

	PIT_timerDisable(PIT_1);
	timeout_flag = FALSE;
}

uint8 timeout_Flag(){
	return timeout_flag;
}
