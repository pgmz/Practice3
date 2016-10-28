/*
 * TermHandler.c
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"

ftpr_Disp ftpr_Disp_Array[9] = {
		&TERM_menuDisp,
		&TERM_readI2CDisp,
		&TERM_writeI2CDisp,
		&TERM_setHourDisp,
		&TERM_setDateDisp,
		&TERM_setHourFormatDisp,
		&TERM_readHourDisp,
		&TERM_readDateDisp,
		&TERM_communicationDisp
};

Term_StateMachineType Term1_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0
};

Term_StateMachineType Term2_StateMachine = {
		MenuDisp,
		Option_param,
		0x0,
		0
};

uint8 TERMHANDLER_init(){

	TERM1_init();
	TERM2_init();
	(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0);
	(*ftpr_Disp_Array[Term2_StateMachine.currentMenu])(UART_4);

}

/**
 * 	MenuDisp = 0,
	ReadI2CDisp,
	WriteI2CDisp,
	SetHourDisp,
	SetDateDisp,
	SetHourFormatDisp,
	ReadHourDisp,
	ReadDateDisp,
	CommunicationDisp
 * */

void TERM1_upd(){
	if(UART_MailBoxFlag(UART_0)){
		switch(Term1_StateMachine.currentMenu){
		case MenuDisp:
			Term1_StateMachine.data = (UART_MailBoxData(UART_0)) - '0';

			if((Term1_StateMachine.data >= 1) && (Term1_StateMachine.data <= 9)
					&& (Term1_StateMachine.currentMenuParameter == Option_param)){
				Term1_StateMachine.currentMenu = Term1_StateMachine.data;
			}

			break;

		case ReadI2CDisp:

			break;

		case WriteI2CDisp:
			break;

		case SetHourDisp:
			break;

		case SetDateDisp:
			break;

		case SetHourFormatDisp:
			break;

		case ReadHourDisp:
			break;

		case ReadDateDisp:
			break;

		case CommunicationDisp:
			break;
		}

		(*ftpr_Disp_Array[Term1_StateMachine.currentMenu])(UART_0);
	}
	return;



}

void TERM2_upd(){
	if(UART_MailBoxFlag(UART_4)){

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
	TERM1_upd();
	TERM2_upd();
}

void TERM_menuDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
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

void TERM_readI2CDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Leer memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de lectura: \r");
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Longitud de Bytes: \r");
	//longitud de bytes
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Contenido: \r\n");
	//contenido
	UART_putString(uartChannel,"Presione una tecla para continunar... \r");
}

void TERM_writeI2CDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de escritura: \r");
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Texto a guardar: \r\n");
	//contenido
	UART_putString(uartChannel,"Su texto ha sido guardado... \r");
}

void TERM_setHourDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer hora\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir hora en hh/mm/ss: \r");
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La hora ha sido cambiada... \r");
}

void TERM_setDateDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer fecha\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir fecha en dd/mm/aaaa: \r");
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La fecha ha sido cambiada... \r");
}

void TERM_setHourFormatDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer formato de hora\r\n");
	UART_putString(uartChannel,"\r\n");

}

void TERM_readHourDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Hora actual:\r\n");
	//hora
	UART_putString(uartChannel,"\r\n");

}

void TERM_readDateDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Fecha actual:\r\n");
	//fecha
	UART_putString(uartChannel,"\r\n");

}

void TERM_communicationDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	//
	UART_putString(uartChannel,"\r\n");

}
