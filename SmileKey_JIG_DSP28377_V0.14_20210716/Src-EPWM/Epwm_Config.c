/*
 * Epwm_Config.c
 *
 *  Created on: 2016. 9. 9.
 *      Author: Yoo Kwang Hyun
 */

#include "F28x_Project.h"
#include "EpwmRegs_Defs.h"
//###########################################################################
//
// FILE:    EpwmConfig_F2806x.c
//
// TITLE:   F2806x EPWM Initialization & Support Functions.
//
//###########################################################################
// $PSTEK Release: F2806x C/C++ Header Files and Peripheral Examples V001 $
// $Release Date: MAR 16, 2016 $
// $Copyright: Copyright (C) PSTEK.CO.LTD
// &Author	Yoo Kwang Hyun
//###########################################################################


void Initialize_Epwm( void );
void InitEPwm_ClockDivide( void );
void InitEPwm_SyncSel( void );
void InitEPwm_ShadowRegs( void );
void InitEPwm_OutModeSel( void );


void EpwmSoc_Cfg(  Uint16 PwmCh  );

void InitEPwm_Regs( void );

void EpwmIntCfg( void );

void ConfigureEPWM(void);

void Initialize_Epwm( void )
{
	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

	InitEPwm_ClockDivide();
	InitEPwm_SyncSel();
	InitEPwm_ShadowRegs();
	InitEPwm_OutModeSel();
	InitEPwm_Regs();
	EpwmIntCfg();

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;


	// Initally disable Free/Soft Bits
	EPwm1Regs.TBCTL.bit.FREE_SOFT = 0;
}

void InitEPwm_Regs( void )
{
	EPwm1Regs.TBPRD 		 = EPWM1_PERIOD;	// Set up PWM1 Period
	EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA;		// CompareA event at PWM falling.
	EPwm1Regs.CMPB.half.CMPB = EPWM1_CMPB;
	EPwm1Regs.DBRED 		 = EPWM1_DBRED; 	// Dead Band Rising Edge Delay
	EPwm1Regs.DBFED 		 = EPWM1_DBFED; 	// Dead Band falling Edge Delay
	EPwm1Regs.TBPHS.half.TBPHS = 0;

	EPwm2Regs.TBPRD 		 = EPWM2_PERIOD;	// Set up PWM1 Period
	EPwm2Regs.CMPA.half.CMPA = EPWM2_CMPA;		// CompareA event at PWM falling.
	EPwm2Regs.CMPB.half.CMPB = EPWM2_CMPB;
	EPwm2Regs.DBRED 		 = EPWM2_DBRED; 	// Dead Band Rising Edge Delay
	EPwm2Regs.DBFED 		 = EPWM2_DBFED; 	// Dead Band falling Edge Delay
	EPwm2Regs.TBPHS.half.TBPHS = 0;

	EPwm3Regs.TBPRD 		 = EPWM3_PERIOD;	// Set up PWM1 Period
	EPwm3Regs.CMPA.half.CMPA = EPWM3_CMPA;		// CompareA event at PWM falling.
	EPwm3Regs.CMPB.half.CMPB = EPWM3_CMPB;
	EPwm3Regs.DBRED 		 = EPWM3_DBRED; 	// Dead Band Rising Edge Delay
	EPwm3Regs.DBFED 		 = EPWM3_DBFED; 	// Dead Band falling Edge Delay
	EPwm3Regs.TBPHS.half.TBPHS = 0;

	EPwm4Regs.TBPRD 		 = EPWM4_PERIOD;	// Set up PWM1 Period
	EPwm4Regs.CMPA.half.CMPA = EPWM4_CMPA;		// CompareA event at PWM falling.
	EPwm4Regs.CMPB.half.CMPB = EPWM4_CMPB;
	EPwm4Regs.DBRED 		 = EPWM4_DBRED; 	// Dead Band Rising Edge Delay
	EPwm4Regs.DBFED 		 = EPWM4_DBFED; 	// Dead Band falling Edge Delay
	EPwm4Regs.TBPHS.half.TBPHS = 0;

	EPwm5Regs.TBPRD 		 = EPWM5_PERIOD;	// Set up PWM1 Period
	EPwm5Regs.CMPA.half.CMPA = EPWM5_CMPA;		// CompareA event at PWM falling.
	EPwm5Regs.CMPB.half.CMPB = EPWM5_CMPB;
	EPwm5Regs.DBRED 		 = EPWM5_DBRED; 	// Dead Band Rising Edge Delay
	EPwm5Regs.DBFED 		 = EPWM5_DBFED; 	// Dead Band falling Edge Delay
	EPwm5Regs.TBPHS.half.TBPHS = 0;

	EPwm6Regs.TBPRD 		 = EPWM6_PERIOD;	// Set up PWM1 Period
	EPwm6Regs.CMPA.half.CMPA = EPWM6_CMPA;		// CompareA event at PWM falling.
	EPwm6Regs.CMPB.half.CMPB = EPWM6_CMPB;
	EPwm6Regs.DBRED 		 = EPWM6_DBRED; 	// Dead Band Rising Edge Delay
	EPwm6Regs.DBFED 		 = EPWM6_DBFED; 	// Dead Band falling Edge Delay
	EPwm6Regs.TBPHS.half.TBPHS = 0;

	EPwm7Regs.TBPRD 		 = EPWM7_PERIOD;	// Set up PWM1 Period
	EPwm7Regs.CMPA.half.CMPA = EPWM7_CMPA;		// CompareA event at PWM falling.
	EPwm7Regs.CMPB.half.CMPB = EPWM7_CMPB;
	EPwm7Regs.DBRED 		 = EPWM7_DBRED; 	// Dead Band Rising Edge Delay
	EPwm7Regs.DBFED 		 = EPWM7_DBFED; 	// Dead Band falling Edge Delay
	EPwm7Regs.TBPHS.half.TBPHS = 0;

	EPwm8Regs.TBPRD 		 = EPWM8_PERIOD;	// Set up PWM1 Period
	EPwm8Regs.CMPA.half.CMPA = EPWM8_CMPA;		// CompareA event at PWM falling.
	EPwm8Regs.CMPB.half.CMPB = EPWM8_CMPB;
	EPwm8Regs.DBRED 		 = EPWM8_DBRED; 	// Dead Band Rising Edge Delay
	EPwm8Regs.DBFED 		 = EPWM8_DBFED; 	// Dead Band falling Edge Delay
	EPwm8Regs.TBPHS.half.TBPHS = 0;

	EPwm9Regs.TBPRD 		 = EPWM9_PERIOD;	// Set up PWM1 Period
	EPwm9Regs.CMPA.half.CMPA = EPWM9_CMPA;		// CompareA event at PWM falling.
	EPwm9Regs.CMPB.half.CMPB = EPWM9_CMPB;
	EPwm9Regs.DBRED 		 = EPWM9_DBRED; 	// Dead Band Rising Edge Delay
	EPwm9Regs.DBFED 		 = EPWM9_DBFED; 	// Dead Band falling Edge Delay
	EPwm9Regs.TBPHS.half.TBPHS = 0;

	EPwm10Regs.TBPRD 		 = EPWM10_PERIOD;	// Set up PWM1 Period
	EPwm10Regs.CMPA.half.CMPA = EPWM10_CMPA;		// CompareA event at PWM falling.
	EPwm10Regs.CMPB.half.CMPB = EPWM10_CMPB;
	EPwm10Regs.DBRED 		 = EPWM10_DBRED; 	// Dead Band Rising Edge Delay
	EPwm10Regs.DBFED 		 = EPWM10_DBFED; 	// Dead Band falling Edge Delay
	EPwm10Regs.TBPHS.half.TBPHS = 0;

	EPwm11Regs.TBPRD 		 = EPWM11_PERIOD;	// Set up PWM1 Period
	EPwm11Regs.CMPA.half.CMPA = EPWM11_CMPA;		// CompareA event at PWM falling.
	EPwm11Regs.CMPB.half.CMPB = EPWM11_CMPB;
	EPwm11Regs.DBRED 		 = EPWM11_DBRED; 	// Dead Band Rising Edge Delay
	EPwm11Regs.DBFED 		 = EPWM11_DBFED; 	// Dead Band falling Edge Delay
	EPwm11Regs.TBPHS.half.TBPHS = 0;

	EPwm12Regs.TBPRD 		 = EPWM12_PERIOD;	// Set up PWM1 Period
	EPwm12Regs.CMPA.half.CMPA = EPWM12_CMPA;		// CompareA event at PWM falling.
	EPwm12Regs.CMPB.half.CMPB = EPWM12_CMPB;
	EPwm12Regs.DBRED 		 = EPWM12_DBRED; 	// Dead Band Rising Edge Delay
	EPwm12Regs.DBFED 		 = EPWM12_DBFED; 	// Dead Band falling Edge Delay
	EPwm12Regs.TBPHS.half.TBPHS = 0;

	EPwm12Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm11Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm10Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm9Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm8Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm7Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm6Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm5Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm4Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm3Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm2Regs.TBCTR = 0xffff;					 // Clear timer counter
	EPwm1Regs.TBCTR = 0xffff;					 // Clear timer counter
}

void InitEPwm_ClockDivide( void )
{
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm1Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm2Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm3Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm4Regs.TBCTL.bit.HSPCLKDIV = 7; // divide 1
	EPwm4Regs.TBCTL.bit.CLKDIV 	  = 7; // divide 1

	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 14
	EPwm5Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 128

	EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 14
	EPwm6Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 128

	EPwm7Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm7Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm8Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm8Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm9Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm9Regs.TBCTL.bit.CLKDIV 	  = 0; // divide 1

	EPwm10Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm10Regs.TBCTL.bit.CLKDIV    = 0; // divide 1

	EPwm11Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm11Regs.TBCTL.bit.CLKDIV    = 0; // divide 1

	EPwm12Regs.TBCTL.bit.HSPCLKDIV = 0; // divide 1
	EPwm12Regs.TBCTL.bit.CLKDIV    = 0; // divide 1
}

void InitEPwm_SyncSel( void )
{
/*					Sync Scheme
*	============================================
*	 Pwm1 --> pwm2 --> pwm3 --> pwm4 --> pwm'x'
*	  |--> ecap1
*	============================================
*/
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;		// Sync Out 0
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;		// Compare B out
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;		//
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm9Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm11Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwm12Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

	// Allow each timer to be sync'ed
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;		// Sync Disable
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;		// Sync Enable
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;		// Sync Disable
	EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm8Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm9Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm11Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm12Regs.TBCTL.bit.PHSEN = TB_DISABLE;
}

void InitEPwm_ShadowRegs( void )
{
	// All Shadow and Counter Zero Load

	EPwm1Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm2Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm3Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm4Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm5Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm6Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm7Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm8Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm9Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm9Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm10Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm11Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm11Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm11Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm11Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	EPwm12Regs.TBCTL.bit.PRDLD 	   = TB_SHADOW;
	EPwm12Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm12Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm12Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm12Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
}

// Count Mode, Action Qualification
void InitEPwm_OutModeSel( void )
{
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_FREEZE;	// Count up
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up
	EPwm12Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;	// Count up

	EPwm1Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm2Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm3Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm4Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm5Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm6Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm7Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm8Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm9Regs.DBCTL.bit.OUT_MODE =  DB_DISABLE;
	EPwm10Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm11Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm12Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm11Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm12Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;


	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm7Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	EPwm9Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm9Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm9Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm9Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EPwm10Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm10Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm10Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EPwm11Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm11Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm11Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm11Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EPwm12Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm12Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm12Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm12Regs.AQCTLB.bit.CBU = AQ_CLEAR;
}

void EpwmIntCfg(void)
{
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	// ET_CTRU_CMPA;//ET_CTRU_CMPB;	// 2011.01.30
	EPwm1Regs.ETSEL.bit.INTEN = 1;				// Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;			// Generate INT on 1st event

	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	//
	EPwm4Regs.ETSEL.bit.INTEN = 0;				// Enable INT
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;			// Generate INT on 1st event

	EPwm1Regs.ETCLR.bit.INT = 1;				// Clear INT flag for EPWM1
	EPwm4Regs.ETCLR.bit.INT = 1;				// Clear INT flag for EPWM4
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Acknowledge this interrupt to receive more interrupts from group 3

}
