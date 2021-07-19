/*
 * Gpio_Ctrl.c
 *
 *  Created on: 2017. 4. 13.
 *      Author: YooKH
 */


#include "F28x_Project.h"
#include "../define.h"

Uint32 	ReadInputStatus( void );
float 	SW_LPF( float filter, Uint16 input );
Uint32 	LpfExtGpioFault( Uint32 Input_status );

Uint32 GPtest;

#pragma CODE_SECTION(ReadInputStatus, "ramfuncs");
Uint32 ReadInputStatus(void)
{
/*	Uint32	present_status;

 	present_status=0;
	IN_SEL(0,0,0);  //A
		if( MUX_IN0 ) 	  		present_status|=BIT0;		//SCR FAULT
		if( MUX_IN1 == 0 ) 		present_status|=BIT1;		//IOP OCP
		if( MUX_IN2 )			present_status|=BIT16;
	IN_SEL(0,0,1);  //B
		if( MUX_IN0 ) 			present_status|=BIT2;		//FAN FUALT
		if( MUX_IN1==0 ) 		present_status|=BIT3;		//UV LO
		if( MUX_IN2 )			present_status|= BIT17;
	IN_SEL(0,1,0);  //C
		if( MUX_IN0 ) 			present_status|=BIT4;		//OTP FAULT
		if( MUX_IN1==0 ) 		present_status|=BIT5;		//ONOFF B
		if (MUX_IN2 )			present_status|=BIT18;
	IN_SEL(0,1,1);  //D
		if( MUX_IN0==0 )	 	present_status|=BIT6;		//VOP OVP
		if( MUX_IN1==0 ) 		present_status|=BIT7;		//Inter Lock B
		if( MUX_IN2 )			present_status|=BIT19;
	IN_SEL(1,0,0);  //E
		if( MUX_IN0==0 ) 		present_status|=BIT8;		//IO OCP
		if( MUX_IN1==0 ) 		present_status|=BIT9;		//Reset B
		if( MUX_IN2 )			present_status|=BIT20;
	IN_SEL(1,0,1);  //F
		if( MUX_IN0==0 ) 		present_status|=BIT10;	//IR1 OCP
		if( MUX_IN1==0 ) 		present_status|=BIT11;	//ONOFF A
		if( MUX_IN2 )			present_status|=BIT21;
	IN_SEL(1,1,0);  //G
		if( MUX_IN0==0 ) 		present_status|=BIT12;	//VO OVP
		if( MUX_IN1==0 ) 		present_status|=BIT13;	//Inter Lock A
		if( MUX_IN2 )			present_status|=BIT22;
	IN_SEL(1,1,1);  //H
		if( MUX_IN0==0 ) 		present_status|=BIT14;	//IR2 OCP
		if( MUX_IN1==0 ) 		present_status|=BIT15;	//Reset A
		if( MUX_IN2 )			present_status|=BIT23;

		GPtest = present_status;
		return ( LpfExtGpioFault( present_status ));*/
	return 0;
}

Uint32 LpfExtGpioFault( Uint32 Input_status)
{
	Uint16 gpio_status;
	Uint16 Checker;
	Uint16 i;
	static float filter[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	gpio_status = 0;

	for( i = 0; i<31; i++ )
	{
		Checker = (Input_status & (BIT0 << i)) ? 1 : 0;
		filter[i] = SW_LPF( filter[i], Checker );			// Active High
		if( filter[i] > 3.0 ) gpio_status |= (BIT0 << i);
		else			   	  gpio_status &=~ (BIT0 << i);
	}

	return (  gpio_status );

}

// software Low Pass Filter Fuction
float SW_LPF( float filter, Uint16 input )
{
	return ((filter * 90) + (input * 100)) / 100;		// Software Low Pass Filter
}
