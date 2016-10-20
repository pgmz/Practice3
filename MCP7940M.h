/*
 * MCP7940M.h
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_MCP7940M_H_
#define SOURCES_MCP7940M_H_

#include "DataTypeDefinitions.h"

typedef struct{
	uint8 weekday :3;
	uint8 date :6;
	uint8 month :6;
	uint8 year :8;
	uint8 format :1;
	uint8 hour :6;
	uint8 minute :7;
	uint8 second :7;
}RTC_ConfigType;


uint8 RTC_write(RTC_ConfigType* config);

uint8 RTC_writeHour(RTC_ConfigType* config);

uint8 RTC_writeDate(RTC_ConfigType* comfig);

uint8 RTC_readHour();

uint8 RTC_readDate();

uint8 RTC_setAlarm1(RTC_ConfigType* alarm0);

uint8 RTC_setAlarm2(RTC_ConfigType* alarm1);

uint8 RTC_disableAlarm0();

uint8 RTC_disableAlarm1();

#endif /* SOURCES_MCP7940M_H_ */
