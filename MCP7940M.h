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

#define CONTROL_W 0x6E
#define CONTROL_R 0x6F

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


uint8 RTC_init();

uint8 RTC_write(uint8 address, uint8 data);

uint8 RTC_writeHour(RTC_ConfigType* config);

uint8 RTC_writeDate(RTC_ConfigType* config);

uint8 RTC_readHour(RTC_ConfigType* read);

uint8 RTC_readDate(RTC_ConfigType* read);

uint8 RTC_setAlarm0(RTC_ConfigType* alarm0);

uint8 RTC_setAlarm1(RTC_ConfigType* alarm1);

uint8 RTC_disableAlarm0();

uint8 RTC_disableAlarm1();

#endif /* SOURCES_MCP7940M_H_ */
