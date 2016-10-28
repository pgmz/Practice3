/*
 * TermHandler.c
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"

Term_MenuDisplayPointerType Term_MenuDisplayPointer = {

};

Term_StateMachineType Term_StateMachine = {
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
};

Term_TXRXStateMachineType Term1_TXRXStateMachine = {
		MenuDisp,
		FALSE,
		Option_param
};

Term_TXRXStateMachineType Term2_TXRXStateMachine = {
		MenuDisp,
		FALSE,
		Option_param
};

uint8 TERMHANDLER_init(){


	TERM2_init();
	TERM_menuDisp(UART_4);
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


void TERM2_display(){

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
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Leer memoria I2C\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Dirección de lectura: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Longitud de Bytes: \r");
	//longitud de bytes
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Contenido: \r\n");
	//contenido
	UART_putString(UART_4,"Presione una tecla para continunar... \r");
}

void TERM_writeI2CDisp(UART_ChannelType uartChannel){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Escribir memoria I2C\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Dirección de escritura: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Texto a guardar: \r\n");
	//contenido
	UART_putString(UART_4,"Su texto ha sido guardado... \r");
}

void TERM_setHourDisp(UART_ChannelType uartChannel){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer hora\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Escribir hora en hh/mm/ss: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La hora ha sido cambiada... \r");
}

void TERM_setDateDisp(UART_ChannelType uartChannel){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer fecha\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Escribir fecha en dd/mm/aaaa: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La fecha ha sido cambiada... \r");
}

void TERM_setHourFormatDisp(UART_ChannelType uartChannel){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer formato de hora\r\n");
	UART_putString(UART_4,"\r\n");

}


uint8 TERM1_init(){
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOB, BIT16, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT17, &pinControlRegister);

	UART_init(UART_0, SYSTEM_CLOCK, BD_9600, 19);
	UART0_interruptEnable(UART_0);
	NVIC_enableInterruptAndPriority(UART0_IRQ, PRIORITY_11);

	return TRUE;
}


void TERM1_menuDisp(){
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in black and background in white*/
	UART_putString(UART_0,"\033[0;37;40m");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0, "Comunicacion por UART e I2C\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[02;01H");
	UART_putString(UART_0, "Opciones:\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[04;10H");
	UART_putString(UART_0, "1) Leer Memoria I2C\r");
	UART_putString(UART_0,"\033[05;10H");
	UART_putString(UART_0, "2) Escribir Memoria I2C\r");
	UART_putString(UART_0,"\033[06;10H");
	UART_putString(UART_0, "3) Escribir hora:\r");
	UART_putString(UART_0,"\033[07;10H");
	UART_putString(UART_0, "4) Escribir fecha:\r");
	UART_putString(UART_0,"\033[08;10H");
	UART_putString(UART_0, "5) Formato de hora:\r");
	UART_putString(UART_0,"\033[09;10H");
	UART_putString(UART_0, "6) Leer hora:\r");
	UART_putString(UART_0,"\033[10;10H");
	UART_putString(UART_0, "7) Leer fecha:\r");
	UART_putString(UART_0,"\033[11;10H");
	UART_putString(UART_0, "8) Comunicacion con terminal 2:\r");
	UART_putString(UART_0,"\033[12;10H");
	UART_putString(UART_0, "9) ECO en LCD:\r");
	UART_putString(UART_0,"\033[14;10H");
	UART_putString(UART_0,"La fecha actual es:\r\n");
	UART_putString(UART_0,"\033[16;10H");
	UART_putString(UART_0,"La hora actual es:\r\n");

	if(UART0_MailBox.flag){
		/**Sends to the PCA the received data in the mailbox*/
		//UART_putChar(UART_0, UART0_MailBox.mailBox);
		swithcMenu(UART0_MailBox.mailBox);
		/**clear the reception flag*/
		UART0_MailBox.flag =0;
	}

	//swithcMenu(UART0_MailBox.mailBox);
}

void TERM1_readI2CDisp(){
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"***Comunicación por UART e I2C***\r");
	UART_putString(UART_0,"\033[02;01H");
	UART_putString(UART_0,"Leer memoria I2C\r");
	UART_putString(UART_0,"\033[03;01H");
	UART_putString(UART_0,"Dirección de lectura: \r");
	//direccion de lectura
	UART_putString(UART_0,"\033[04;01H");
	UART_putString(UART_0,"Longitud de Bytes: \r");
	//longitud de bytes
	UART_putString(UART_0,"\033[05;01H");
	UART_putString(UART_0,"Contenido: \r");
	//contenido
	UART_putString(UART_0,"\033[06;01H");
	UART_putString(UART_0,"Presione una tecla para continunar... \r");
}

void TERM1_writeI2CDisp(){
	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_0,"\033[02;01H");
	UART_putString(UART_0,"Escribir memoria I2C\r\n");
	UART_putString(UART_0,"\033[03;01H");
	UART_putString(UART_0,"Dirección de escritura: \r");
	//direccion de lectura
	UART_putString(UART_0,"\033[04;01H");
	UART_putString(UART_0,"Texto a guardar: \r");
	//contenido
	UART_putString(UART_0,"\033[05;01H");
	UART_putString(UART_0,"Su texto ha sido guardado... \r");
}

void TERM1_setHourDisp(){
	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"***Comunicación por UART e I2C***\r");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"Establecer hora\r");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"Escribir hora en hh/mm/ss: \r");
	//direccion de lectura
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"La hora ha sido cambiada... \r");
}

void TERM1_setDateDisp(){
	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"***Comunicación por UART e I2C***\r");
	UART_putString(UART_0,"\033[02;01H");
	UART_putString(UART_0,"Establecer fecha\r");
	UART_putString(UART_0,"\033[03;01H");
	UART_putString(UART_0,"Escribir fecha en dd/mm/aaaa: \r");
	//direccion de lectura
	UART_putString(UART_0,"\033[04;01H");
	UART_putString(UART_0,"La fecha ha sido cambiada... \r");
}

void TERM1_setHourFormatDisp(){
	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0,"Establecer formato de hora\r\n");

}

