/*
 * F2837x_Adc_Defs.h
 *
 *  Created on: 2016. 9. 12.
 *      Author: Yoo Kwang Hyun
 */

#ifndef HF_F28377D_CPU1_V1_01_SRC_ADC_F2837X_ADC_DEFS_H_
#define HF_F28377D_CPU1_V1_01_SRC_ADC_F2837X_ADC_DEFS_H_


//definitions for selecting ADC resolution
#define RESOLUTION_12BIT 0 //12-bit resolution
#define RESOLUTION_16BIT 1 //16-bit resolution (not supported for all variants)

//definitions for selecting ADC signal mode
#define SIGNAL_SINGLE 0 //single-ended channel conversions (12-bit mode only)
#define SIGNAL_DIFFERENTIAL 1 //differential pair channel conversions


#define TRIGSEL_SW_ONLY				0x0
#define TRIGSEL_CPU1TIMER0			0x1
#define TRIGSEL_CPU1TIMER1			0x2
#define TRIGSEL_CPU1TIMER2			0x3
#define TRIGSEL_EXTGPIO				0x4
#define TRIGSEL_EPWM1_SOCA			0x5
#define TRIGSEL_EPWM1_SOCB			0x6
#define TRIGSEL_EPWM2_SOCA			0x7
#define TRIGSEL_EPWM2_SOCB			0x8
#define TRIGSEL_EPWM3_SOCA			0x9
#define TRIGSEL_EPWM3_SOCB			0xA
#define TRIGSEL_EPWM4_SOCA			0xB
#define TRIGSEL_EPWM4_SOCB			0xC
#define TRIGSEL_EPWM5_SOCA			0xD
#define TRIGSEL_EPWM5_SOCB			0xE
#define TRIGSEL_EPWM6_SOCA			0xF
#define TRIGSEL_EPWM6_SOCB			0x10
#define TRIGSEL_EPWM7_SOCA			0x11
#define TRIGSEL_EPWM7_SOCB			0x12
#define TRIGSEL_EPWM8_SOCA			0x13
#define TRIGSEL_EPWM8_SOCB			0x14
#define TRIGSEL_EPWM9_SOCA			0x15
#define TRIGSEL_EPWM9_SOCB			0x16
#define TRIGSEL_EPWM10_SOCA			0x17
#define TRIGSEL_EPWM10_SOCB			0x18
#define TRIGSEL_EPWM11_SOCA			0x19
#define TRIGSEL_EPWM11_SOCB			0x1A
#define TRIGSEL_EPWM12_SOCA			0x1B
#define TRIGSEL_EPWM12_SOCB			0x1C
#define TRIGSEL_CPU2TIMER0			0x1D
#define TRIGSEL_CPU2TIMER1			0x1E
#define TRIGSEL_CPU2TIMER2			0x1F

#endif /* HF_F28377D_CPU1_V1_01_SRC_ADC_F2837X_ADC_DEFS_H_ */
