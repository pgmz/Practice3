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
	//I2C0, PB2 - SCL, PB3 - SDA
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister= GPIO_MUX2;
	GPIO_pinControlRegister(GPIOB, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT3, &pinControlRegister);
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);

}

uint8 RTC_write(uint8 address, uint8 data){
	I2C_start(I2C_0);
	I2C_write_Byte(I2C_0, CONTROL_W);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, data);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_stop(I2C_0);

	return TRUE;
}

uint8 RTC_read(uint8 address){
	uint8 dataFromMCP7940M;
	//I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);

	I2C_write_Byte(I2C_0, CONTROL_W);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_repeted_Start(I2C_0);
	I2C_write_Byte(I2C_0, CONTROL_R);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_TX_RX_Mode(I2C_0, I2C_RX_MODE);


	dataFromMCP7940M = I2C_read_Byte(I2C_0);
	I2C_wait(I2C_0);
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_NACK(I2C_0);

	I2C_stop(I2C_0);
	dataFromMCP7940M = I2C_read_Byte(I2C_0);

 	return dataFromMCP7940M;
}

uint8 RTC_writeHour(RTC_ConfigType* config){
	RTC_write(RTCSEC, config->second);
	RTC_write(RTCMIN, config->minute);
	RTC_write(RTCHOUR, ((config->format << 6) || config->hour));

	return TRUE;
}

uint8 RTC_writeDate(RTC_ConfigType* config){
	RTC_write(RTCWKDAY, config->weekday);
	RTC_write(RTCDATE, config->date);
	RTC_write(RTCMTH, config->month);
	RTC_write(RTCYEAR, config->year);

	return TRUE;
}

uint8 RTC_readHour(RTC_ConfigType* read){
	read->second = RTC_read(RTCSEC);
	read->minute = RTC_read(RTCMIN);
	read->hour = RTC_read(RTCHOUR);

	return TRUE;
}

uint8 RTC_readDate(RTC_ConfigType* read){
	read->weekday = RTC_read(RTCWKDAY);
	read->date = RTC_read(RTCDATE);
	read->month = RTC_read(RTCMTH);
	read->year = RTC_read(RTCYEAR);

	return TRUE;
}

uint8 RTC_setAlarm0(RTC_ConfigType* alarm0){
	//enable alarm ----

	RTC_write(ALM0SEC, alarm0->second);
	RTC_write(ALM0MIN, alarm0->minute);
	RTC_write(ALM0HOUR, ((alarm0->format << 6) || alarm0->hour));
	RTC_write(ALM0WKDAY, alarm0->weekday);
	RTC_write(ALM0DATE, alarm0->date);
	RTC_write(ALM0MTH, alarm0->month);

	return TRUE;
}

uint8 RTC_setAlarm1(RTC_ConfigType* alarm1){
	//enable alarm --

	RTC_write(ALM1SEC, alarm1->second);
	RTC_write(ALM1MIN, alarm1->minute);
	RTC_write(ALM1HOUR, ((alarm1->format << 6) || alarm1->hour));
	RTC_write(ALM1WKDAY, alarm1->weekday);
	RTC_write(ALM1DATE, alarm1->date);
	RTC_write(ALM1MTH, alarm1->month);

	return TRUE;
}

uint8 RTC_disableAlarm0();

uint8 RTC_disableAlarm1();
