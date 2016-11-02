
/*
 * MCP7940M.c
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#include "MCP7940M.h"
#include "I2C.h"
#include "GPIO.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"


uint8 RTC_init(){

	/** Enables the clock gating to use PORTB*/
	GPIO_clockGating(GPIOB);

	/** Use PB2 and PB3 with the functionality of I2C0, PB2 - SCL, PB3 - SDA*/
	GPIO_pinControlRegisterType pinControlRegister= GPIO_MUX2;
	GPIO_pinControlRegister(GPIOB, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT3, &pinControlRegister);

	/*I2C init*/
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);
}

/** Function that writes in the RTC*/
uint8 RTC_write(uint8 address, uint8 data){

	/** Send start signal*/
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);

	/** Send Control byte or chip select, for writting in the RTC*/
	I2C_write_Byte(I2C_0, CONTROL_W);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send the internal address, to write in that address*/
	I2C_write_Byte(I2C_0, address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send the data*/
	I2C_write_Byte(I2C_0, data);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send stop signal*/
	I2C_stop(I2C_0);

	return TRUE;
}

/** Function that read from the RTC*/
uint8 RTC_read(uint8 address){

	uint8 dataFromMCP7940M;

	/** Send start signal*/
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);

	/** Send Control byte or chip select to write in the RTC*/
	I2C_write_Byte(I2C_0, CONTROL_W);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send the internal address, that will be read*/
	I2C_write_Byte(I2C_0, address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send repeated start signal (start signal)*/
	I2C_repeted_Start(I2C_0);
	I2C_write_Byte(I2C_0, CONTROL_R);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Change to receiving mode*/
	I2C_TX_RX_Mode(I2C_0, I2C_RX_MODE);
	I2C_NACK(I2C_0);

	/** Dummy read*/
	dataFromMCP7940M = I2C_read_Byte(I2C_0);
	I2C_wait(I2C_0);

	/** Send stop signal*/
	I2C_stop(I2C_0);

	/** Read from the RTC*/
	dataFromMCP7940M = I2C_read_Byte(I2C_0);

	return dataFromMCP7940M;
}

/** Function that writes a 'full hour' config*/
uint8 RTC_writeHour(RTC_ConfigType* config){

	//Write hour with the corresponding format
	RTC_write(RTCHOUR, ((config->format << 6) | config->hour));
	delay(100);

	//Write the minutes
	RTC_write(RTCMIN, config->minute);
	delay(100);

	//Writes the seconds, and the ST, that enables the RTC to use the
	//external crystal
	RTC_write(RTCSEC, ((config->second))|0x80);
	delay(100);

	return TRUE;
}

/** Functino that writes a date config*/
uint8 RTC_writeDate(RTC_ConfigType* config){

	/** Write the weekday*/
	RTC_write(RTCWKDAY, config->weekday);
	delay(100);

	/** Write the day*/
	RTC_write(RTCDATE, config->date);
	delay(100);

	/** Write the month*/
	RTC_write(RTCMTH, config->month);
	delay(100);

	/** Write the year*/
	RTC_write(RTCYEAR, config->year);
	delay(100);

	return TRUE;
}

/** Read a 'full hour', and write in the read struct*/
uint8 RTC_readHour(RTC_ConfigType* read){

	/** Read seconds*/
	read->second = RTC_read(RTCSEC);
	delay(100);

	/** Read minutes*/
	read->minute = RTC_read(RTCMIN);
	delay(100);

	/** Read the hour*/
	read->hour = RTC_read(RTCHOUR);
	delay(100);

	/** Read implicitly, the format*/
	if((read->hour & 0x40) == 0){
		read->format = 0;
	} else {
		read->format = 1;
	}
	return TRUE;
}

/** Read a date, and write in the read struct*/
uint8 RTC_readDate(RTC_ConfigType* read){
	/** Read weekday*/
	read->weekday = RTC_read(RTCWKDAY);
	delay(100);

	/** Read day*/
	read->date = RTC_read(RTCDATE);
	delay(100);

	/** Read month*/
	read->month = RTC_read(RTCMTH);
	delay(100);

	/** Read year*/
	read->year = RTC_read(RTCYEAR);
	delay(100);

	return TRUE;
}

/** Write the Alarm 0*/
uint8 RTC_setAlarm0(RTC_ConfigType* alarm0){

	RTC_write(ALM0SEC, alarm0->second);
	RTC_write(ALM0MIN, alarm0->minute);
	RTC_write(ALM0HOUR, ((alarm0->format << 6) || alarm0->hour));
	RTC_write(ALM0WKDAY, alarm0->weekday);
	RTC_write(ALM0DATE, alarm0->date);
	RTC_write(ALM0MTH, alarm0->month);

	return TRUE;
}

/** Write the Alarm 1*/
uint8 RTC_setAlarm1(RTC_ConfigType* alarm1){

	RTC_write(ALM1SEC, alarm1->second);
	RTC_write(ALM1MIN, alarm1->minute);
	RTC_write(ALM1HOUR, ((alarm1->format << 6) || alarm1->hour));
	RTC_write(ALM1WKDAY, alarm1->weekday);
	RTC_write(ALM1DATE, alarm1->date);
	RTC_write(ALM1MTH, alarm1->month);

	return TRUE;
}

/** Disable the alarm 0*/
uint8 RTC_disableAlarm0();

/** Disable the alarm 1*/
uint8 RTC_disableAlarm1();
