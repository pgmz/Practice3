/*
 * DISP.c
 *
 *	DISP file, handles the LCDNokia, by writting the
 *	needed stuff in each state.
 *
 *  Created on: 08/10/2016
 *      Author: Patricio Gomez
 */

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"
#include "GPIO.h"
#include "DISP.h"
#include "SPI.h"
#include "LCDNokia5110.h"
#include "MCP7940M.h"
#include "UART.h"

/*Clear the display and write the time and date*/
void Info_Display(RTC_CharArray* info){
	LCDNokia_clear();
	LCDNokia_gotoXY(0,0);
	LCDNokia_sendString(info->Time_Char);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(info->Date_Char);
}

/*Write the eco from TeraTerm*/
void Eco_Display(uint8 data){
	LCDNokia_sendChar(data);
}

/**Write the manual hour and date change menu*/
void Button_Display(RTC_CharArray* info){
	LCDNokia_clear();
	LCDNokia_gotoXY(0,0);
	LCDNokia_sendString("HH/MM/SS");
	LCDNokia_gotoXY(0,1);
	LCDNokia_sendString(info->Time_Char);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString("B1(+)B2(-)B3(OK)");
	LCDNokia_gotoXY(0,3);
	LCDNokia_sendString("DD/MM/AAAA");
	LCDNokia_gotoXY(0,4);
	LCDNokia_sendString(info->Date_Char);
	LCDNokia_gotoXY(0,5);
	LCDNokia_sendString("B4(+)B5(-)B6(OK=");
}


