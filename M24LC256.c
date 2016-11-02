/*
 * M24LC256.c
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

void MEM_init(){
	GPIO_clockGating(GPIOB);
	GPIO_pinControlRegisterType pinControlRegister= GPIO_MUX2;
	GPIO_pinControlRegister(GPIOB, BIT2, &pinControlRegister);
	GPIO_pinControlRegister(GPIOB, BIT3, &pinControlRegister);
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);

}

uint8 MEM_write(uint16 address, char data){
	while(I2C_busy(I2C_0) == TRUE);

	uint8 h_address = 0x00FF & (address >> 8);
	uint8 l_address = address;
	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);
	I2C_write_Byte(I2C_0, MEM_CONTROL_W);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, h_address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, l_address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, data);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_stop(I2C_0);
	delay(100);

	return TRUE;
}

char MEM_read(uint16 address){
	while(I2C_busy(I2C_0) == TRUE);
	uint8 h_address = (address >> 8);
	uint8 l_address = address;
	char dataFromM24LC256;

	I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);
	I2C_start(I2C_0);

	I2C_write_Byte(I2C_0, MEM_CONTROL_W);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, h_address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_write_Byte(I2C_0, l_address);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);


	I2C_repeted_Start(I2C_0);
	I2C_write_Byte(I2C_0, MEM_CONTROL_R);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	I2C_TX_RX_Mode(I2C_0, I2C_RX_MODE);

	I2C_NACK(I2C_0);
	dataFromM24LC256 = I2C_read_Byte(I2C_0);
	//I2C_NACK(I2C_0);

	I2C_wait(I2C_0);

	//I2C_TX_RX_Mode(I2C_0, I2C_TX_MODE);



	I2C_stop(I2C_0);
	dataFromM24LC256 = I2C_read_Byte(I2C_0);
 	return dataFromM24LC256;
}
