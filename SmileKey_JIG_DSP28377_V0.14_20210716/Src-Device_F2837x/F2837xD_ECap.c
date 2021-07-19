//###########################################################################
// FILE:   F2837xD_ECap.c
// TITLE:  F2837xD eCAP Initialization & Support Functions.
//###########################################################################
// $TI Release: F2837xD Support Library v100 $
// $Release Date: Mon Dec  9 12:58:09 CST 2013 $
//###########################################################################

#include "F2837xD_Device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File

//---------------------------------------------------------------------------
// InitECap:
//---------------------------------------------------------------------------
// This function initializes the eCAP(s) to a known state.
void InitECap(void)
{
    // Initialize eCAP1/2/3/4/5/6
	InitAPwm1Gpio();
	InitECap3Gpio(26);
    //tbd...

}

//---------------------------------------------------------------------------
// Example: InitECapGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ECAP pins
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
// Caution:
// For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.

void InitECapGpio()
{
}

void InitECap1Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT7SELECT = pin; 		// Set eCAP1 source to GPIO-pin
	EDIS;
}

void InitECap2Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT8SELECT = pin; 		// Set eCAP2 source to GPIO-pin
	EDIS;
}

void InitECap3Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT9SELECT = pin; 		// Set eCAP3 source to GPIO-pin
	EDIS;
}

void InitECap4Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT10SELECT = pin; 		// Set eCAP4 source to GPIO-pin
	EDIS;
}

void InitECap5Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT11SELECT = pin; 		// Set eCAP5 source to GPIO-pin
	EDIS;
}

void InitECap6Gpio(Uint16 pin)
{
	EALLOW;
	TrigRegs.INPUT12SELECT = pin; 		// Set eCAP6 source to GPIO-pin
	EDIS;
}

void InitAPwm1Gpio()
{
	EALLOW;
	OutputXbarRegs.OUTPUT2MUX0TO15CFG.bit.Mux2 = 3;	// Select ECAP2.OUT on Mux0
	OutputXbarRegs.OUTPUT2MUXENABLE.bit.Mux2 = 1;	// Enable MUX0 for ECAP2.OUT

	GPIO_SetupPinMux(25, GPIO_MUX_CPU2, 1);//TEST PIN
	GPIO_SetupPinOptions(25, GPIO_OUTPUT, GPIO_PUSHPULL);
	EDIS;

	EALLOW;

	OutputXbarRegs.OUTPUT1MUX0TO15CFG.bit.Mux0 = 3;	// Select ECAP1.OUT on Mux0
	OutputXbarRegs.OUTPUT1MUXENABLE.bit.Mux0 = 1;	// Enable MUX0 for ECAP1.OUT
	//GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 6;	// Select XTRIPOUT3 on GPIO14

	GPIO_SetupPinMux(24, GPIO_MUX_CPU1, 1);//TEST PIN
	GPIO_SetupPinOptions(24, GPIO_OUTPUT, GPIO_PUSHPULL);

	EDIS;
/*	EALLOW;

	OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.Mux4 = 3;	// Select ECAP3.OUT on Mux0
	OutputXbarRegs.OUTPUT3MUXENABLE.bit.Mux4 = 1;	// Enable MUX0 for ECAP2.OUT

	GPIO_SetupPinMux(26, GPIO_MUX_CPU1, 1);//TEST PIN
	GPIO_SetupPinOptions(26, GPIO_OUTPUT, GPIO_PUSHPULL);

	EDIS;*/
}
//===========================================================================
// End of file.
//===========================================================================
