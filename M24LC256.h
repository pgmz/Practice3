/*
 * M24LC256.h
 *
 *	This file is a device driver for the 24LC256 integrated,
 *	that includes the functions needed for writing and reading
 *	the memory. Includes I2C functions
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_M24LC256_H_
#define SOURCES_M24LC256_H_

#include "DataTypeDefinitions.h"
#include "I2C.h"

//Control byte when writting, or chip select for I2C Memory (if A0 = A1 = A2 = 0)
#define MEM_CONTROL_W 0xA0

//Control byte when reading, or chip select for 12C Memory (if A0 = A1 = A2 = 0)
#define MEM_CONTROL_R 0xA1

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This initializes the I2C in order to have communication with the I2C Memory
 	 \return
 	 TODO: return 0 if init failed

 */
uint8 MEM_init();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This gathers the I2C functions needed for writting in the memory
 	 \param[in] address, is the internal address where the data will be written
 	 \param[in] data is the value that will be written
 	 \return May return 1 or 0 to indicate if the operation was succesful or not


 */
uint8 MEM_write(uint16 address, char data);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This gathers the 12C functions needed for reading the memory
 	 \param[in] address, is the internal address that will be read
 	 \return returns the char readed.


 */
char MEM_read(uint16 address);

#endif /* SOURCES_M24LC256_H_ */
