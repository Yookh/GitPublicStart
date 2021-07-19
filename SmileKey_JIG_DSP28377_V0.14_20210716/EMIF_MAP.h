/**********************************************************************************\
 *  File Name :EMIF_MAP.h
 *
 *  Created on: 2015. 4. 29.
 *      Author: Yoo Gwang Hyun
 *
\**********************************************************************************/
#ifndef DSP_V4_00_CPU1_EMIF_MAP_H_
#define DSP_V4_00_CPU1_EMIF_MAP_H_

/* EMIF-A Base Address Def*/
#define __EMIFA_BASE 	0x2000

/**********************************************************************************\
*  Global Macro declarations
\**********************************************************************************/

/* STACK INDEX Declarations */
#define ADC_VO			0
#define ADC_IO			1


/**********************************************************************************\
*  EMIF-A W-R Macro declarations
\**********************************************************************************/
/*   Read Cmd   */
#define GetEMIFA_EXT(addr, data)\
	DINT; data = *(Uint16 *)(__EMIFA_BASE | addr); EINT;


/*   Write Cmd   */
#define PutEMIFA_EXT(addr, data)\
	DINT; *(Uint16 *)(__EMIFA_BASE | addr) = data; EINT;

/**********************************************************************************\
*  28377 EMIF-A Read Address MAP
\**********************************************************************************/

 /** Read ADDR **/

//=============== page 0 ================== //
#define RD_PAGE0	0  	// STACK index Use Only
// IO
// VO


//=============== page 1 ================== //
#define RD_PAGE1	BIT4

//=============== page 2 ================== //
#define RD_PAGE2	BIT5

//=============== page 3 ================== //
#define RD_PAGE3	BIT4|BIT5


/**********************************************************************************\
*  28377 EMIF-A Write Address MAP
\**********************************************************************************/
//=============== page 0 ================== //
#define WR_PAGE0	0  				// Control Variable Setting

/* Write Page 0 Index Declarations*/
//enum Control_Value {Command=0, Status37, P_GAIN, I_GAIN, INDUCTOR, RO,
//					LFTS, TS4CF, REFIO1, REFT1, REFIO2, REFT2, REFT3, REFT4, PULSE_NUM, VDC_AVG  };

//=============== page 1 ================== //
#define WR_PAGE1	BIT4 			//VDC Sensing Value out page
//x is 0 to 15

#define VDC(x)		WR_PAGE1|(x) 	// 0~15 실제 사용은 8개 0~7 이 외는 reserved

//=============== page 2 ================== //
// page 2  -----------------------
#define WR_PAGE2	BIT5			//Calibration Value page
// page2 STACK index Use Only

#define OFFSET(x)	WR_PAGE2|(x)		// Offset Value Map
// IC
// IF
// VF
// REF
#define GAIN(x)		WR_PAGE2|BIT2|(x)	// GAIN Value Map
// IC
// IF
// VF
// REF -- reserved
#define CALI(x)		WR_PAGE2|BIT3|(x)	// CALI Value Map
// Vo
// Io
//reserved
//reserved

//=============== page 3 ================== //
#define WR_PAGE3	BIT4|BIT5


#endif /* DSP_V4_00_CPU1_EMIF_MAP_H_ */
