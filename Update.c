#include "UART.h"
#include "GPIO.h"


const uint8 DirectionIN[] = "0000";
/*
const DisplayStruct DefaultDisplay[9] = {{0,DEFAULT_DISPLAY},
										 {1,RD_MEMORY},
										 {2,WR_MEMORY},
										 {3,TIME_SET},
										 {4,DATE_SET},
										 {5,TIME_FORMAT},
										 {6,RD_TIME},
										 {7,RD_DATE},
										 {8,TERM2_COM},
										 {9,LCD_ECO}};
 */

void SYSUPD_init(){
	SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
	PORTB_PCR(16) = PORT_PCR_MUX(3);
	PORTB_PCR(17) = PORT_PCR_MUX(3);
	UART_init (UART_0,  21000000, BD_115200);
	UART0_interruptEnable(UART_0);
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_10);
	EnableInterrupts;
}

void DEFAULT_DISPLAY(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in dark gray and background in white*/
	UART_putString(UART_0,"\033[0;37;40m");
	/** VT100 command for text in red and background in green*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0, "Comunicacion por UART e I2C\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[02;01H");
	UART_putString(UART_0, "Opciones:\r");
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[04;10H");
	UART_putString(UART_0, "1) Leer Memoria I2C\r");
	UART_putString(UART_0,"\033[05;10H");
	UART_putString(UART_0, "2) Escribir Memoria I2C\r");
	UART_putString(UART_0,"\033[06;10H");
	UART_putString(UART_0, "3) Escribir hora:\r");
	UART_putString(UART_0,"\033[07;10H");
	UART_putString(UART_0, "4) Escribir fecha:\r");
	UART_putString(UART_0,"\033[08;10H");
	UART_putString(UART_0, "5) Formato de hora:\r");
	UART_putString(UART_0,"\033[09;10H");
	UART_putString(UART_0, "6) Leer hora:\r");
	UART_putString(UART_0,"\033[10;10H");
	UART_putString(UART_0, "7) Leer fecha:\r");
	UART_putString(UART_0,"\033[11;10H");
	UART_putString(UART_0, "8) Comunicacion con terminal 2:\r");
	UART_putString(UART_0,"\033[12;10H");
	UART_putString(UART_0, "9) ECO en LCD:\r");

	if(UART0_MailBox.flag)
	{
		/**Sends to the PCA the received data in the mailbox*/
		UART_putChar(UART_0, UART0_MailBox.mailBox);
		/**clear the reception flag*/
		UART0_MailBox.flag =0;
	}

	swithcMenu(UART0_MailBox.mailBox);
}

void RD_MEMORY(){
	int i = 0;

	UART_putString(UART_0,"\033[2J");
	UART_putString(UART_0,"\033[01;01H");
	UART_putString(UART_0, "Dirreccion de lectyra: 0x\r");

	for(i = 0; i < 4; i++){
		if(UART0_MailBox.flag){
			/**Sends to the PCA the received data in the mailbox*/
			DirectionIN[i] = UART_putChar (UART_0, UART0_MailBox.mailBox);

			/**clear the reception flag*/
			UART0_MailBox.flag =0;
		}
	}

}

void SYSUPD_update(uint8){

}

void switchMenu(uint8 option){
	switch(option){

	case DEFAULT_DISP:

		break;


	case READ_MEMORY:

		break;

	case WRITE_MEMORY:

		break;

	case SET_TIME:

		break;

	case SET_DATE:

		break;

	case TIME_FORM:

		break;

	case READ_TIME:

		break;

	case READ_DATE:

		break;

	case COM_TERM2:

		break;

	case ECO_LCD:

		break;
	}

}

void WR_MEMORY(){

}



void TIME_SET(){

}

void DATE_SET(){

}

void TIME_FORMAT(){

}

void RD_TIME(){

}

void WR_TIME(){

}

void TERM2_COM(){

}

void LCD_ECO(){

}







