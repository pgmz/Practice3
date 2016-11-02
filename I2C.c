/*
 * I2C.c
 *
 *  Created on: 20/10/2016
 *      Author: Patricio Gomez
 */
/*
 * I2C.c
 *
 *  Created on: 20/10/2016
 *      Author: Laplace´s Demon
 */

#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"
#include "MK64F12.h"
#include "I2c.h"



/* Configures the I2C port based on the input parameters */
void I2C_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate){
	switch(channel){
	/*Set the configuration to activate the channel 0 of the I2C*/
	case I2C_0:
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
		I2C0_F = 0x56;
		I2C0_C1 |= I2C_C1_IICEN_MASK;
		break;
		/*Set the configuration to activate the channel 1 of the I2C*/
	case I2C_1:
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
		I2C1_F = 0x14;
		I2C1_C1 |= I2C_C1_IICEN_MASK;
		break;
		/*Set the configuration to activate the channel 2 of the I2C*/
	case I2C_2:		
		SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK; 
		I2C2_F = 0x14;
		I2C2_C1 |= I2C_C1_IICEN_MASK;
		break;

	default:
		break;

	}


}
/* Verify if the Bus of the I2C is busy, return TRUE if the bit busy is 1 or FALSE if the bit busy is 0  */
uint8 I2C_busy(I2C_ChannelType channel){

	switch(channel){

	case I2C_0:
		/* Verify the bit busy of the channel 0 of the I2C*/
		if((I2C0_S & I2C_S_BUSY_MASK) == FALSE ){
			/* If not busy return FALSE*/
			return FALSE;
		}else{
			/* If  busy return TRUE*/
			return TRUE;
		}
		break;
	case I2C_1:
		/* Verify the bit busy of the channel 1 of the I2C*/
		if((I2C1_S & I2C_S_BUSY_MASK) == FALSE ){
			/* If not busy return FALSE*/
			return FALSE;
		}else{
			/* If busy return TRUE*/
			return TRUE;
		}
		break;

	case I2C_2:
		/* Verify the bit busy of the channel 2 of the I2C*/
		if((I2C2_S & I2C_S_BUSY_MASK) == FALSE ){
			/* If not busy return FALSE*/
			return FALSE;
		}else{
			/* If busy return TRUE*/
			return TRUE;
		}
		break;


	default:
		break;

	}


}
/* Activate the MASTER or SLAVE mode of the selected I2C Channel*/
void I2C_MST_OrSLV_Mode(I2C_ChannelType channel, uint8 master_slave){
	switch(channel){
	case I2C_0:
		if(master_slave == FALSE){
			/* Activate the SLAVE mode of channel 0 of the I2C*/
			I2C0_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			/* Activate the MASTER mode of channel 0 of the I2C*/
			I2C0_C1 |= I2C_C1_MST_MASK;
		}
		break;

	case I2C_1:
		if(master_slave == FALSE){
			/* Activate the SLAVE mode of channel 1 of the I2C*/
			I2C1_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			/* Activate the SLAVE mode of channel 1 of the I2C*/
			I2C1_C1 |= I2C_C1_MST_MASK;
		}
		break;

	case I2C_2:
		if(master_slave == FALSE){
			/* Activate the SLAVE mode of channel 2 of the I2C*/
			I2C2_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			/* Activate the SLAVE mode of channel 2 of the I2C*/
			I2C2_C1 |= I2C_C1_MST_MASK;
		}
		break;
	}
}

/* Activate the TRANSMIT or RECEIVE mode of the selected I2C Channel */
void I2C_TX_RX_Mode(I2C_ChannelType channel, uint8 TX_RX){
	switch(channel){

	case I2C_0:
		if(TX_RX == FALSE){
			/* Activate the RECEIVE mode of channel 0 of the I2C*/
			I2C0_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			/* Activate the TRANSMIT mode of channel 0 of the I2C*/
			I2C0_C1 |= I2C_C1_TX_MASK;
		}
		break;

	case I2C_1:
		if(TX_RX == FALSE){
			/* Activate the RECEIVE mode of channel 1 of the I2C*/
			I2C1_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			/* Activate the TRANSMIT mode of channel 1 of the I2C*/
			I2C1_C1 |= I2C_C1_TX_MASK;
		}
		break;

	case I2C_2:
		if(TX_RX == FALSE){
			/* Activate the RECEIVE mode of channel 1 of the I2C*/
			I2C2_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			/* Activate the TRANSMIT mode of channel 1 of the I2C*/
			I2C2_C1 |= I2C_C1_TX_MASK;
		}
		break;
	}

}
/* Changes the bit Trasnmit Acknowledge Enable so the master can read the data */
void I2C_NACK(I2C_ChannelType channel){

	switch(channel){
	case I2C_0:
		/* Generate the No Acknowledge Signal to receive the data from the channel 0 of the I2C*/
		I2C0_C1 |= I2C_C1_TXAK_MASK;
		break;

	case I2C_1:
		/* Generate the No Acknowledge Signal to receive the data from the channel 1 of the I2C*/
		I2C1_C1 |= I2C_C1_TXAK_MASK;
		break;

	case I2C_2:
		/* Generate the No Acknowledge Signal to receive the data from the channel 2 of the I2C*/
		I2C2_C1 |= I2C_C1_TXAK_MASK;
		break;

	default:
		break;

	}


}
/* Changes the bit Repeat START to generated a signal condition to it is current master */
void I2C_repeted_Start(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/* Generates a repeated START condition to the channel 0 of the I2C */
		I2C0_C1 |= I2C_C1_RSTA_MASK;
		break;

	case I2C_1:
		/* Generates a repeated START condition to the channel 1 of the I2C */
		I2C1_C1 |= I2C_C1_RSTA_MASK;
		break;

	case I2C_2:
		/* Generates a repeated START condition to the channel 2 of the I2C */
		I2C2_C1 |= I2C_C1_RSTA_MASK;
		break;

	default:
		break;

	}
}
/* Write the data to be transmitted into the selected I2C channel */
void I2C_write_Byte(I2C_ChannelType channel,uint8 data){
	switch(channel){
	case I2C_0:
		/* Write the data into the the transmission buffer of the channel 0 of the I2C */
		I2C0_D = data;
		break;

	case I2C_1:
		/* Write the data into the the transmission buffer of the channel 1 of the I2C */
		I2C1_D = data;
		break;

	case I2C_2:
		/* Write the data into the the transmission buffer of the channel 2 of the I2C */
		I2C2_D = data;
		break;

	default:
		break;

	}
}
/* Return the data from the receiving buffer of the selected I2C channel*/
uint8  I2C_read_Byte(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/* Return the data from the receiving buffer of the channel 0 of the I2C */
		return I2C0_D;

	case I2C_1:
		/* Return the data from the receiving buffer of the channel 1 of the I2C */
		return I2C1_D;

	case I2C_2:
		/* Return the data from the receiving buffer of the channel 2 of the I2C */
		return I2C2_D;

	default:
		break;

	}
}
/* Set the Interrupt Flag bit of the selected channel of the I2C */
void I2C_wait(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/*Wait for the event that can set this bit in the channel 0 of the I2C*/
		while(((I2C0_S & I2C_S_IICIF_MASK) == FALSE));
		/*The bit is cleared*/
		I2C0_S |= I2C_S_IICIF_MASK;

		break;

	case I2C_1:
		/*Wait for the event that can set this bit in the channel 1 of the I2C*/
		while(((I2C1_S & I2C_S_IICIF_MASK) == FALSE));
		/*The bit is cleared*/
		I2C1_S |= I2C_S_IICIF_MASK;
		break;

	case I2C_2:
		/*Wait for the event that can set this bit in the channel 2  of the I2C*/
		while(((I2C2_S & I2C_S_IICIF_MASK) == FALSE));
		/*The bit is cleared*/
		I2C2_S |= I2C_S_IICIF_MASK;
		break;

	default:
		break;

	}
}
/* Indicates if the acknowledge signal was received in the channel selected return TRUE if the No Acknowledge signal is detected or FALSE if the Acknowledge signal was received */
uint16 I2C_get_ACK(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/* return TRUE if the No Acknowledge signal is detected or FALSE if the Acknowledge signal was received from the channel 0 of the I2C */
		return (I2C0_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	case I2C_1:
		/* return TRUE if the No Acknowledge signal is detected or FALSE if the Acknowledge signal was received from the channel 1 of the I2C */
		return (I2C1_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	case I2C_2:
		/* return TRUE if the No Acknowledge signal is detected or FALSE if the Acknowledge signal was received from the channel 2 of the I2C */
		return (I2C2_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	default:
		break;

	}
}
/* Change the bit MST to generated a START signal on the bus of the channel selected*/
void I2C_start(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/*START signal generated on the bus of the channel 0 of the I2C*/
		I2C0_C1 |= I2C_C1_MST_MASK;
		break;

	case I2C_1:
		/*START signal generated on the bus of the channel 1 of the I2C*/
		I2C1_C1 |= I2C_C1_MST_MASK;
		break;

	case I2C_2:
		/*START signal generated on the bus of the channel 2 of the I2C*/
		I2C2_C1 |= I2C_C1_MST_MASK;
		break;

	default:
		break;

	}
}

/* Change the bit MST to generated a STOP signal on the bus of the channel selected*/
void I2C_stop(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		/*STOP signal generated on the bus of the channel 0 of the I2C*/
		I2C0_C1 &= ~I2C_C1_MST_MASK;
		break;

	case I2C_1:
		/*START signal generated on the bus of the channel 0 of the I2C*/
		I2C1_C1 &= ~I2C_C1_MST_MASK;
		break;

	case I2C_2:
		/*START signal generated on the bus of the channel 0 of the I2C*/
		I2C2_C1 &= ~I2C_C1_MST_MASK;
		break;

	default:
		break;

	}

}
