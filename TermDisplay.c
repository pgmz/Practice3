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
		"01/01/2000",
		"\0"
};

void TERM_menuDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
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

}

void TERM_readI2CDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Leer memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de lectura: \r\n");
	UART_putString(uartChannel, "0X");
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
	//UART_putString(uartChannel,"Presione una tecla para continunar... \r\n");
}



void TERM_writeI2CDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de escritura: \r\n");
	UART_putString(uartChannel, "0X");

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
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer hora\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir hora en hh:mm:ss : \r\n");
}

void TERM_setHourDisp2(UART_ChannelType uartChannel){
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"La hora ha sido cambiada... \r\n");
}

void TERM_setDateDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
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
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer formato de hora\r\n");
	UART_putString(uartChannel,"\r\n");
	if(Struct_RTC.format == TRUE){
		UART_putString(uartChannel,"El formato actual es de 12 horas\r\n");
		UART_putString(uartChannel,"Cambiar a formato de 24 horas? Si/No \r\n");
	} else if(Struct_RTC.format == FALSE){
		UART_putString(uartChannel,"El formato actual es de 24 horas\r\n");
		UART_putString(uartChannel,"Cambiar a formato de 12 horas? Si/No \r\n");
	}

}

void TERM_readHourDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Hora actual:\r\n");
	TERM_readHourDisp1(uartChannel);
	UART_putString(UART_0, "\r\n... Presione cualquier tecla para continuar... \r\n");
}

void TERM_readHourDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel, "\033[4;0H");
	UART_putString(uartChannel, Struct_Char.Time_Char);
}


void TERM_readDateDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Fecha actual:\r\n");
	TERM_readDateDisp1(uartChannel);
	UART_putString(UART_0, "\r\n... Presione cualquier tecla para continuar... \r\n");
}

void TERM_readDateDisp1(UART_ChannelType uartChannel){
	UART_putString(uartChannel, "\033[4;0H");
	UART_putString(uartChannel, Struct_Char.Date_Char);
}


void TERM_communicationDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel, "Comunicación entre terminales");
	UART_putString(uartChannel,"\r\n");

}

void TERM_lcdDisp(UART_ChannelType uartChannel){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[0;30;47m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	//
	UART_putString(uartChannel,"\r\n");

}

void RTC_newRead(){
    RTC_readHour(&Struct_RTC);
    RTC_readDate(&Struct_RTC);
    Cast_Time(&Struct_RTC, &Struct_Char);
    Cast_Date(&Struct_RTC, &Struct_Char);
}

void RTC_changeFormat(uint8 format){
    RTC_readHour(&Struct_RTC);
	Struct_RTC.format = format;
    RTC_writeHour(&Struct_RTC);

}

void Date_Check(RTC_CharArray* struct_char ,RTC_ConfigType* struct_config){
	//		"01/01/2000",

	Struct_Char.Date_Char[6] = struct_char->Date_Char[6];
	Struct_Char.Date_Char[7] = struct_char->Date_Char[7];

	struct_config->year = ((struct_char->Date_Char[8] - '0') << 4) | ((struct_char->Date_Char[9] - '0'));
	struct_config->month = ((struct_char->Date_Char[3] - '0') << 4) | ((struct_char->Date_Char[4] - '0'));
	struct_config->date = (((struct_char->Date_Char[0] - '0') << 4) | ((struct_char->Date_Char[1] - '0')));

	if((struct_config->month <= 0) && (struct_config->month >= 13)){
		struct_config->month = 1;
	}

	if((struct_config->date <= 0) && (struct_config->date >= 32)){
		struct_config->month = 1;
	}

}

void Hour_Check(RTC_CharArray* struct_char ,RTC_ConfigType* struct_config){

	struct_config->hour = ((struct_char->Time_Char[0] - '0') << 4) | ((struct_char->Time_Char[1] - '0'));
	struct_config->minute = ((struct_char->Time_Char[3] - '0') << 4) | ((struct_char->Time_Char[4] - '0'));
	struct_config->second = (((struct_char->Time_Char[6] - '0') << 4) | ((struct_char->Time_Char[7] - '0')) | 0x80);

	if((struct_config->hour >= 0x13) && (struct_config->format == TRUE)){
		struct_config->hour = (struct_config->hour - 0x12)|(0x40);
	}


}
