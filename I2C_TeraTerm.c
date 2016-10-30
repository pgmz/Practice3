/*
 * I2C_TeraTerm.c
 *
 *  Created on: 29/10/2016
 *      Author: Laplace´s Demon
 */
#include "uart.h"
#include "TermHandler.h"
#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"



uint16 expo(uint8 a,uint8 b){
	uint16 dataout = 1;
	int i;
	if(b == 0){
		dataout = 1;
	}else{
		for(i = 0;i<b;i++){
			dataout = dataout*a;
		}
	}
	return dataout;
}

uint16 Cast_Memory(uint8 memory[]){
	uint16 DataOut = 0;
	int i;
	int j = 0;
	for(i = 5;i>1;i--){
		if(memory[i] >= 65){
			DataOut += (int)((memory[i]-55)*(expo(16,j)));
			j++;
		}
		else{
			DataOut += (int)((memory[i]-48)*(expo(16,j)));
			j++;
		}
	}
	return DataOut;
}



