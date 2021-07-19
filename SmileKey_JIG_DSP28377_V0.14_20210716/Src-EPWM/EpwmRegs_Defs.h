/*
 * EpwmRegs_Defs.h
 *
 *  Created on: 2016. 9. 9.
 *      Author: Yoo Kwang Hyun
 */

#ifndef EPWMREGS_DEFS_H_
#define EPWMREGS_DEFS_H_

// Configure the period for each timer

// PWM Swiching Frequency   Default 200Mhz
#define EPWM_CLOCK			200000000L

#define HW_FAULT_REF_FREQ	100000L		//100Khz
#define HW_F_PRD			EPWM_CLOCK/HW_FAULT_REF_FREQ

//Device tester Switching Setting
#define AD_SAMPLE_FREQ      160000L
#define AD_SAMPLE_PRD       EPWM_CLOCK/AD_SAMPLE_FREQ       //160khz

#define EPWM1_PERIOD  		AD_SAMPLE_PRD
#define EPWM2_PERIOD  		0xfffe
#define EPWM3_PERIOD  		0xfffe
#define EPWM4_PERIOD  		0xfffe
#define EPWM5_PERIOD  		0xfffe
#define EPWM6_PERIOD  		0xfffe
#define EPWM7_PERIOD  		0xfffe
#define EPWM8_PERIOD  		0xfffe
#define EPWM9_PERIOD  		0xfffe
#define EPWM10_PERIOD  		0xfffe
#define EPWM11_PERIOD		0xfffe
#define EPWM12_PERIOD		0xfffe

/* COMP A & B*/
#define EPWM1_CMPA     		EPWM1_PERIOD/2
#define EPWM1_CMPB     		0//EPWM1_PERIOD/3		// 120deg shift

#define EPWM2_CMPA     		0
#define EPWM2_CMPB     		0

#define EPWM3_CMPA     		0
#define EPWM3_CMPB     		0

#define EPWM4_CMPA     		0
#define EPWM4_CMPB     		0

#define EPWM5_CMPA     		0
#define EPWM5_CMPB     		0

#define EPWM6_CMPA     		EPWM6_PERIOD/2
#define EPWM6_CMPB     		EPWM6_PERIOD/2

#define EPWM7_CMPA     		2000
#define EPWM7_CMPB     		2000

#define EPWM8_CMPA     		2000
#define EPWM8_CMPB     		2000

#define EPWM9_CMPA     		2000
#define EPWM9_CMPB     		2000

#define EPWM10_CMPA     	2000
#define EPWM10_CMPB     	0

#define EPWM11_CMPA     		2000
#define EPWM11_CMPB     		2000

#define EPWM12_CMPA     		2000
#define EPWM12_CMPB     		2000
/* Dead Band Rising|Falling Edge Delay */
// 1/PWM clk = per 1 dead band
// default 90Mhz = EPWM CLK --> 1 = 11.11ns
#define EPWM1_DBRED			0			// 200*5ns = 1000ns
#define EPWM1_DBFED			0			// 200*5ns = 1000ns

#define EPWM2_DBRED			0			// 200*5ns = 1000ns
#define EPWM2_DBFED			0			// 200*5ns = 1000ns

#define EPWM3_DBRED			0			// 200*5ns = 1000ns
#define EPWM3_DBFED			0			// 200*5ns = 1000ns

#define EPWM4_DBRED			0
#define EPWM4_DBFED			0

#define EPWM5_DBRED			0
#define EPWM5_DBFED			0

#define EPWM6_DBRED			0
#define EPWM6_DBFED			0

#define EPWM7_DBRED			0
#define EPWM7_DBFED			0

#define EPWM8_DBRED			0
#define EPWM8_DBFED			0

#define EPWM9_DBRED			0
#define EPWM9_DBFED			0

#define EPWM10_DBRED		0
#define EPWM10_DBFED		0

#define EPWM11_DBRED		0
#define EPWM11_DBFED		0

#define EPWM12_DBRED		0
#define EPWM12_DBFED		0

#endif /* EPWMREGS_DEFS_H_ */
