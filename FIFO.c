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
	if(f->tail == f->head){
		return FALSE;
	} else {
		f->tail--;
		return f->buff[f->tail];
	}
}

