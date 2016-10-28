/*
 * TermHandler.c
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"

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
};

Term_StateMachineType Term1_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0,
		0,
		0,
		24
};

Term_StateMachineType Term2_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0,
		0,
		0,
		24
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
					//////Display data read
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
			(*ftpr_Disp_Array[statemachine->currentMenu])(uartChannel);
			break;

		case CommunicationDisp:
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

void TERM_menuDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Menu:\r\n");
	UART_putString(uartChannel,"1) Leer Memoria I2C\r\n");
	UART_putString(uartChannel,"2) Escribir Memoria I2C\r\n");
	UART_putString(uartChannel,"3) Establecer Hora\r\n");
	UART_putString(uartChannel,"4) Establecer Fecha\r\n");
	UART_putString(uartChannel,"5) Formato de hora\r\n");
	UART_putString(uartChannel,"6) Leer hora\r\n");
	UART_putString(uartChannel,"7) Leer fecha\r\n");
	UART_putString(uartChannel,"8) Comunicación terminales\r\n");
	UART_putString(uartChannel,"9) Eco en LCD\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La fecha actual es:\r\n");
	//date
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La hora actual es:\r\n");
	//hour
	UART_putString(uartChannel,"\r\n");
}

void TERM_readI2CDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Leer memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de lectura: \r\n");
}

void TERM_readI2CDisp2(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Longitud de Bytes: \r\n");

}

void TERM_readI2CDisp3(UART_ChannelType uartChannel){
	//longitud de bytes
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Contenido: \r\n");
	//contenido
	UART_putString(uartChannel,"Presione una tecla para continunar... \r\n");
}



void TERM_writeI2CDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de escritura: \r\n");
	//direccion de lectura
}

void TERM_writeI2CDisp2(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Texto a guardar: \r\n");
	//contenido
}

void TERM_writeI2CDisp3(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"Su texto ha sido guardado... \r\n");
}

void TERM_setHourDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer hora\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir hora en hh/mm/ss: \r\n");
}

void TERM_setHourDisp2(UART_ChannelType uartChannel){
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La hora ha sido cambiada... \r\n");
}

void TERM_setDateDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer fecha\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir fecha en dd/mm/aaaa: \r\n");
	//direccion de lectura
}

void TERM_setDateDisp2(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La fecha ha sido cambiada... \r\n");
}

void TERM_setHourFormatDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer formato de hora\r\n");
	UART_putString(uartChannel,"\r\n");

}

void TERM_readHourDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Hora actual:\r\n");
	//hora
	UART_putString(uartChannel,"\r\n");

}

void TERM_readDateDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Fecha actual:\r\n");
	//fecha
	UART_putString(uartChannel,"\r\n");

}

void TERM_communicationDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	//
	UART_putString(uartChannel,"\r\n");

}

void TERM_lcdDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	//
	UART_putString(uartChannel,"\r\n");

}
