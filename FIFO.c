/*
 * FIFO.c
 *
 * This functions, lets the user have a FIFO, that has the basic
 * utilities, like PUSH or POP of MAX_BUFF chars.
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#include "FIFO.h"

/*Function that pushes a value in the FIFO*/
uint8 FIFO_PUSH(FIFO_Type* f, char data){

	/** If the tail is not the edge (FIFO is full), return 0*/
	if(f->tail >= (MAX_BUFF-1)){
		return FALSE;
	} else {
		/** If FIFO is not full, store in the buffer, at the tail index, the data*/
		f->buff[f->tail] = data;
		/** Increment the tail index*/
		f->tail++;
	}
}

/** Function that pops a value from the FIFO*/
uint8 FIFO_POP(FIFO_Type* f){
	char data;

	/** If the tail and the head index are equal, the
	 * FIFO is empty, return FALSE*/
	if(f->tail == f->head){
		return FALSE;
	} else {
		/** If FIFO is not empty, return the value at the
		 * head index, and increment the head index*/
		data = f->buff[f->head];
		f->head++;
		return data;
	}
}

/*Restart the FIFO indexes (head = tail = 0)*/
uint8 FIFO_restart(FIFO_Type *f){
	f->head = 0;
	f->tail = 0;
}
