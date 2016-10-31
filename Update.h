

#ifndef SOURCES_SYSUPD_H_
#define SOURCES_SYSUPD_H_

#include "UART.h"

#define SYSTEM_CLOCK 21000000

typedef enum{
	DEFAULT_DISP,
	READ_MEMORY,
	WRITE_MEMORY,
	SET_TIME,
	SET_DATE,
	TIME_FORM,
	READ_TIME,
	READ_DATE,
	COM_TERM2,
	ECO_LCD
}MenuStateType;

typedef struct{
	uint8 option;
	void (*fptr_Option_func)(uint8);
}DisplayStruct;

/*
typedef struct{
	MenuStateType CurrentState;
	DisplayStruct ButtonFunct[9];
}SystemUpdateStateMachine;
*/

void DEFAULT_DISPLAY();

void SYSUPD_init();

void SYSUPD_update(uint8);

void switchMenu(MenuStateType);

void WR_MEMORY();

void RD_MEMORY();

void TIME_SET();

void DATE_SET();

void TIME_FORMAT();

void RD_TIME();

void WR_TIME();

void TERM2_COM();

void LCD_ECO();



#endif /* SOURCES_SYSUPD_H_ */
