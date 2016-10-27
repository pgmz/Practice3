/**
	\file
	\brief
		This is the header file for the I2C device driver.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Functions are not implemented.
 */

#ifndef I2C_H_
#define I2C_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"



#define I2C_MASTER_MODE	1
#define I2C_SLAVE_MODE 0

#define I2C_RX_MODE 0
#define I2C_TX_MODE 1

//#define SYSTEM_CLOCK 110000000
#define SYSTEM_CLOCK 21000000
/** Constant that represent the clock enable for GPIO A */
#define I2C0_CLOCK_GATING 0x40
/**
 * \brief This enum define the UART port to be used.
 */
typedef enum {I2C_0, I2C_1, I2C_2}I2C_ChannelType;



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
void I2C_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
  	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
  	 \param[in] channel It is the channel to be used.
  	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

  */
 uint8 I2C_busy(I2C_ChannelType channel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between master or slave mode.
  	 \param[in] channel It is the channel to be used.
  	 \param[in] masterOrSlave If == 1 master mode, if == 0 slave mode.
  	 \return void

  */
 void I2C_MST_OrSLV_Mode(I2C_ChannelType channel, uint8);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between transmitter mode or receiver mode.
  	 \param[in] channel It is the channel to be used.
  	 \param[in] txOrRx If == 1 transmitter mode, if == 0 slave mode.
  	 \return void

  */
 void I2C_TX_RX_Mode(I2C_ChannelType channel, uint8);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates the Not ACKnowledge that is needed when the master reads data.
 	 \param[in] channel It is the channel to be used.
  	 \return void

  */
 void I2C_NACK(I2C_ChannelType channel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates a repeated start that is needed when master reads data.
 	 \param[in] channel It is the channel to be used.
  	 \return void

  */
 void I2C_repeted_Start(I2C_ChannelType channel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It writes the data to be transmitted into the transmission buffer. When you want to
  	 	 write a value into the buffer you need to use this sentence I2C0_D = data. Avoid to use
  	 	 masks like this I2C0_D |= data.
 	 \param[in] channel It is the channel to be used.
  	 \return void

  */
void I2C_write_Byte(I2C_ChannelType channel, uint8);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 It reads data from the receiving buffer.
 	 \param[in] channel It is the channel to be used.
 	 \return void

 */
uint8  I2C_read_Byte(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
 	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
 	 \param[in] channel It is the channel to be used.
 	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

 */
void I2C_wait(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates if the acknowledge was received.
 	 \param[in] channel It is the channel to be used.
 	 \return This function returns a 0 logic if the acknowledge was received and returns 1 logic if the acknowledge was not received.

 */
uint16 I2C_get_ACK(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the start signal. When MST bit is changed from 0 to 1, a START signal is generated
 	 	 on the bus and master mode is selected. Also, inside the function the I2C is
 	 	 change to transmitter mode.
 	 \param[in] channel It is the channel to be used.
 	 \return void

 */
void I2C_start(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the stop signal. When this bit changes from 1 to 0, a STOP signal is generated
 	 	 and the mode of operation changes from master to slave. Also, inside the function the I2C is
 	 	 change to receiver mode.
 	 \param[in] channel It is the channel to be used.
 	 \return void

 */
void I2C_stop(I2C_ChannelType channel);

#endif /* I2C_H_ */
