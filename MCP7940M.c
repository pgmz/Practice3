
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

uint8 Time_Char[]="00:00:00";




uint8 RTC_init(){
	//I2C0, PB2 - SCL, PB3 - SDA
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister= GPIO_MUX2;
	GPIO_pinControlRegister(GPIOB, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT3, &pinControlRegister);
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);
}


void Cast_Time(RTC_ConfigType* configRAW, RTC_CharArray* config){
	uint8 units_seconds = configRAW->second & 0x0F;
	uint8 dozens_seconds = configRAW->second >> 4;
	config->Time_Char[7] = (char)(units_seconds + 48);
	config->Time_Char[6] = (char)(dozens_seconds + 48);

	uint8 units_minutes = configRAW->minute & 0x0F;
	uint8 dozens_minutes = configRAW->minute >> 4;
	config->Time_Char[4] = (char)(units_minutes + 48);
	config->Time_Char[3] = (char)(dozens_minutes + 48);

	uint8 units_hours = configRAW->hour& 0x0F;
	uint8 dozens_hours = configRAW->hour >> 4;
	config->Time_Char[1] = (char)(units_hours + 48);
	config->Time_Char[0] = (char)(dozens_hours + 48);

	if(configRAW->format){
		config->Time_Char[9] = 'A';
	}else{
		config->Time_Char[9] = 'P';
	}

}

void Cast_Date(RTC_ConfigType* configRAW, RTC_CharArray* config){
	uint8 units_year = configRAW->year & 0x0F;
	uint8 dozens_year =configRAW->year >> 4;
	config->Date_Char[3] = (char)(units_year + 48);
	config->Date_Char[2] = (char)(dozens_year + 48);

	uint8 units_month = configRAW->month & 0x0F;
	uint8 dozens_month = configRAW->month >> 4;
	config->Date_Char[6] = (char)(units_month + 48);
	config->Date_Char[5] = (char)(dozens_month + 48);

	uint8 units_days = configRAW->date & 0x0F;
	uint8 dozens_days =configRAW->date >> 4;
	config->Date_Char[9] = (char)(units_days + 48);
	config->Date_Char[8] = (char)(dozens_days + 48);
}




uint8 RTC_write(uint8 address, uint8 data){
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
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
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
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

	I2C_NACK(I2C_0);
	dataFromMCP7940M = I2C_read_Byte(I2C_0);
	I2C_wait(I2C_0);
	//I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	//I2C_NACK(I2C_0);

	I2C_stop(I2C_0);
	dataFromMCP7940M = I2C_read_Byte(I2C_0);

	return dataFromMCP7940M;
}

uint8 RTC_writeHour(RTC_ConfigType* config){
	RTC_write(RTCSEC, config->second);
	delay(100);
	RTC_write(RTCMIN, config->minute);
	delay(100);
	RTC_write(RTCHOUR, ((config->format << 6) || config->hour));
	delay(100);

	return TRUE;
}

uint8 RTC_writeDate(RTC_ConfigType* config){
	RTC_write(RTCWKDAY, config->weekday);
	delay(100);
	RTC_write(RTCDATE, config->date);
	delay(100);
	RTC_write(RTCMTH, config->month);
	delay(100);
	RTC_write(RTCYEAR, config->year);
	delay(100);

	return TRUE;
}

uint8 RTC_readHour(RTC_ConfigType* read){
	read->second = RTC_read(RTCSEC);
	delay(100);
	read->minute = RTC_read(RTCMIN);
	delay(100);
	read->hour = RTC_read(RTCHOUR);
	delay(100);

	return TRUE;
}

uint8 RTC_readDate(RTC_ConfigType* read){
	read->weekday = RTC_read(RTCWKDAY);
	delay(100);
	read->date = RTC_read(RTCDATE);
	delay(100);
	read->month = RTC_read(RTCMTH);
	delay(100);
	read->year = RTC_read(RTCYEAR);
	delay(100);

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
