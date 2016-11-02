/*
 * MCP7940M.h
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_MCP7940M_H_
#define SOURCES_MCP7940M_H_

#include "DataTypeDefinitions.h"
#include "I2C.h"

#define CONTROL_W 0xDE
#define CONTROL_R 0xDF

#define RTCSEC 0x0
#define RTCMIN 0x1
#define RTCHOUR 0x2
#define RTCWKDAY 0x3
#define RTCDATE 0x4
#define RTCMTH 0x5
#define RTCYEAR 0x6

#define ALxMEN 0x7
#define AL0MEN 4
#define AL1MEN 5

#define ALM0SEC 0xA
#define ALM0MIN 0xB
#define ALM0HOUR 0xC
#define ALM0WKDAY 0xD
#define ALM0DATE 0xE
#define ALM0MTH 0xF

#define ALM1SEC 0x11
#define ALM1MIN 0x12
#define ALM1HOUR 0x13
#define ALM1WKDAY 0x14
#define ALM1DATE 0x15
#define ALM1MTH 0x16

#define LOW4 0x0F
#define SHIFT4 4


typedef struct{
	uint8 weekday :3;
	uint8 date :6;
	uint8 month :6;
	uint8 year :8;
	uint8 format :1;
	uint8 hour :7;
	uint8 minute :7;
	uint8 second :8;
}RTC_ConfigType;

typedef struct{
	char Time_Char[11];
	char end2[2];
	char Date_Char[10];
	char end1[2];
}RTC_CharArray;


uint8 RTC_init();

uint8 RTC_write(uint8 address, uint8 data);

static uint8 RTC_read(uint8 address);

uint8 RTC_writeHour(RTC_ConfigType* config);

uint8 RTC_writeDate(RTC_ConfigType* config);

uint8 RTC_readHour(RTC_ConfigType* read);

uint8 RTC_readDate(RTC_ConfigType* read);

static uint8 RTC_setAlarm0(RTC_ConfigType* alarm0);

static uint8 RTC_setAlarm1(RTC_ConfigType* alarm1);

static uint8 RTC_disableAlarm0();

static uint8 RTC_disableAlarm1();

uint8 RTC_ErrorFlag();


#endif /* SOURCES_MCP7940M_H_ */
