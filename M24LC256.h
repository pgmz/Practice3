/*
 * MCP7940M.h
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_M24LC256_H_
#define SOURCES_M24LC256_H_

#include "DataTypeDefinitions.h"
#include "I2C.h"


/*Constant that define */
#define MEM_CONTROL_W 0xA0
#define MEM_CONTROL_R 0xA1

/*
	\brief	This Function configures the PINS 2 and 3 of the port B and start the channel 0 of the I2C with a specific system clock and baud rate

	\return	void
 */
void MEM_init();
/*
	\brief	This Function write the direction and data of that direction to the terminal usiang I2C

	\param[in]	address input value that represent the direction that was accessed
	\param[in]	data input value that represent the data stored in that direction

	\return	uint8 set a true value after finished the communication
 */
uint8 MEM_write(uint16 address, char data);
/*
	\brief	This Function clear the Display LCD and write the message that was written at the PC terminal or SmartPhone terminal

	\param[in]	uartChannel input value that determine the UART channel that is used to trasmit the message to the LCD
	\return	void
 */
char MEM_read(uint16 address);


#endif /* SOURCES_M24LC256_H_ */
