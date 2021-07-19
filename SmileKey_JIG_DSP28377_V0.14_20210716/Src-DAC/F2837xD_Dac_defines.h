/*
 * F2837xD_Dac_defines.h
 *
 *  Created on: 2016. 9. 27.
 *      Author: Yoo Kwang hyun
 */

#ifndef DUALFREQ_F28377D_CPU1_V1_01_SRC_DAC_F2837XD_DAC_DEFINES_H_
#define DUALFREQ_F28377D_CPU1_V1_01_SRC_DAC_F2837XD_DAC_DEFINES_H_


//DAC Reference Selection
#define REF_VDC			0
#define REF_VREF_HI		1

//DAC Load Mode
#define LOAD_SYSCLK		0
#define LOAD_PWMCLK		1

//DAC Sync Selection
#define SYNC_EPWM1		0
#define SYNC_EPWM2		1
#define SYNC_EPWM3		2
#define SYNC_EPWM4		3
#define SYNC_EPWM5		4
#define SYNC_EPWM6		5
#define SYNC_EPWM7		6

//DA Enable
#define DA_DISABLE		0
#define DA_ENABLE		1



#endif /* DUALFREQ_F28377D_CPU1_V1_01_SRC_DAC_F2837XD_DAC_DEFINES_H_ */
