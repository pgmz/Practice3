/*
 * TermHandler.c
 *
 *  Created on: 21/10/2016
 *      Author: Patricio Gomez
 */


uint8 TERM2_init(){
	GPIO_clockGating(GPIOC);
	GPIO_pinControlRegisterType = GPIO_MUX3;
	GPIO_pinControlRegister(GPIOC, BIT14, &GPIO_pinControlRegister);
	GPIO_pinControlRegister(GPIOC, BIT15, &GPIO_pinControlRegister);

	UART_init(UART_4, SYSTEM_CLOCK, BD_9600, 19);
	UART0_interruptEnable(UART_4);
	NVIC_enableInterruptAndPriority(UART4_IRQ, PRIORITY_10);

	return TRUE;
}


void TERM2_display(){

}

void TERM_menuDisp(){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Menu:\r\n");
	UART_putString(UART_4,"1) Leer Memoria I2C\r\n");
	UART_putString(UART_4,"2) Escribir Memoria I2C\r\n");
	UART_putString(UART_4,"3) Establecer Hora\r\n");
	UART_putString(UART_4,"4) Establecer Fecha\r\n");
	UART_putString(UART_4,"5) Formato de hora\r\n");
	UART_putString(UART_4,"6) Leer hora\r\n");
	UART_putString(UART_4,"7) Leer fecha\r\n");
	UART_putString(UART_4,"8) Comunicación terminales\r\n");
	UART_putString(UART_4,"9) Eco en LCD\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La fecha actual es:\r\n");
	//date
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La hora actual es:\r\n");
	//hour
	UART_putString(UART_4,"\r\n");
}

void TERM_readI2CDisp(){
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

void TERM_writeI2CDisp(){
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

void TERM_setHourDisp(){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer hora\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Escribir hora en hh/mm/ss: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La hora ha sido cambiada... \r");
}

void TERM_setDateDisp(){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer fecha\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Escribir fecha en dd/mm/aaaa: \r");
	//direccion de lectura
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"La fecha ha sido cambiada... \r");
}

void TERM_setHourFormatDisp(){
	UART_putString(UART_4,"***Comunicación por UART e I2C***\r\n");
	UART_putString(UART_4,"\r\n");
	UART_putString(UART_4,"Establecer formato de hora\r\n");
	UART_putString(UART_4,"\r\n");

}
