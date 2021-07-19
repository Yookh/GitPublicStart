/*
 * Comp_Config.c
 *
 *  Created on: 2016. 9. 12.
 *      Author: Yoo Kwang Hyun
 */

#include "F28x_Project.h"

//DAC Value bits, scales the output of the DAC from 0 – 4095.
#define COMP_REF( x, y ) 	Cmpss##x##Regs.DACHVALS.bit.DACVAL = y;

void InitCMPSS( void );
void InternalCompRef(Uint16 Comp1Neg);

//Comperator 결과를 GPIO로 출력하기 위해선 x-Bar를 사용해야한다.
// 각각의 Trip out 핀에 매칭되고 xbar의 먹스는 datasheet를 참고해야한다.
// 설정하는게 조금 까다롭다.

void InitCMPSS(void)
{
	//------------------------------------------------------------------//

	//--Cmpss 1H GPIO25(XTRIPOUT2)-------------------------------------//	IF low
    EALLOW;
    // Configure CTRIPOUTH output pin
    OutputXbarRegs.OUTPUT2MUX0TO15CFG.bit.Mux0 = 0;	//0:CMPSS CTRIPOUT1H
    //Enable XTRIPOUT8 Mux for Output
    OutputXbarRegs.OUTPUT2MUXENABLE.bit.Mux0   = 1;

    //Enable CMPSS
    Cmpss1Regs.COMPCTL.bit.COMPDACE            = 1;
    // NEG signal comes from (1 :COMINxN / 0: DAC)
    Cmpss1Regs.COMPCTL.bit.COMPHSOURCE         = 0;

    //Use VDDA as the reference for DAC
    Cmpss1Regs.COMPDACCTL.bit.SELREF           = 0;
    //Set DAC to midpoint for arbitrary reference
//    Cmpss1Regs.DACHVALS.bit.DACVAL             = 2048;

    //Set Comparator Output Inverted.
    Cmpss1Regs.COMPCTL.bit.COMPHINV = 1;

    // Configure CTRIPOUT path
    //0 : Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss1Regs.COMPCTL.bit.CTRIPHSEL           = 2;
    Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL        = 2;				// Comparator Fitered Out

    Cmpss1Regs.CTRIPHFILCLKCTL.bit.CLKPRESCALE = 0;// 0~1023

    Cmpss1Regs.CTRIPHFILCTL.bit.SAMPWIN = 31;		// 0~31		// sample Window
    Cmpss1Regs.CTRIPHFILCTL.bit.THRESH = 31;		// 0~31		// at least Number. Window
    Cmpss1Regs.CTRIPHFILCTL.bit.FILINIT = 1;


    EDIS;
    //------------------------------------------------------------------//

    //--Cmpss 2H : GPIO26(XTRIPOUT3)-------------------------------------//	VF
    EALLOW;
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.Mux2 = 0;      // Select CMPSS2.CTRIPOUTH on Mux2
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.Mux2 = 1; 		// Enable MUX2 for CMPSS2.CTRIPOUTH

    //Enable CMPSS
    Cmpss2Regs.COMPCTL.bit.COMPDACE            = 1;
    // NEG signal comes from (1 :COMINxN / 0: DAC)
    Cmpss2Regs.COMPCTL.bit.COMPHSOURCE         = 1;

    //Use VDDA as the reference for DAC
    Cmpss2Regs.COMPDACCTL.bit.SELREF           = 0;
    //Set DAC to midpoint for arbitrary reference
//    Cmpss2Regs.DACHVALS.bit.DACVAL             = 2048;

    // Configure CTRIPOUT path
    //0 : Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss2Regs.COMPCTL.bit.CTRIPHSEL           = 0;
    Cmpss2Regs.COMPCTL.bit.CTRIPOUTHSEL        = 0;
    EDIS;


	//--Cmpss 4H : GPIO27(XTRIPOUT4)-------------------------------------//	arc
    EALLOW;
    // Configure CTRIPOUTH output pin
    OutputXbarRegs.OUTPUT4MUX0TO15CFG.bit.Mux6 = 0;	//0:CMPSS CTRIPOUT1H
    //Enable XTRIPOUT4 Mux for Output
    OutputXbarRegs.OUTPUT4MUXENABLE.bit.Mux6   = 1;

    //Enable CMPSS
    Cmpss4Regs.COMPCTL.bit.COMPDACE            = 1;

    // NEG signal comes from (1 :COMINxN / 0: DAC)
    Cmpss4Regs.COMPCTL.bit.COMPHSOURCE         = 1;

    //Use VDDA as the reference for DAC
    Cmpss4Regs.COMPDACCTL.bit.SELREF           = 0;
    //Set DAC to midpoint for arbitrary reference
//    Cmpss4Regs.DACHVALS.bit.DACVAL             = 2048;		//1.5V

    //Set Comparator Output Inverted.
    Cmpss4Regs.COMPCTL.bit.COMPHINV = 0;

    // Configure CTRIPOUT path
    //0 : Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss4Regs.COMPCTL.bit.CTRIPHSEL           = 0;
    Cmpss4Regs.COMPCTL.bit.CTRIPOUTHSEL        = 0;
    EDIS;
    //------------------------------------------------------------------//

	//--Cmpss 8H : GPIO31(XTRIPOUT8)-------------------------------------//	VF
    EALLOW;
    // Configure CTRIPOUTL output pin
    OutputXbarRegs.OUTPUT8MUX0TO15CFG.bit.Mux14 = 0;	//0:CMPSS CTRIPOUT1L
    //Enable XTRIPOUT8 Mux for Output
    OutputXbarRegs.OUTPUT8MUXENABLE.bit.Mux14   = 1;

    //Enable CMPSS
    Cmpss8Regs.COMPCTL.bit.COMPDACE            = 1;
    // NEG signal comes from (1 :COMINxN / 0: DAC)
    Cmpss8Regs.COMPCTL.bit.COMPHSOURCE         = 1;

    //Use VDDA as the reference for DAC
    Cmpss8Regs.COMPDACCTL.bit.SELREF           = 0;
    //Set DAC to midpoint for arbitrary reference
//    Cmpss8Regs.DACLVALS.bit.DACVAL             = 2048;

    // Configure CTRIPOUT path
    //0 : Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss8Regs.COMPCTL.bit.CTRIPLSEL           = 0;
    Cmpss8Regs.COMPCTL.bit.CTRIPOUTLSEL        = 0;
    EDIS;
    //------------------------------------------------------------------//
}

void InternalCompRef(Uint16 Comp1Neg)
{
	Comp1Neg = (Comp1Neg > 4095 ) ? 4095 : Comp1Neg;
//	Comp2Neg = (Comp2Neg > 1023 ) ? 1023 : Comp2Neg;
//	Comp3Neg = (Comp3Neg > 1023 ) ? 1023 : Comp3Neg;

	COMP_REF(1, Comp1Neg);
//	COMP_REF(2, Comp2Neg);
//	COMP_REF(3, Comp3Neg);
}
