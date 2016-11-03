/*
 * TermDisplay.c
 *
 *	This file has all the "graphic" part of the UART for sending stuff.
 *	Has the strings in order to display the menus, and do the RTC read
 *	data transformation, for displaying
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#include "TermHandler.h"
#include "TermDisplay.h"
#include "MCP7940M.h"

/** Write in the uartChannel, the Main menu*/
void TERM_menuDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
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

/** Write in the uartChannel the first text for reading the memory*/
void TERM_readI2CDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Leer memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de lectura: \r\n");
	UART_putString(uartChannel, "0X");
}

/** Write in the uartChannel the second text for reading the memory*/
void TERM_readI2CDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Longitud de Bytes: \r\n");

}

/** Write in the uartChannel the third text for reading the memory*/
void TERM_readI2CDisp3(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Contenido: \r\n");
}

/** Write in the uartChannel the first text for writting in the memory*/
void TERM_writeI2CDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir memoria I2C\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Dirección de escritura: \r\n");
	UART_putString(uartChannel, "0X");
}

/** Write in the uartChannel the second text for writting in the memory*/
void TERM_writeI2CDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Texto a guardar: \r\n");
}

/** Write in the uartChannel the third text for writting in the memory*/
void TERM_writeI2CDisp3(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,":D Su texto ha sido guardado!... \r\n");
}

/** Write in the uartChannel the first text for writting the hour in the RTC*/
void TERM_setHourDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer hora\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir hora en hh:mm:ss : \r\n");
}

/** Write in the uartChannel the second text for writting the hour in the RTC*/
void TERM_setHourDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	//direccion de lectura
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,":D La hora ha sido cambiada!... \r\n");
}

/** Write in the uartChannel the first text for writting the date in the RTC*/
void TERM_setDateDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer fecha\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Escribir fecha en dd/mm/aaaa: \r\n");
	//direccion de lectura
}

/** Write in the uartChannel the second text for writting the date in the RTC*/
void TERM_setDateDisp2(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,":D La fecha ha sido cambiada!... \r\n");
}

/** Write in the uartChannel the text for writting the hour format in the RTC*/
void TERM_setHourFormatDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Establecer formato de hora\r\n");
	UART_putString(uartChannel,"\r\n");

	/** if actual format is 12 hours, ask to change to 24 hours format*/
	if(RTC_Char->format == TRUE){
		UART_putString(uartChannel,"El formato actual es de 12 horas\r\n");
		UART_putString(uartChannel,"Cambiar a formato de 24 horas? Si/No \r\n");

	/** if actual format is 24 hours, ask to change to 12 hours format*/
	} else if(RTC_Char->format == FALSE){
		UART_putString(uartChannel,"El formato actual es de 24 horas\r\n");
		UART_putString(uartChannel,"Cambiar a formato de 12 horas? Si/No \r\n");
	}

}

/** Write in the uartChannel the text for reading the hour from the RTC*/
void TERM_readHourDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Hora actual:\r\n");

	/** Write Hour*/
	TERM_readHourDisp1(uartChannel, RTC_Char);
	UART_putString(uartChannel, "\r\n... Presione cualquier tecla para continuar... \r\n");
}

/** Write in the uartChannel the hour from the RTC*/
void TERM_readHourDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){

	/** Set in the proper line*/
	UART_putString(uartChannel, "\033[4;0H");

	/** Write hour*/
	UART_putString(uartChannel, RTC_Char->Time_Char);
}

/** Write in the uartChannel the text for reading the date from the RTC*/
void TERM_readDateDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,"Fecha actual:\r\n");

	/** Write Date*/
	TERM_readDateDisp1(uartChannel, RTC_Char);
	UART_putString(uartChannel, "\r\n... Presione cualquier tecla para continuar... \r\n");
}

/** Write in the uartChannel the date from the RTC*/
void TERM_readDateDisp1(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){

	/** Set in the proper line*/
	UART_putString(uartChannel, "\033[4;0H");

	/** Write hour*/
	UART_putString(uartChannel, RTC_Char->Date_Char);
}

/** Write in the uartChannel the text for communication between terminals*/
void TERM_communicationDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel, "Comunicación entre terminales");
	UART_putString(uartChannel,"\r\n");

}

/** Write in the uartChannel the text for LCD echo*/
void TERM_lcdDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\033[2J");
	UART_putString(uartChannel,"\033[38;5;202m");
	UART_putString(uartChannel,"\033[48;5;15m");
	UART_putString(uartChannel,"\033[H");
	UART_putString(uartChannel,"***Comunicación por UART e I2C***\r\n");
	UART_putString(uartChannel,"\r\n");
	//
	UART_putString(uartChannel,"\r\n");

}

/** Write in the uartChannel the text when an error occurs*/
void TERM_ErrorDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,":( Ocurrio un error en la comunicación I2C \r\n");
	UART_putString(uartChannel,"Verifique los dispositivos I2C \r\n");

}

/** Write in the uartChannel the text a peripheral is busy*/
void TERM_BusyDisp(UART_ChannelType uartChannel, RTC_CharArray* RTC_Char){
	UART_putString(uartChannel,"\r\n");
	UART_putString(uartChannel,":( Lo sentimos, \r\n");
	UART_putString(uartChannel,	"La opcion a la que quieres acceder, esta \r\n");
	UART_putString(uartChannel,"siendo ocupada por la otra terminal");
	UART_putString(uartChannel,"\r\n Intenta con otra opcion \r\n");
	UART_putString(uartChannel,"\r\n");

}

/** Do a 'new' read of the hour and date, in order to update the hour displayed*/
void RTC_newRead(RTC_ConfigType* Struct_RTC, RTC_CharArray* RTC_Char){

	/** Read hour and date*/
    RTC_readHour(Struct_RTC);
    RTC_readDate(Struct_RTC);

    /** Transform the new hour and date*/
    Cast_Time(Struct_RTC, RTC_Char);
    Cast_Date(Struct_RTC, RTC_Char);
}

/** Change the format in the RTC*/
void RTC_changeFormat(RTC_ConfigType* Struct_RTC){

	/** Write in the RTC the new format*/
    RTC_writeHour(Struct_RTC);

}

/** Check if the date is valid*/
void Date_Check(RTC_CharArray* RTC_Char ,RTC_ConfigType* struct_config){

	/** Transform the date from char to uint8*/
	struct_config->year = ((RTC_Char->Date_Char[8] - '0') << 4) | ((RTC_Char->Date_Char[9] - '0'));
	struct_config->month = ((RTC_Char->Date_Char[3] - '0') << 4) | ((RTC_Char->Date_Char[4] - '0'));
	struct_config->date = (((RTC_Char->Date_Char[0] - '0') << 4) | ((RTC_Char->Date_Char[1] - '0')));

	/** Check that the month is a valid one*/
	if((struct_config->month <= 0) && (struct_config->month >= 13)){
		struct_config->month = 1;
	}

	/** Checl that the day is a valid one*/
	if((struct_config->date <= 0) && (struct_config->date >= 32)){
		struct_config->month = 1;
	}

}

/** Check if the hour is valid*/
void Hour_Check(RTC_CharArray* RTC_Char ,RTC_ConfigType* struct_config){

	/** Transform the date from char to uint8*/
	struct_config->hour = ((RTC_Char->Time_Char[0] - '0') << 4) | ((RTC_Char->Time_Char[1] - '0'));
	struct_config->minute = ((RTC_Char->Time_Char[3] - '0') << 4) | ((RTC_Char->Time_Char[4] - '0'));
	struct_config->second = (((RTC_Char->Time_Char[6] - '0') << 4) | ((RTC_Char->Time_Char[7] - '0')) | 0x80);

	/** Check that the hour is in the corresponding format, if not, change the format*/
	if((struct_config->hour >= 0x13) && (struct_config->format == TRUE)){
		struct_config->hour = (struct_config->hour - 0x12)|(0x40);
	}


}

/** Transform the readed hour to char array*/
void Cast_Time(RTC_ConfigType* configRAW, RTC_CharArray* RTC_Char){

	/** Transform seconds*/
	uint8 units_seconds = configRAW->second & 0x0F;
	uint8 dozens_seconds = ((configRAW->second >> 4) & (0x7));
	RTC_Char->Time_Char[7] = (char)(units_seconds + 48);
	RTC_Char->Time_Char[6] = (char)(dozens_seconds + 48);

	/** Transform minutes*/
	uint8 units_minutes = configRAW->minute & 0x0F;
	uint8 dozens_minutes = configRAW->minute >> 4;
	RTC_Char->Time_Char[4] = (char)(units_minutes + 48);
	RTC_Char->Time_Char[3] = (char)(dozens_minutes + 48);

	/**Transform hours*/
	uint8 units_hours = configRAW->hour& 0x0F;
	uint8 dozens_hours = (configRAW->hour >> 4) & ~(0x4);

	/**Check format*/
	RTC_Char->format = configRAW->format;

	//If 12 hours format, check if AM or PM
	if(configRAW->format == TRUE){

		if((dozens_hours & 0x2) == FALSE){
			RTC_Char->Time_Char[9] = 'P';
			RTC_Char->Time_Char[10] = 'M';
			}else{
			//If AM, clear AM/PM byte
			dozens_hours = dozens_hours & ~(0x2);
			RTC_Char->Time_Char[9] = 'A';
			RTC_Char->Time_Char[10] = 'M';
			}
	//If 24 hours format, replace 'AM' or 'PM', for spaces
	} else {
		RTC_Char->Time_Char[9] = ' ';
		RTC_Char->Time_Char[10] = ' ';
	}

	/** Finish transform of hours*/
	RTC_Char->Time_Char[1] = (char)(units_hours + 48);
	RTC_Char->Time_Char[0] = (char)(dozens_hours + 48);



}

/** Tranform the date received from uint8 to char*/
void Cast_Date(RTC_ConfigType* configRAW, RTC_CharArray* RTC_Char){

	/** Transform year*/
	uint8 units_year = configRAW->year & 0x0F;
	uint8 dozens_year =configRAW->year >> 4;
	RTC_Char->Date_Char[9] = (char)(units_year + 48);
	RTC_Char->Date_Char[8] = (char)(dozens_year + 48);

	/** Transform month*/
	uint8 units_month = configRAW->month & 0x0F;
	uint8 dozens_month = (configRAW->month >> 4) & ~0x2;
	RTC_Char->Date_Char[4] = (char)(units_month + 48);
	RTC_Char->Date_Char[3] = (char)(dozens_month + 48);

	/** Transform day*/
	uint8 units_days = configRAW->date & 0x0F;
	uint8 dozens_days =configRAW->date >> 4;
	RTC_Char->Date_Char[1] = (char)(units_days + 48);
	RTC_Char->Date_Char[0] = (char)(dozens_days + 48);
}
