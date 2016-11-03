/*
 * TermHandler.c
 *
 *	This function is the main file that is in charge of the system update,
 *	The functions of each menu, and the conditionals to verify that the
 *	options selected are right
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
#include "BTTN.h"

/** Struct that has the values for writing
 * in the RTC, as uint8*/
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

/** Struct that has the values for reading
 * from the RTC, as uint8*/
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

/** Struct that has the values for writing
 * in the RTC, as chars*/
RTC_CharArray Struct_Char_W = {
		"00:00:00 AM",
		"\0",
		"01/01/2000",
		"\0",
		1
};

/** Struct that has the values for reading
 * in the RTC, as chars*/
RTC_CharArray Struct_Char_R = {
		"00:00:00 AM",
		"\0",
		"01/01/2000",
		"\0",
		1
};

/** Function pointers array of each menu display in UART*/
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

/** Function pointers array of each menu option
 * functionality*/
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

/** Struct of state of the terminal 1*/
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

/** Struct of state of the terminal 2*/
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

/** Struct of state of the terminal handler*/
TermHandler_StateMachineType TermHandler_StateMachine = {
		FALSE, FALSE, FALSE, FALSE, FALSE
};

/** Flags in the terminal handler*/
static uint8 timeout_flag = FALSE;
static uint8 timeout_notification = FALSE;
static uint8 manual_mode = FALSE;
static uint8 manual_counter_hour = FALSE;
static uint8 manual_counter_date = FALSE;

/** Terminal handler update*/
uint8 TERM_upd(){

	/** Check if a data was received from the UART channel 0*/
	if(UART_MailBoxFlag(UART_0)){

	/** Set current id as terminal 1*/
	TermHandler_StateMachine.id = '1';

	/** Update current terminal with the input value*/
	(*ftpr_Update_Array[Term1_StateMachine.currentMenu])(UART_0, &Term1_StateMachine);

	}

	/** Check if a data was received from the UART channel 4*/
	if(UART_MailBoxFlag(UART_4)){

	/** Set current id as terminal 2*/
	TermHandler_StateMachine.id = '2';

	/** Update current terminal with the input value*/
	(*ftpr_Update_Array[Term2_StateMachine.currentMenu])(UART_4, &Term2_StateMachine);
	}

	/**Set current terminal as none*/
	TermHandler_StateMachine.id = '0';

	/** If the PIT counter overflowed == 1 sec has passed*/
	if(PIT_mailBoxFlag(PIT_0) == TRUE){

		/** Make a new reading of the RTC*/
		timeout_Enable();
		while(I2C_busy(I2C_0) == TRUE);
		RTC_newRead(&Struct_RTC_R, &Struct_Char_R);
		timeout_Disable();

		/**Check if its needed to refresh the UART displaying data*/
		if((Term1_StateMachine.currentMenu == ReadHourDisp)){
			(*ftpr_Disp_Array[16])(UART_0, &Struct_Char_R);
		} else if((Term1_StateMachine.currentMenu == ReadDateDisp)){
			(*ftpr_Disp_Array[17])(UART_0, &Struct_Char_R);
		}
		if((Term2_StateMachine.currentMenu == ReadHourDisp)){
			(*ftpr_Disp_Array[16])(UART_4, &Struct_Char_R);
		} else if((Term2_StateMachine.currentMenu == ReadDateDisp)){
			(*ftpr_Disp_Array[17])(UART_4, &Struct_Char_R);
		}

		/**Check if its needed to refresh the SPI displaying hour*/
		if((TermHandler_StateMachine.LCDBusy == FALSE) && (manual_mode == FALSE)){
		Info_Display(&Struct_Char_R);
		}
	}

	/** If a button was received*/
	if(BTTN_mailBoxFlag() == TRUE){
		Button_Hour();
	}
}

/** Read memory*/
void TERM_ReadMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){
	switch(statemachine->currentMenuParameter){
	case Option_param:

		/** The first readed values, is the first address data*/
		statemachine->char_address[0] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;
		statemachine->currentMenuParameter = Address_param;
		break;

		/** If we are receiving now the address*/
	case Address_param:

		/**Check that there wasn´t an enter, or we don't go pass the limit*/
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 4)){

			/*Receive the next data**/
			statemachine->char_address[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}

		/**If there was an enter, or we already have the 4 address characters*/
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 4)){

			/** Reset counter*/
			statemachine->shift_counter = 0;

			/** Change the current receiving parameter*/
			statemachine->currentMenuParameter = Len_param;
			(*ftpr_Disp_Array[10])(uartChannel, &Struct_Char_R);
		}
		break;

		/** If receiving the Len_param*/
	case Len_param:

		/**If data isn't enter, or counter isn't at the limit*/
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 2)){

			/**Store the new data*/
			statemachine->char_len[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}

		/** If enter or already 2 bytes*/
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 2)){

			/** Reset counter*/
			statemachine->shift_counter = 0;

			/** Current param, is data param (Key to go back to main menu)*/
			statemachine->currentMenuParameter = Data_param;
			(*ftpr_Disp_Array[11])(uartChannel, &Struct_Char_R);

			/** Cast memory and len parameters*/
			Cast_Memory_param(statemachine);

			/**Read all the data, according to len*/
			while(statemachine->len > 0){

				/** Read from Memory, and write in UART*/
				timeout_Enable();
				UART_putChar(uartChannel, MEM_read(statemachine->address));
				timeout_Disable();
				statemachine->len -= 1;
				statemachine->address += 8;
			}

			/** Reset address*/
			statemachine->address = 0;
			UART_putString(uartChannel, "\r\nPresione cualquier tecla para continuar... ");
		}

		break;

		/** if already wrote everything, wait for a key to go back to main menu*/
	case Data_param:
		UART_MailBoxData(uartChannel);
		statemachine->currentMenuParameter = Option_param;
		statemachine->currentMenu = MenuDisp;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.MemBusy = FALSE;

		break;
	}
}

/** Write in memory*/
void TERM_WriteMem(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	switch(statemachine->currentMenuParameter){

	/**If option param, the first thing we receive is the first byte of address*/
	case Option_param:

		statemachine->char_address[0] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;
		statemachine->currentMenuParameter = Address_param;
		break;

	/** Obtain the address bytes*/
	case Address_param:

		/** If address not complete, get new data*/
		if(UART_MailBoxData(uartChannel) != 13 && (statemachine->shift_counter != 4) && UART_MailBoxData(uartChannel) != 10){

			statemachine->char_address[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
			statemachine->shift_counter++;

		}

		/** If address complete, wait for writing data*/
		if((UART_MailBoxData(uartChannel) == 13) || (statemachine->shift_counter == 4) || (UART_MailBoxData(uartChannel) == 10)){
			statemachine->shift_counter = 0;
			statemachine->currentMenuParameter = Data_param;
			(*ftpr_Disp_Array[12])(uartChannel, &Struct_Char_R);
		}
		break;

	/** If Data_param, write the data*/
	case Data_param:

		/** If Enter, go back to main menu*/
		if ((UART_MailBoxData(uartChannel) == 13)){
			UART_putString(uartChannel, "\r\n[Enter]");
			UART_putString(uartChannel, "\r\nSu texto ha sido guardado!\r\nPresione cualquier tecla para continuar");
			statemachine->currentMenuParameter = Len_param;
			statemachine->address = 0;

		//what if we receive any other type of data, we write it in the memory
			} else {
				//// Expect if memory is 0x7FFF, then writting is not able
				if(statemachine->address < 0x7FFF){
				timeout_Enable();
				MEM_write(statemachine->address, UART_MailBoxData(uartChannel));
				timeout_Disable();
				statemachine->address += 8;
				}
			}

		break;

		/** If already wrote, and pressed enter, wait for a key to go back to main menu*/
	case Len_param:
		UART_MailBoxData(uartChannel);
		statemachine->currentMenuParameter = Option_param;
		statemachine->currentMenu = MenuDisp;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.MemBusy = FALSE;

		break;
	}
}

/** Write the hour*/
void TERM_WriteHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/** Receive data, until shift counter is 8*/
	if(statemachine->shift_counter < 8){

		/** If value in the range of 0 - 9, store*/
		Struct_Char_W.Time_Char[statemachine->shift_counter] =
				(((UART_MailBoxData(uartChannel) - '0') >= 0)
						&& ((UART_MailBoxData(uartChannel) - '0') <= 9) )?
								((UART_MailBoxData(uartChannel))):((UART_MailBoxData(uartChannel) == ':')?
										(':'):('1'));
		statemachine->shift_counter++;

		/** If already 8 and ENTER pressed, write the hour*/
	} else if((UART_MailBoxData(uartChannel) == 13) && (statemachine->shift_counter == 8)){
		UART_MailBoxData(uartChannel);
		Struct_Char_W.Time_Char[2] = ':';
		Struct_Char_W.Time_Char[5] = ':';
		Hour_Check(&Struct_Char_W ,&Struct_RTC_W);

		/** Write the hour*/
		timeout_Enable();
		RTC_writeHour(&Struct_RTC_W);
		timeout_Disable();

		(*ftpr_Disp_Array[14])(uartChannel, &Struct_Char_R);
		statemachine->currentMenuParameter = Len_param;

		return;

		/** If ENTER obtained, go back to main menu*/
	} else if(statemachine->currentMenuParameter == Len_param){
		UART_MailBoxData(uartChannel);
		statemachine->shift_counter = 0;
		statemachine->currentMenu = MenuDisp;
		statemachine->currentMenuParameter = Option_param;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.RTCBusy = FALSE;

		/** If ENTER not obtaind, warn the user of character excedeed*/
	} else {
		UART_putString(uartChannel, "\r\nSe ha excedido del numero de caracteres,\r\n");
		UART_putString(uartChannel, "se ignorara el utimo caracter ... (Presione ENTER)");
	}
}

/** Write the date*/
void TERM_WriteDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/** Receive date param*/
	if(statemachine->shift_counter < 10){
			Struct_Char_W.Date_Char[statemachine->shift_counter] =
					(((UART_MailBoxData(uartChannel) - '0') >= 0)
							&& ((UART_MailBoxData(uartChannel) - '0') <= 9) )?
									((UART_MailBoxData(uartChannel))):((UART_MailBoxData(uartChannel) == '/')?
											('/'):('1'));
			statemachine->shift_counter++;

			/** Write the date in RTC*/
		} else if((UART_MailBoxData(uartChannel) == 13) && (statemachine->shift_counter == 10)){
			UART_MailBoxData(uartChannel);
			Struct_Char_W.Date_Char[2] = '/';
			Struct_Char_W.Date_Char[5] = '/';
			Date_Check(&Struct_Char_W ,&Struct_RTC_W);

			timeout_Enable();
			RTC_writeDate(&Struct_RTC_W);
			timeout_Disable();

			/** Save the first to bytes of year*/
			Struct_Char_R.Date_Char[6] = Struct_Char_W.Date_Char[6];
			Struct_Char_R.Date_Char[7] = Struct_Char_W.Date_Char[7];

			(*ftpr_Disp_Array[15])(uartChannel, &Struct_Char_R);

			statemachine->currentMenuParameter = Len_param;

			return;

			/** If ENTER obtained, go back to main menu*/
		} else if(statemachine->currentMenuParameter == Len_param){
			UART_MailBoxData(uartChannel);
			statemachine->shift_counter = 0;
			statemachine->currentMenu = MenuDisp;
			statemachine->currentMenuParameter = Option_param;
			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
			TermHandler_StateMachine.RTCBusy = FALSE;

			/**If ENTER not obtained, warn user of limit excedeed*/
		} else {
			UART_putString(uartChannel, "\r\nSe ha excedido del numero de caracteres,\r\n");
			UART_putString(uartChannel, "se ignorara el utimo caracter ... (Presione ENTER)");
		}

}

/** Write the format of hour*/
void TERM_WriteFormat(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/**If enter, go back to main menu*/
	if((UART_MailBoxData(uartChannel) == 13)){

		statemachine->currentMenu = MenuDisp;
		statemachine->currentMenuParameter = Option_param;
		statemachine->shift_counter = 0;
		(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
		TermHandler_StateMachine.RTCBusy = FALSE;

	/**Store user's answer*/
	} else if(statemachine->shift_counter <= 1){
		statemachine->char_len[statemachine->shift_counter] = (UART_MailBoxData(uartChannel));
		statemachine->shift_counter++;

	/**Check if SI or NOT received*/
	if(statemachine->shift_counter == 2){
		if((((statemachine->char_len[0] == 'S'))&&((statemachine->char_len[1] == 'i')))
				||(((statemachine->char_len[0] == 's'))&&((statemachine->char_len[1] == 'i')))
				||(((statemachine->char_len[0] == 'S'))&&((statemachine->char_len[1] == 'I')))){


			/** If SI, change format*/
			Struct_RTC_W.format = (Struct_RTC_W.format == 1)?(FALSE):(TRUE);
			RTC_changeFormat(&Struct_RTC_W);

			timeout_Enable();
		    RTC_readHour(&Struct_RTC_R);
		    timeout_Disable();

			UART_putString(uartChannel, "\r\nSe ha cambiado el formato, presione ENTER para continuar... \r\n");

		} else if((((statemachine->char_len[0] == 'N'))&&((statemachine->char_len[1] == 'o')))
				||(((statemachine->char_len[0] == 'n'))&&((statemachine->char_len[1] == 'o')))
				||(((statemachine->char_len[0] == 'N'))&&((statemachine->char_len[1] == 'O')))){


			/** If NO, do not change format*/
			UART_putString(uartChannel, "\r\n No se ha cambiado el formato, presione ENTER para continuar... \r\n");

		}

		}
	}
}

/** LCD Echo*/
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

					/**Send data*/
					while(statemachine->f.tail != statemachine->f.head){

						Eco_Display(FIFO_POP(&statemachine->f));

					}
					UART_putString(uartChannel,"\r\n... Presione ESC para salir\r\n");
					FIFO_restart(&statemachine->f);

	//what if we receive any other type of data, store it in FIFO
				} else {
					FIFO_PUSH(&statemachine->f,UART_MailBoxData(uartChannel));
				}

}

/** Term communication*/
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

/**Read the date*/
void TERM_ReadDate(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/** If key pressed, go back to main menu*/
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;
	(*ftpr_Disp_Array[MenuDisp])(uartChannel, &Struct_Char_R);
	TermHandler_StateMachine.RTCBusy = FALSE;


}

/**Read the hour*/
void TERM_ReadHour(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/** If key pressed, go back to main menu*/
	UART_MailBoxData(uartChannel);
	statemachine->currentMenuParameter = Option_param;
	statemachine->currentMenu = MenuDisp;
	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);
	TermHandler_StateMachine.RTCBusy = FALSE;

}

/**Menu Display*/
void TERM_MenuDisp(UART_ChannelType uartChannel, Term_StateMachineType* statemachine){

	/**If data, in the range 0 to 9, use it*/
	statemachine->data = (UART_MailBoxData(uartChannel)) - '0';
	if((statemachine->data >= 1) && (statemachine->data <= 9)
			&& (statemachine->currentMenuParameter == Option_param)){
		statemachine->currentMenu = statemachine->data;
	}

	/** Check if menu is available*/
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

	/** If the RTC is about to be used, set RTCBusy*/
	if(((statemachine->currentMenu >= SetHourDisp
						&& statemachine->currentMenu <= ReadDateDisp))){

		TermHandler_StateMachine.RTCBusy = TRUE;

	}

	/** If the MEM is about to be used, set MemBusy*/
	if(((statemachine->currentMenu >= ReadI2CDisp
							&& statemachine->currentMenu <= WriteI2CDisp))){

			TermHandler_StateMachine.MemBusy = TRUE;
			}

	/** If the LCD is about to be used, set LCDBusy*/
	if((statemachine->currentMenu == LCDDisp)){

			TermHandler_StateMachine.LCDBusy = TRUE;
			}

	/** Refresh UART display*/
	(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel, &Struct_Char_R);

	/** Check communication conditionals*/
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

/**Init term 1*/
uint8 TERM1_init(){

	/** Init UART_4*/
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOB, BIT16, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT17, &pinControlRegister);

	UART_init(UART_0, SYSTEM_CLOCK, BD_9600, BRFA_19);
	UART0_interruptEnable(UART_0);
	NVIC_enableInterruptAndPriority(UART0_IRQ, PRIORITY_10);

	return TRUE;
}

/**Init term 2*/
uint8 TERM2_init(){

	/** Init UART_0*/
	GPIO_clockGating(GPIOC);
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOC, BIT14, &pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT15, &pinControlRegister);

	UART_init(UART_4, SYSTEM_CLOCK, BD_9600, BRFA_19);
	UART0_interruptEnable(UART_4);
	NVIC_enableInterruptAndPriority(UART4_IRQ, PRIORITY_10);

	return TRUE;
}

/**Transform Address and len param, from char to uint8*/
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

/***Init the TERM Handler*/
uint8 TERMHANDLER_init(){


	/**Init PIT channels*/
	NVIC_enableInterruptAndPriority(PIT_CH0_IRQ, PRIORITY_11);
	NVIC_enableInterruptAndPriority(PIT_CH1_IRQ, PRIORITY_12);
	EnableInterrupts;
	PIT_clockGating();
	PIT_enable();
	PIT_delay(PIT_0,SYSTEM_CLOCK,2);
	PIT_timerInterruptEnable(PIT_0);
	PIT_timerEnable(PIT_0);

	/**Init terminals*/
	TERM1_init();
	TERM2_init();

	/**Make sure the RTC is running (time is running)*/
	timeout_Enable();
	RTC_write(0,0x80);
	timeout_Disable();

	/** Display menu in terminals*/
	(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);
	(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4, &Struct_Char_W);
}

/** If an timeout ocurred, set the flag, and disable the PIT 1*/
void timeout_Ocurred(){
	timeout_flag = TRUE;
	PIT_timerInterruptDisable(PIT_1);
	PIT_timerDisable(PIT_1);
}

/** Enable the PIT 1*/
void timeout_Enable(){
	PIT_delay(PIT_1,SYSTEM_CLOCK,0.5);
	PIT_timerInterruptEnable(PIT_1);
	PIT_timerEnable(PIT_1);
}

/** Disable the timeout checking*/
void timeout_Disable(){

	/** If timeout ocurred*/
	if(timeout_flag == TRUE){

		/** clear flag*/
		timeout_flag = FALSE;

		/** go to main menu, if we are in an unaffected menu*/
		if(((Term1_StateMachine.currentMenu != CommunicationDisp)
				&&(Term1_StateMachine.currentMenu != LCDDisp))){

			/**If we are in a menu that uses I2C, warn user*/
			Term1_StateMachine.currentMenu = MenuDisp;
			Term1_StateMachine.currentMenuParameter = Option_param;

			(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);
			(*ftpr_Disp_Array[18])(UART_0, &Struct_Char_W);

		}

		/**Make sure we have notified the user*/
		timeout_notification = TRUE;

	}

	/**If we are in the main menu, and we haven't notify the user, notify the user in terminal 1*/
	if((Term1_StateMachine.currentMenu == MenuDisp) && (timeout_notification == FALSE)){
				(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0, &Struct_Char_W);

			}

	/**If we are in the main menu, and we haven't notify the user, notify the user in terminal 2*/
			if((Term2_StateMachine.currentMenu == MenuDisp) && (timeout_notification == FALSE)){

				(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4, &Struct_Char_W);

				timeout_notification = TRUE;

			}

	/*Disable PIT 1*/
	PIT_timerDisable(PIT_1);
	timeout_flag = FALSE;
}

/**Read timeout flag*/
uint8 timeout_Flag(){
	return timeout_flag;
}

/**Button Hour menu*/
void Button_Hour(){

	/**If LCD and RTC is busy, and we aren'r using it, leave the function*/
	if(((TermHandler_StateMachine.RTCBusy == FALSE)
			&& (TermHandler_StateMachine.LCDBusy == FALSE)) || (manual_mode == TRUE)){

		/**Else, use the RTC and LCD*/
		TermHandler_StateMachine.RTCBusy = TRUE;
		TermHandler_StateMachine.LCDBusy = TRUE;

		/**Make sure we are in manual mode*/
		if(manual_mode == FALSE){
		manual_mode = TRUE;

		/**Display the button hour and date change menu*/
		Button_Display(&Struct_Char_W);

		/**Clear flag*/
		BTTN_mailBoxData();

		/**Reset counters*/
		manual_counter_hour = 0;
		manual_counter_date = 0;
		return;

		/**Else, check the data*/
		} else{
			switch(BTTN_mailBoxData()){

			/**If BUTTON 0, add in the current param*/
			case BUTTON_0:
				if(manual_counter_hour >= 8){
					return;
				}
				if(((Struct_Char_W.Time_Char[manual_counter_hour]) + 1) <= '9'){
					Struct_Char_W.Time_Char[manual_counter_hour] += 1;
				}
				break;

				/**If BUTTON 1, substract in the current param*/
			case BUTTON_1:
				if(manual_counter_hour >= 8){
					return;
				}
				if((Struct_Char_W.Time_Char[manual_counter_hour] - 1) >= '0'){
					Struct_Char_W.Time_Char[manual_counter_hour] -= 1;
				}
				break;

				/**If BUTTON 2, set current param, and move to the next one*/
			case BUTTON_2:

				manual_counter_hour++;
				if((manual_counter_hour == 2) || (manual_counter_hour == 5)){
					manual_counter_hour++;
				}
				if(manual_counter_hour >= 8){
					manual_counter_hour = 8;
				}

				break;

				/**If BUTTON 3, added in the current param*/
			case BUTTON_3:
				if(manual_counter_date >= 10){
					manual_counter_date = 10;
				}
				if((Struct_Char_W.Date_Char[manual_counter_date] + 1) <= '9'){
					Struct_Char_W.Date_Char[manual_counter_date] += 1;
				}
				break;

				/**If BUTTON 4, substract in the current param*/
			case BUTTON_4:
				if(manual_counter_date >= 10){
					manual_counter_date = 10;
				}
				if((Struct_Char_W.Date_Char[manual_counter_date] - 1) >= '0'){
					Struct_Char_W.Date_Char[manual_counter_date] -= 1;
				}
				break;

				/**If BUTTON 5, set current param, and move to the next one*/
			case BUTTON_5:

				manual_counter_date++;
				if((manual_counter_date == 2) || (manual_counter_date == 5)){
					manual_counter_date++;
				}
				if(manual_counter_date >= 10){
					manual_counter_date = 10;
				}

				break;

			default:
				break;
			}

			/**Display changes in LCD*/
			Button_Display(&Struct_Char_W);

		}

		/**If already change all the parameters, write in RTC*/
		if((manual_counter_date == 10) && (manual_counter_hour == 8)){
			Hour_Check(&Struct_Char_W,&Struct_RTC_W);
			Date_Check(&Struct_Char_W,&Struct_RTC_W);
			timeout_Enable();
			RTC_writeHour(&Struct_RTC_W);
			timeout_Disable();

			timeout_Enable();
			RTC_writeDate(&Struct_RTC_W);
			timeout_Disable();

		/**Free LCD and RTC usage*/
		TermHandler_StateMachine.RTCBusy = FALSE;
		TermHandler_StateMachine.LCDBusy = FALSE;
		manual_mode = FALSE;


		}

	}

}
