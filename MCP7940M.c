/*
 * MCP7940M.c
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#include "MCP7940M.h"


uint8 RTC_write(RTC_ConfigType* config);

uint8 RTC_writeHour(RTC_ConfigType* config);

uint8 RTC_writeDate(RTC_ConfigType* comfig);

uint8 RTC_readHour();

uint8 RTC_readDate();

uint8 RTC_setAlarm1(RTC_ConfigType* alarm0);

uint8 RTC_setAlarm2(RTC_ConfigType* alarm1);

uint8 RTC_disableAlarm0();

uint8 RTC_disableAlarm1();

