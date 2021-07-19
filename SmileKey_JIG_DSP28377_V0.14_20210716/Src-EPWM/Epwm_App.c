/*
 * Epwm_App.c
 *
 *  Created on: 2016. 9. 26.
 *      Author: Yoo Kwang Hyun
 */

#include "F28x_Project.h"
#include "EpwmRegs_Defs.h"

void HwFaultInit( float Vo_Arc, float Io_Arc, float Vo_OVP, float Io_OCP, float Ir_OCP, float VOP_OVP, float IOP_OVP );

void HwFaultInit(float Vo_Arc, float Io_Arc, float Vo_OVP, float Io_OCP, float Ir_OCP, float VOP_OVP, float IOP_OVP  ) //  Max = 4000 -> 3.3V
{
	float Varc, Iarc, Vo, Io;
	float Ir, VoP, IoP;
	float PerV;

	//

	GPIO_SetupPinMux(17, GPIO_MUX_CPU1, 5);	// epwm 9B
	GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 5);	// epwm 10A
	GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 5);	// epwm 10B
	GPIO_SetupPinMux(20, GPIO_MUX_CPU1, 5);	// epwm 11A
	GPIO_SetupPinMux(21, GPIO_MUX_CPU1, 5);	// epwm 11B
	GPIO_SetupPinMux(22, GPIO_MUX_CPU1, 5);	// epwm 12A
	GPIO_SetupPinMux(23, GPIO_MUX_CPU1, 5);	// epwm 12B

//	GPIO_SetupPinMux(17, GPIO_MUX_CPU1, 5);	// epwm 9B
//	GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 5);	// epwm 10A

	PerV = HW_F_PRD/3.3f;			// Period/3.3V

	Varc = PerV * Vo_Arc;
	Iarc = PerV * Io_Arc;

	Vo = PerV * Vo_OVP;
	Io = PerV * Io_OCP;

	Ir = PerV * Ir_OCP;
	VoP = PerV * VOP_OVP;
	IoP = PerV * IOP_OVP;

	Varc = (Varc > HW_F_PRD)? HW_F_PRD : Varc;
	Iarc = (Iarc > HW_F_PRD)? HW_F_PRD : Iarc;

	Vo = (Vo > HW_F_PRD)? HW_F_PRD : Vo;
	Io = (Io > HW_F_PRD)? HW_F_PRD : Io;

	Ir = (Ir > HW_F_PRD)? HW_F_PRD : Ir;
	VoP = (VoP > HW_F_PRD)? HW_F_PRD : VoP;
	IoP = (IoP > HW_F_PRD)? HW_F_PRD : IoP;

	EPwm12Regs.CMPA.half.CMPA = ( Uint16 )Varc;		//DEF 3.3V
	EPwm12Regs.CMPB.half.CMPB = ( Uint16 )Iarc;		//DEF 3.3V
	EPwm9Regs.CMPB.half.CMPB = ( Uint16 )Vo;		//DEF 3.3V
	EPwm10Regs.CMPA.half.CMPA = ( Uint16 )Io;		//DEF 3.3V
	EPwm10Regs.CMPB.half.CMPB = ( Uint16 )Ir;		//DEF 3.3V
	EPwm11Regs.CMPA.half.CMPA = ( Uint16 )VoP;		//DEF 3.3V
	EPwm11Regs.CMPB.half.CMPB = ( Uint16 )IoP;		//DEF 3.3V
//	EPwm9Regs.CMPB.half.CMPB = ( Uint16 )Vin;		//DEF 3.3V
//	EPwm10Regs.CMPA.half.CMPA =( Uint16 )Vdc;		//DEF 1.8v
}


