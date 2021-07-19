/*
 * DAC_Config_F28377.c
 *
 *  Created on: 2016. 9. 23.
 *      Author: Yoo Kwang Hyun
 */
#include "F28x_Project.h"
#include "F2837xD_Dac_defines.h"

void InitCfgDAC( void );


void InitCfgDAC( void )
{
	//Unwanted others Comment lines
/*	EALLOW;
	// DAC Channel A Cfg
	DacaRegs.DACCTL.bit.MODE = 0;			// Not Used.
	DacaRegs.DACCTL.bit.DACREFSEL = REF_VREF_HI;		// VREFHI/VSSA are the reference voltage
	DacaRegs.DACCTL.bit.LOADMODE = LOAD_SYSCLK;		// Next System Clk Load
	DacaRegs.DACCTL.bit.SYNCSEL = SYNC_EPWM1;		// ePWM1 Sync

	DacaRegs.DACOUTEN.bit.DACOUTEN = DA_ENABLE;		// DAC-A Out Enable


	// DAC Channel B Cfg
	DacbRegs.DACCTL.bit.MODE = 0;			// Not Used.
	DacbRegs.DACCTL.bit.DACREFSEL = REF_VREF_HI;		// VREFHI/VSSA are the reference voltage
	DacbRegs.DACCTL.bit.LOADMODE = LOAD_SYSCLK;		// Next System Clk Load
	DacbRegs.DACCTL.bit.SYNCSEL = SYNC_EPWM1;		// ePWM1 Sync

	DacbRegs.DACOUTEN.bit.DACOUTEN = DA_ENABLE;		// DAC-B out Enable


//	DaccRegs.DACCTL.all = 1; //adc VREFHI/VSSA are the reference voltage
//	DaccRegs.DACOUTEN.bit.DACOUTEN = 1;

	//delay for 1ms to allow ADC time to power up
	DELAY_US(1000);
	EDIS;
*/
}



