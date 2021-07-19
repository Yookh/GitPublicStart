
/*******************************************************************
 *
 *    DESCRIPTION:  Parameters declaration
 *
 *    AUTHOR:		Eun Ji An
 *					Kwang Hyun Yoo
 *
 *    HISTORY:		140929 coding start
 *					160224 adding structure	(control variables)
 *
 *******************************************************************/

/** include files **/

#include "define.h"
/** local definitions **/

/** default settings **/

/** external functions **/
/** public data **/

/** private data **/

/** public functions **/

/** private functions **/
									 // MAX   MIN    DFT
const int SET[M_NUM][SET_NUM][3] =	  {  999,   -999,      0,   //SET_IR_GAIN                 0
										 999,   -999,      0,	//SET_IR_OFFSET               1
										 999,   -999,      0,	//SET_Vbat_GAIN               2
										 999,   -999,      0,   //SET_Vbat_OFFSET             3
										 999,   -999,      0,   //SET_5V_GAIN                 4
										 999,   -999,      0,   //SET_5V_OFFSET               5
										 999,   -999,      0,	//SET_3_3V_GAIN               6
										 999,   -999,      0,	//SET_3_3V_OFFSET             7
										 999,   -999,      0,	//SET_1_8V_GAIN               8
										 999,   -999,      0,   //SET_1_8V_OFFSET             9
                                         999,   -999,      0,   //SET_6V_GAIN                 10
                                         999,   -999,      0,   //SET_6V_OFFSET               11
                                         999,   -999,      0,   //SET_Ichg1_GAIN              12
                                         999,   -999,      0,   //SET_Ichg1_OFFSET            13
                                         999,   -999,      0,   //SET_Ichg2_GAIN              14
                                         999,   -999,      0,   //SET_Ichg2_OFFSET            15
                                         999,   -999,      0,   //SET_Ichg3_GAIN              16
                                         999,   -999,      0,   //SET_Ichg3_OFFSET            17
                                         999,   -999,      0,   //SET_IDC_GAIN                18
                                         999,   -999,      0,   //SET_IDC_OFFSET              19
                                         999,   -999,      0,   //SET_2_5V_GAIN               20
                                         999,   -999,      0,   //SET_2_5V_OFFSET             21
                                         999,   -999,      0,   //SET_1_65V_GAIN              22
                                         999,   -999,      0,   //SET_1_65V_OFFSET            23
                                         100,    100,    100,   //SET_MODEL                   24
                                         14,    14,    14,   //SET_VERSION                 25
										};


const	int ADC_GAIN[]=       	  { 3052,                       // IR
     	                      	    6600,                       // Vbat  : 6.600V
     	                      	    6600,                       // +5V   : 6.600V
     	                      	    4002,                       // +3.3V : 4.002V
     	                      	    4002,                       // +1.8V : 4.002V
     	                      	    6600,                       // +6V   : 6.600V
     	                      	    8250,                       // I chg1: 2.5V offset, 3.3V : 2A = 8.250A
     	                      	   25000,                       // Idc   : 1.65V offset, 3.3V :12.5A = 25.000A
     	                      	    8250,                       // I chg2: 2.5V offset, 3.3V : 2A = 8.250A
     	                      	    3300,                       // +2.5V : 3.300V
     	                      	    3300,                       // +1.65V: 3.300V
     	                      	    8250                        // I chg3: 2.5V offset, 3.3V : 2A = 8.250A
};


const	int AD_PROTECT_LV[]=	  { 1900, 4800,  1900, 4900, 2700, 2700 };
const	int REF_PO_GAIN=			    10000;



