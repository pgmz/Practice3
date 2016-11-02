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

//#define A0 0
//#define A1 0
//#define A2 0

#define MEM_CONTROL_W 0xA0
#define MEM_CONTROL_R 0xA1


uint8 MEM_init();

uint8 MEM_write(uint16 address, char data);

char MEM_read(uint16 address);

#endif /* SOURCES_M24LC256_H_ */
