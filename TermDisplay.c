/*
 * TermDisplay.c
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"
#include "TermDisplay.h"
#include "MCP7940M.h"

RTC_ConfigType Struct_RTC = {
		6,
		41,
		17,
		22,
		0,
		18,
		17,
		16
};

RTC_CharArray Struct_Char = {
		"00:00:00 AM",
		"\0",
		"2000/01/01",
		"\0"
};

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
    RTC_readDate(&Struct_RTC);
    Cast_Date(&Struct_RTC, &Struct_Char);
	UART_putString(uartChannel, Struct_Char.Date_Char);
	UART_putString(uartChannel,"\r\n");
    RTC_readHour(&Struct_RTC);
    Cast_Time(&Struct_RTC, &Struct_Char);
	UART_putString(uartChannel,"La hora actual es:\r\n");
	UART_putString(uartChannel, Struct_Char.Time_Char);
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
    RTC_readHour(&Struct_RTC);
    Cast_Time(&Struct_RTC, &Struct_Char);
	UART_putString(uartChannel, Struct_Char.Time_Char);
	UART_putString(uartChannel,"\r\n");

}

void TERM_readDateDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Fecha actual:\r\n");
    RTC_readDate(&Struct_RTC);
    Cast_Date(&Struct_RTC, &Struct_Char);
	UART_putString(uartChannel, Struct_Char.Date_Char);
	UART_putString(uartChannel,"\r\n");

}

void TERM_communicationDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel, "Comunicación entre terminales");
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

