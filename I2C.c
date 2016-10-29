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



/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 Configures the I2C port based on the input parameters.
  	 	 Also, internally this function configures the GPIO, pin control register and clock gating, to be used as I2C.
  	 	 It is recommended to use pin 2 and 3 of GPIOB.
  	 \param[in] channel It is the channel to be used.
  	 \param[in] systemClock Frequency of the system.
  	 \param[in] baudRate baud rate between MCU and I2C device.
  	 \return void

 */

void I2C_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate){
	switch(channel){
	case I2C_0:
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
		I2C0_F = 0x56;
		//56 disque, 100k
		//E disque, 400k
		//8c disque, 9600
		//14 sabe!!
		I2C0_C1 |= I2C_C1_IICEN_MASK;
		//I2C0_SMB |= I2C_SMB_FACK_MASK;
		break;
	case I2C_1:
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
		I2C1_F = 0x14;
		I2C1_C1 |= I2C_C1_IICEN_MASK;
		break;

	case I2C_2:		
		SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK; 
		I2C2_F = 0x14;
		I2C2_C1 |= I2C_C1_IICEN_MASK;
		break;

	default:
		break;

	}


}

uint8 I2C_busy(I2C_ChannelType channel){

	switch(channel){

	case I2C_0:

		return ((I2C0_S & I2C_S_BUSY_MASK) == FALSE)?(FALSE):(TRUE);

	case I2C_1:

		if((I2C1_S & I2C_S_BUSY_MASK) == FALSE ){
			return FALSE;
		}else{
			return TRUE;
		}
		break;

	case I2C_2:

		if((I2C2_S & I2C_S_BUSY_MASK) == FALSE ){
			return FALSE;
		}else{
			return TRUE;
		}
		break;


	default:
		break;

	}


}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 It selects between master or slave mode.
  	 \param[in] masterOrSlave If == 1 master mode, if == 0 slave mode.
  	 \return void

 */
void I2C_MST_OrSLV_Mode(I2C_ChannelType channel, uint8 master_slave){
	switch(channel){

	case I2C_0:
		if(master_slave == FALSE){
			I2C1_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			I2C1_C1 |= I2C_C1_MST_MASK;
		}
		break;

	case I2C_1:
		if(master_slave == FALSE){
			I2C1_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			I2C1_C1 |= I2C_C1_MST_MASK;
		}
		break;

	case I2C_2:
		if(master_slave == FALSE){
			I2C1_C1 &= ~(I2C_C1_MST_MASK);
		}
		else{
			I2C1_C1 |= I2C_C1_MST_MASK;
		}
		break;
	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 It selects between transmitter mode or receiver mode.
  	 \param[in] txOrRx If == 1 transmitter mode, if == 0 slave mode.
  	 \return void

 */
void I2C_TX_RX_Mode(I2C_ChannelType channel, uint8 TX_RX){
	switch(channel){

	case I2C_0:
		if(TX_RX == FALSE){
			I2C0_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			I2C0_C1 |= I2C_C1_TX_MASK;
		}
		break;

	case I2C_1:
		if(TX_RX == FALSE){
			I2C1_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			I2C1_C1 |= I2C_C1_TX_MASK;
		}
		break;

	case I2C_2:
		if(TX_RX == FALSE){
			I2C2_C1 &= ~(I2C_C1_TX_MASK);
		}
		else{
			I2C2_C1 |= I2C_C1_TX_MASK;
		}
		break;
	}

}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 It generates the Not ACKnowledge that is needed when the master reads data.
  	 \return void

 */
void I2C_NACK(I2C_ChannelType channel){

	switch(channel){
	case I2C_0:
		//I2C0_C1 &= I2C_C1_TXAK_MASK;
		I2C0_C1 |= I2C_C1_TXAK_MASK;
		break;

	case I2C_1:
		//I2C1_C1 &= I2C_C1_TXAK_MASK;
		I2C1_C1 |= I2C_C1_TXAK_MASK;
		break;

	case I2C_2:
		//I2C2_C1 &= I2C_C1_TXAK_MASK;
		I2C2_C1 |= I2C_C1_TXAK_MASK;
		break;

	default:
		break;

	}


}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 It generates a repeated start that is needed when master reads data.
  	 \return void

 */
void I2C_repeted_Start(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		I2C0_C1 |= I2C_C1_RSTA_MASK;
		break;

	case I2C_1:
		I2C1_C1 |= I2C_C1_RSTA_MASK;
		break;

	case I2C_2:
		I2C2_C1 |= I2C_C1_RSTA_MASK;
		break;

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
  	 \brief
  	 	 It writes the data to be transmitted into the transmission buffer. When you want to
  	 	 write a value into the buffer you need to use this sentence I2C0_D = data. Avoid to use
  	 	 masks like this I2C0_D |= data.
  	 \return void

 */
void I2C_write_Byte(I2C_ChannelType channel,uint8 data){
	switch(channel){
	case I2C_0:
		I2C0_D = data;
		break;

	case I2C_1:
		I2C1_D = data;
		break;

	case I2C_2:
		I2C2_D = data;
		break;

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 It reads data from the receiving buffer.
 	 \return void

 */
uint8  I2C_read_Byte(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		return I2C0_D;

	case I2C_1:
		return I2C1_D;

	case I2C_2:
		return I2C2_D;

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
 	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
 	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

 */
void I2C_wait(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		while(((I2C0_S & I2C_S_IICIF_MASK) == FALSE));
		I2C0_S |= I2C_S_IICIF_MASK;

		break;

	case I2C_1:
		while(((I2C1_S & I2C_S_IICIF_MASK) == FALSE));
		I2C1_S |= I2C_S_IICIF_MASK;
		break;

	case I2C_2:
		while(((I2C2_S & I2C_S_IICIF_MASK) == FALSE));
		I2C2_S |= I2C_S_IICIF_MASK;
		break;

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates if the acknowledge was received.
 	 \return This function returns a 0 logic if the acknowledge was received and returns 1 logic if the acknowledge was not received.

 */
uint16 I2C_get_ACK(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		return (I2C0_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	case I2C_1:
		return (I2C1_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	case I2C_2:
		return (I2C2_S & I2C_S_RXAK_MASK == FALSE)?(FALSE):(TRUE);

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the start signal. When MST bit is changed from 0 to 1, a START signal is generated
 	 	 on the bus and master mode is selected. Also, inside the function the I2C is
 	 	 change to transmitter mode.
 	 \return void

 */
void I2C_start(I2C_ChannelType channel){
	switch(channel){
	case I2C_0:
		I2C0_C1 |= I2C_C1_IICEN_MASK;

		//I2C0_C1 |= I2C_C1_TX_MASK;
		I2C0_C1 |= I2C_C1_MST_MASK;
		break;

	case I2C_1:
		I2C1_C1 |= I2C_C1_TX_MASK;
		I2C1_C1 |= I2C_C1_MST_MASK;
		break;

	case I2C_2:
		I2C2_C1 |= I2C_C1_TX_MASK;
		I2C2_C1 |= I2C_C1_MST_MASK;
		break;

	default:
		break;

	}
}
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the stop signal. When this bit changes from 1 to 0, a STOP signal is generated
 	 	 and the mode of operation changes from master to slave. Also, inside the function the I2C is
 	 	 change to receiver mode.
 	 \return void

 */
void I2C_stop(I2C_ChannelType channel){
	switch(channel){
		case I2C_0:
			I2C0_C1 &= ~I2C_C1_MST_MASK;
			//I2C0_C1 &= ~I2C_C1_TX_MASK;
			break;

		case I2C_1:
			I2C1_C1 &= ~I2C_C1_MST_MASK;
			I2C1_C1 &= ~I2C_C1_TX_MASK;
			break;

		case I2C_2:
			I2C2_C1 &= ~I2C_C1_MST_MASK;
			I2C2_C1 &= ~I2C_C1_TX_MASK;
			break;

		default:
			break;

		}

}
