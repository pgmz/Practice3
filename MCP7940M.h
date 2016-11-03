/*
 * MCP7940M.h
 *
 *	This file is a device driver for the MCP7940M integrated,
 *	that includes the functions needed for writing and reading
 *	the RTC. Includes I2C functions.
 *
 *	Has functions that write or read the 'full hour' (hour, minutes, seconds)
 * 	or date (day, month, year)
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_MCP7940M_H_
#define SOURCES_MCP7940M_H_

#include "DataTypeDefinitions.h"
#include "I2C.h"

/** Control bytes for reading or writing*/
#define CONTROL_W 0xDE
#define CONTROL_R 0xDF

/** RTC address for seconds*/
#define RTCSEC 0x0
/** RTC address for minutes*/
#define RTCMIN 0x1
/** RTC address for hour*/
#define RTCHOUR 0x2
/** RTC address for weekday*/
#define RTCWKDAY 0x3
/** RTC address for day*/
#define RTCDATE 0x4
/** RTC address for month*/
#define RTCMTH 0x5
/** RTC address for year*/
#define RTCYEAR 0x6

/** RTC address for alamrs*/
#define ALxMEN 0x7
#define AL0MEN 4
#define AL1MEN 5

/** RTC address for alarms*/
#define ALM0SEC 0xA
#define ALM0MIN 0xB
#define ALM0HOUR 0xC
#define ALM0WKDAY 0xD
#define ALM0DATE 0xE
#define ALM0MTH 0xF

/** RTC address for alarms*/
#define ALM1SEC 0x11
#define ALM1MIN 0x12
#define ALM1HOUR 0x13
#define ALM1WKDAY 0x14
#define ALM1DATE 0x15
#define ALM1MTH 0x16

/** Defines*/
#define LOW4 0x0F
#define SHIFT4 4

/** Struct that has the hour and date values in uint8*/
typedef struct{
	/** weekday number*/
	uint8 weekday :3;
	/** Day number*/
	uint8 date :6;
	/** Month number*/
	uint8 month :6;
	/** Year number*/
	uint8 year :8;
	/** Format number*/
	uint8 format :1;
	/** Hour number*/
	uint8 hour :7;
	/** Minute number*/
	uint8 minute :7;
	/** Second number*/
	uint8 second :8;
}RTC_ConfigType;

/** Struct that has the hour and date values in char arrays*/
typedef struct{
	/** Time_char, has the char values of the hour*/
	char Time_Char[11];
	/** End of line*/
	char end2[2];
	/** Date_char, has the char values of the date*/
	char Date_Char[10];
	/** End of line*/
	char end1[2];
	/** Format number*/
	uint8 format :1;
}RTC_CharArray;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This initializes the I2C in order to communicate with the RTC
 	 \return
 	 TODO: May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_init();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function gathers the I2C functions needed for writting in the rtc
 	 \param[in] address, is the internal address where the data will be written
 	 \param[in] data is the value that will be written
 	 \return May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_write(uint8 address, uint8 data);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This funciton gathers the 12C functions needed for reading the rtc
 	 \param[in] address, is the internal address that will be read
 	 \return returns the uint8 readed.


 */
static uint8 RTC_read(uint8 address);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function writes hour (Hour, minutes and seconds) in the config struct
 	 \param[in] config, is the struct that contains the hour, minutes, and seconds that will
 	 	 be written in the RTC
 	 \return
 	 TODO: May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_writeHour(RTC_ConfigType* config);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function writes date (day, month and year) in the config struct
 	 \param[in] config, is the struct that contains the day, month and year that will
 	 	 be written in the RTC
 	 \return
 	 TODO: May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_writeDate(RTC_ConfigType* config);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function reads hour (Hour, minutes and seconds), and stores in the config struct
 	 \param[in] config, is the struct that will contain the hour, minutes, and seconds that will
 	 	 be read from the RTC
 	 \return
 	 TODO: May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_readHour(RTC_ConfigType* read);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function reads date (day, month and year), and stores in the config struct
 	 \param[in] config, is the struct that will contain the day, month and year that will
 	 	 be read from the RTC
 	 \return
 	 TODO: May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 RTC_readDate(RTC_ConfigType* read);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function sets an alarm, taking the values in the alarm0 struct
 	 \param[in] alarm0, is the struct that contains the alarm values
 	 	 be read from the RTC
 	 \return
 	 TODO: Not implemented or not used in code


 */
static uint8 RTC_setAlarm0(RTC_ConfigType* alarm0);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function sets an alarm, taking the values in the alarm1 struct
 	 \param[in] alarm1, is the struct that contains the alarm values
 	 	 be read from the RTC
 	 \return
 	 TODO: Not implemented or not used in code


 */
static uint8 RTC_setAlarm1(RTC_ConfigType* alarm1);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function disables alarm 0
 	 \return
 	 TODO: Not implemented or not used in code


 */
static uint8 RTC_disableAlarm0();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function disables alarm 1
 	 \return
 	 TODO: Not implemented or not used in code


 */
static uint8 RTC_disableAlarm1();



#endif /* SOURCES_MCP7940M_H_ */
