/*
 * FIFO.h
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_FIFO_H_
#define SOURCES_FIFO_H_

#include "DataTypeDefinitions.h"

typedef struct {
	char buff [50];
	uint8 head;
	uint8 tail;
}FIFO_Type;

#define EMPTY 0
#define FULL 1


uint8 FIFO_PUSH(FIFO_Type* f, char data);
uint8 FIFO_POP(FIFO_Type* f);
#endif /* SOURCES_FIFO_H_ */
