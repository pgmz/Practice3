/*
 * M24LC256.c
 *
 *	This file is a device driver for the 24LC256 integrated,
 *	that includes the functions needed for writing and reading
 *	the memory. Includes I2C functions
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#include "M24LC256.h"
#include "I2C.h"
#include "GPIO.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"

/**  Function that initialized*/
uint8 MEM_init(){

	/** Enables clock gating in PORTB to use PB2 and PB3*/
	GPIO_clockGating(GPIOB);

	/** Use PB2 and PB3 with the functionality of I2C0, PB2 - SCL, PB3 - SDA*/
	GPIO_pinControlRegisterType pinControlRegister= GPIO_MUX2;
	GPIO_pinControlRegister(GPIOB, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT3, &pinControlRegister);

	/** Init I2C*/
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);

}

/** Function that writes in the memory*/
uint8 MEM_write(uint16 address, char data){

	/** Separate the high and low address*/
	uint8 h_address = 0x00FF & (address >> 8);
	uint8 l_address = address;

	/** Set transmitting mode*/
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	/** Send the start signal*/
	I2C_start(I2C_0);
	/** Write the control byte*/
	I2C_write_Byte(I2C_0, MEM_CONTROL_W);
	/** Wait for transfer complete*/
	I2C_wait(I2C_0);
	/** Wait for ack byte from slave*/
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Write the high part of address*/
	I2C_write_Byte(I2C_0, h_address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Write the low part of address*/
	I2C_write_Byte(I2C_0, l_address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Write the data*/
	I2C_write_Byte(I2C_0, data);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send the stop signal*/
	I2C_stop(I2C_0);

	/** Safe delay*/
	delay(100);

	return TRUE;
}

/** Function that read the memory*/
char MEM_read(uint16 address){
	/** Separate high and low address*/
	uint8 h_address = (address >> 8);
	uint8 l_address = address;
	char dataFromM24LC256;

	/** Send start signal*/
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);

	/** Write Control byte for writting*/
	I2C_write_Byte(I2C_0, MEM_CONTROL_W);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send high address*/
	I2C_write_Byte(I2C_0, h_address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send low address*/
	I2C_write_Byte(I2C_0, l_address);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Send repeated start signal (start signal)*/
	I2C_repeted_Start(I2C_0);

	/** Write Control byte for reading*/
	I2C_write_Byte(I2C_0, MEM_CONTROL_R);
	I2C_wait(I2C_0);
	while(((timeout_Flag() == 0) && (I2C_get_ACK(I2C_0) == TRUE)));

	/** Change to receiving mode*/
	I2C_TX_RX_Mode(I2C_0, I2C_RX_MODE);

	/** Read the data (Dummy read)*/
	I2C_NACK(I2C_0);
	dataFromM24LC256 = I2C_read_Byte(I2C_0);

	I2C_wait(I2C_0);

	/** Send stop signal*/
	I2C_stop(I2C_0);

	/** Read the data*/
	dataFromM24LC256 = I2C_read_Byte(I2C_0);

	/** Return data readed*/
 	return dataFromM24LC256;
}


