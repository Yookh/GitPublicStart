/*
 * ADC_Config_F28377.c
 *
 *  Created on: 2016. 9. 12.
 *      Author: Yoo Kwang Hyun
 */
#include "F28x_Project.h"
#include "F2837x_Adc_Defs.h"


void Initialize_ADC( void );

void ConfigureADC( void );
void SetupADCEpwm( void );
void AdcChannelSel( void );
void AdcTrigSelect( void );
void AdcSnHWindow( int acqps );

void EpwmSoc_Cfg ( Uint16 PwmCh, Uint16 Event );
void AdcInt_Cfg( void );

void Initialize_ADC( void )
{
	Uint16 acqps;
	ConfigureADC();
	AdcChannelSel();
	AdcTrigSelect();

	//분해능에 따른 minimum acquisition window (S/H 시간) 설정
	if(RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
	{
		acqps = 14; //75ns = (ACQPS+1)/SYSCLK  14
	}
	else
	{ //resolution is 16-bit
		acqps = 63; //320ns = (ACQPS+1)/SYSCLK
	}

	AdcSnHWindow(acqps);
	EpwmSoc_Cfg(1, ET_CTRU_CMPA );		// SOC EVENT Ch = Pwm Ch1 , timing = when Up-count direction meet Compare A.
	AdcInt_Cfg();

}

//Write ADC configurations and power up the ADC for both ADC A and ADC B
void ConfigureADC(void)
{
	EALLOW;
	//-- ADC A ------------------------------------------------------------------------------//
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // ADCCLK = SYSCLK / 4
	AdcaRegs.ADCCTL2.bit.RESOLUTION = RESOLUTION_12BIT; // 12비트 분해능 모드
	AdcaRegs.ADCCTL2.bit.SIGNALMODE = SIGNAL_SINGLE; // Single-Ended 모드
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; //Set pulse positions to late
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;	// ADC 시동(Power-up)

	//-- ADC B ------------------------------------------------------------------------------//
	AdcbRegs.ADCCTL2.bit.PRESCALE = 6; // ADCCLK = SYSCLK / 4
	AdcbRegs.ADCCTL2.bit.RESOLUTION = RESOLUTION_12BIT; // 12비트 분해능 모드
	AdcbRegs.ADCCTL2.bit.SIGNALMODE = SIGNAL_SINGLE; // Single-Ended 모드
	AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1; //Set pulse positions to late
	AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;	// ADC 시동(Power-up)

	//-- ADC C ------------------------------------------------------------------------------//
	AdccRegs.ADCCTL2.bit.PRESCALE = 6; // ADCCLK = SYSCLK / 4
	AdccRegs.ADCCTL2.bit.RESOLUTION = RESOLUTION_12BIT; // 12비트 분해능 모드
	AdccRegs.ADCCTL2.bit.SIGNALMODE = SIGNAL_SINGLE; // Single-Ended 모드
	AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1; //Set pulse positions to late
	AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;	// ADC 시동(Power-up)

	//-- ADC D ------------------------------------------------------------------------------//
	AdcdRegs.ADCCTL2.bit.PRESCALE = 6; // ADCCLK = SYSCLK / 4
	AdcdRegs.ADCCTL2.bit.RESOLUTION = RESOLUTION_12BIT; // 12비트 분해능 모드
	AdcdRegs.ADCCTL2.bit.SIGNALMODE = SIGNAL_SINGLE; // Single-Ended 모드
	AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1; //Set pulse positions to late
	AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;	// ADC 시동(Power-up)

	AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 1;		 // ADC Interrupt Pulse Position: 변환종료 후 발생
	//delay for 1ms to allow ADC time to power up
	DELAY_US(1000);		// ADC가 시동되는 동안 1ms 지연
	EDIS;
}

void AdcChannelSel( void )
{
	EALLOW;
	//Select the channels to convert and end of conversion flag
    //-- ADC A ----------------------------------------------------------------------//
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //VDSS Sensing
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;  //VDSS Sensing
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;  //VDSS Sensing
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;  //VDSS Sensing
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;

    //-- ADC B ----------------------------------------------------------------------//
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;  //VDSS Sensing
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 1;  //VDSS Sensing
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;  //VDSS Sensing
    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 3;  //VDSS Sensing

    //-- ADC C ----------------------------------------------------------------------//
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 0;  //Vth Sensing
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 1;  //Vth Sensing
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2;  //Vth Sensing
    AdccRegs.ADCSOC3CTL.bit.CHSEL = 3;  //Vth Sensing
    AdccRegs.ADCSOC4CTL.bit.CHSEL = 4;
//  AdccRegs.ADCSOC5CTL.bit.CHSEL = 5;

    //-- ADC D ----------------------------------------------------------------------//
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;  //Vth Sensing
    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 1;  //Vth Sensing
    AdcdRegs.ADCSOC2CTL.bit.CHSEL = 2;  //Vth Sensing
    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 3;  //Vth Sensing
    AdcdRegs.ADCSOC4CTL.bit.CHSEL = 4;

	EDIS;
}

void AdcTrigSelect( void )
{
	EALLOW;
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA; //trigger on ePWM1 SOCA
//	AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA; //trigger on ePWM1 SOCA

	AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;

	AdccRegs.ADCSOC0CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdccRegs.ADCSOC1CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdccRegs.ADCSOC2CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdccRegs.ADCSOC3CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdccRegs.ADCSOC4CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA; //trigger on ePWM1 SOCA

	AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA;
	AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = TRIGSEL_EPWM1_SOCA; //trigger on ePWM1 SOCA
	EDIS;
}

void AdcSnHWindow( int acqps )
{
	// if Acqps 6 : Sample window is 7 cycles long (6 + 1 clock cycles).
	// system Clock = 200Mhz, 1 Cycle = 5ns

	// Invaild Selection Protect.
	acqps = (acqps < 1 ) ? 1  : acqps;			    //minimum Value Allowed is 6. system Clock 1 cylce :(10 ns).
	acqps = (acqps > 512 )? 512 : acqps;			//Maximum Value Allowed is system Clock  513 cycle :(2.565 us).

	// Configuration Sample & Hold Window.
	EALLOW;
	AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles

	//-- ADC B ----------------------------------------------------------------------//
	AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles

	//-- ADC C ----------------------------------------------------------------------//
	AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdccRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdccRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles

	//-- ADC D ----------------------------------------------------------------------//
	AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	AdcdRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 15 SYSCLK cycles
	EDIS;
}

void EpwmSoc_Cfg ( Uint16 PwmCh, Uint16 Event )
{
	volatile struct EPWM_REGS* SOCPwmCh;

	if(( PwmCh == 0 ) && ( PwmCh > 10 )) return;						// invalid parameters.
	if( Event > 7) 					 	 return;						// invalid parameters.

	SOCPwmCh = &EPwm1Regs + (PwmCh-1);
	// Choose Trigger Selection.	////////////////////////

	EALLOW;
	SOCPwmCh->ETSEL.bit.SOCAEN = 1;         		// Enable SOC on A group
	SOCPwmCh->ETSEL.bit.SOCBEN = 1;         		// Enable SOC on B group
	SOCPwmCh->ETSEL.bit.SOCASEL = Event; 		//Select SOCA on compare B event
	SOCPwmCh->ETSEL.bit.SOCBSEL = Event; 		//Select SOCB on compare B event
	SOCPwmCh->ETPS.bit.SOCAPRD = 1;         		// Generate pulse on 1st event
	SOCPwmCh->ETPS.bit.SOCBPRD = 1;         		// Generate pulse on 1st event
	EDIS;
}

void AdcInt_Cfg( void )
{
	EALLOW;
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 1; 	//end of SOC1 will set INT1 flag
	AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   	//enable INT1 flag
	AdcaRegs.ADCINTFLGCLR.all = 1; 			//make sure INT1 flag is cleared

	AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 1; 	//end of SOC1 will set INT1 flag
	AdcbRegs.ADCINTSEL1N2.bit.INT1E = 0;   	//enable INT1 flag
	AdcbRegs.ADCINTFLGCLR.all = 1; //make sure INT1 flag is cleared

	AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 1; 	//end of SOC1 will set INT1 flag
	AdccRegs.ADCINTSEL1N2.bit.INT1E = 0;   	//enable INT1 flag
	AdccRegs.ADCINTFLGCLR.all = 1; 			//make sure INT1 flag is cleared

	AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 1; 	//end of SOC1 will set INT1 flag
	AdcdRegs.ADCINTSEL1N2.bit.INT1E = 0;   	//enable INT1 flag
	AdcdRegs.ADCINTFLGCLR.all = 1; 			//make sure INT1 flag is cleared
	EDIS;
}
