/**
	\file
	\brief
		This is the source file for the PIT in Kinetis 64F, it has the functions needed
		to enable any PIT channel, and load values to any PIT channel.
	\author Patricio Gomez García
	\date	13/09/2016
 */

#include "DataTypeDefinitions.h"
#include "PIT.h"

PIT_MailBoxType PIT_MailBox0 = {
		FALSE, 0
};

PIT_MailBoxType PIT_MailBox1 = {
		FALSE, 0
};

PIT_MailBoxType PIT_MailBox2 = {
		FALSE, 0
};

PIT_MailBoxType PIT_MailBox3 = {
		FALSE, 0
};

void PIT_clockGating(){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

void PIT_enable(){
	PIT_MCR  &= ~(PIT_MCR_FRZ_MASK);
	PIT_MCR  &= ~(PIT_MCR_MDIS_MASK);
}

void PIT_disable(){
	PIT_MCR  |= PIT_MCR_FRZ_MASK;
	PIT_MCR  |= PIT_MCR_MDIS_MASK;
}

void PIT_timerInterruptEnable(PIT_TimerType pitTimer){
		switch(pitTimer){
		case PIT_0:
			PIT_TCTRL0 |= (PIT_TCTRL_TIE_MASK);
			break;
		case PIT_1:
			PIT_TCTRL1 |= (PIT_TCTRL_TIE_MASK);
			break;
		case PIT_2:
			PIT_TCTRL2 |= (PIT_TCTRL_TIE_MASK);
			break;
		case PIT_3:
			PIT_TCTRL3 |= (PIT_TCTRL_TIE_MASK);
			break;
	}
}

void PIT_timerInterruptDisable(PIT_TimerType pitTimer){
		switch(pitTimer){
		case PIT_0:
			PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK);
			break;
		case PIT_1:
			PIT_TCTRL1 &= ~(PIT_TCTRL_TIE_MASK);
			break;
		case PIT_2:
			PIT_TCTRL2 &= ~(PIT_TCTRL_TIE_MASK);
			break;
		case PIT_3:
			PIT_TCTRL3 &= ~(PIT_TCTRL_TIE_MASK);
			break;
	}
}

void PIT_timerEnable(PIT_TimerType pitTimer){
		switch(pitTimer){
		case PIT_0:
			PIT_TCTRL0 |= (PIT_TCTRL_TEN_MASK);
			break;
		case PIT_1:
			PIT_TCTRL1 |= (PIT_TCTRL_TEN_MASK);
			break;
		case PIT_2:
			PIT_TCTRL2 |= (PIT_TCTRL_TEN_MASK);
			break;
		case PIT_3:
			PIT_TCTRL3 |= (PIT_TCTRL_TEN_MASK);
			break;
	}
}

void PIT_timerDisable(PIT_TimerType pitTimer){
		switch(pitTimer){
		case PIT_0:
			PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);
			break;
		case PIT_1:
			PIT_TCTRL1 &= ~(PIT_TCTRL_TEN_MASK);
			break;
		case PIT_2:
			PIT_TCTRL2 &= ~(PIT_TCTRL_TEN_MASK);
			break;
		case PIT_3:
			PIT_TCTRL3 &= ~(PIT_TCTRL_TEN_MASK);
			break;
	}
}

void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period){

	/*specified formula to obtain the delay*/
	float delay = (((period*(systemClock))/2)-1);
	switch(pitTimer){
		case PIT_0:
			PIT_LDVAL0 = (uint32)delay;
			break;
		case PIT_1:
			PIT_LDVAL1 = (uint32)delay;
			break;
		case PIT_2:
			PIT_LDVAL2 = (uint32)delay;
			break;
		case PIT_3:
			PIT_LDVAL3 = (uint32)delay;
			break;
	}

}

void PIT0_clearInterrupt(){
	/*Clear interruption flag for PIT channel 0*/
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL0;
	/*Enable the timer again*/
	PIT_timerInterruptEnable(PIT_0);
	PIT_timerEnable(PIT_0);
}

void PIT1_clearInterrupt(){
	/*Clear interruption flag for PIT channel 0*/
	PIT_TFLG1 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL1;
	/*Enable the timer again*/
	PIT_timerInterruptEnable(PIT_1);
	PIT_timerEnable(PIT_1);
}

void PIT2_clearInterrupt(){
	/*Clear interruption flag for PIT channel 0*/
	PIT_TFLG2 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL2;
	/*Enable the timer again*/
	PIT_timerInterruptEnable(PIT_2);
	PIT_timerEnable(PIT_2);
}

void PIT3_clearInterrupt(){
	/*Clear interruption flag for PIT channel 3*/
	PIT_TFLG3 |= PIT_TFLG_TIF_MASK;
	PIT_TCTRL3;
	/*Enable the timer again*/
	PIT_timerInterruptEnable(PIT_3);
	PIT_timerEnable(PIT_3);
}

void PIT0_IRQHandler(){
	PIT0_clearInterrupt();
    PIT_MailBox0.flag = TRUE;
 }

void PIT1_IRQHandler(){
	PIT1_clearInterrupt();
	PIT_MailBox1.flag = TRUE;
 }

void PIT2_IRQHandler(){
	PIT2_clearInterrupt();
	PIT_MailBox2.flag = TRUE;
}

void PIT3_IRQHandler(){
	PIT3_clearInterrupt();
	PIT_MailBox3.flag = TRUE;
}

uint32 PIT_readTimerValue(PIT_TimerType pitTimer){
	/*According to the pit Timer, we return the value of the counter in the requested
	 * channel*/
	switch(pitTimer){
	case PIT_0:
		return PIT_CVAL0;
	case PIT_1:
		return PIT_CVAL1;
	case PIT_2:
		return PIT_CVAL2;
	case PIT_3:
		return PIT_CVAL3;
	}
	return FALSE;
}

uint8 PIT_mailBoxFlag(PIT_TimerType pitTimer){
	uint8 temp;
	switch(pitTimer){
	case PIT_0:
		temp = PIT_MailBox0.flag;
		PIT_MailBox0.flag = FALSE;
		return temp;
	case PIT_1:
		temp = PIT_MailBox1.flag;
		PIT_MailBox1.flag = FALSE;
		return temp;
	case PIT_2:
		temp = PIT_MailBox2.flag;
		PIT_MailBox2.flag = FALSE;
		return temp;
	case PIT_3:
		temp = PIT_MailBox3.flag;
		PIT_MailBox3.flag = FALSE;
		return temp;
	}
}

