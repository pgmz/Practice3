/*
 * FIFO.h
 *
 * This functions, lets the user have a FIFO, that has the basic
 * utilities, like PUSH or POP of MAX_BUFF chars.
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#ifndef SOURCES_FIFO_H_
#define SOURCES_FIFO_H_

#include "DataTypeDefinitions.h"

#define MAX_BUFF 50

/**typedef struct for a FIFO*/
typedef struct {
	/**Buffer of 50 characters, that will be stored
	 * in the FIFO*/
	char buff [MAX_BUFF];
	/**Index of head*/
	uint8 head;
	/**Index of tail*/
	uint8 tail;
}FIFO_Type;

/** Flag to indicate if FIFO is empty*/
#define EMPTY 0

/** Flag to indicate if FIFO is full*/
#define FULL 1

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function pushes a data in the FIFO f
 	 \param[in] f is the direction of the FIFO struct that will be modified
 	 \param[in] data is the value that will be pushed in the FIFO
 	 \return May return 1 or 0 ti indicate if the operation was succesful or not (if FIFO is full)


 */
uint8 FIFO_PUSH(FIFO_Type* f, char data);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function pops a data from the FIFO f
 	 \param[in] f is the direction of the FIFO struct from which the data will be read
 	 \return Returns the 'popped' value


 */
uint8 FIFO_POP(FIFO_Type* f);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	This function sets the tail and head to 0, and the buffer to 0
 	 \param[in] f is the direction of the FIFO struct that will be modified
 	 \return May return 1 or 0 ti indicate if the operation was succesful or not


 */
uint8 FIFO_restart(FIFO_Type *f);
#endif /* SOURCES_FIFO_H_ */
