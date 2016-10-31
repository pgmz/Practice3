/*
 * FIFO.c
 *
 *  Created on: 30/10/2016
 *      Author: Patricio Gomez
 */

#include "FIFO.h"

uint8 FIFO_PUSH(FIFO_Type* f, char data){
	if(f->tail >= 49){
		return FALSE;
	} else {
		f->buff[f->tail] = data;
		f->tail++;
	}
}

uint8 FIFO_POP(FIFO_Type* f){
	char data;
	if(f->tail == f->head){
		return FALSE;
	} else {
		data = f->buff[f->head];
		f->head++;
		return data;
	}
}

uint8 FIFO_restart(FIFO_Type *f){
	f->head = 0;
	f->tail = 0;
}
