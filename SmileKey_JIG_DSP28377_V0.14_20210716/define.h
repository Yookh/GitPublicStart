//***************************************************************************

//---------------------------------------------------------------------------
// Modify : Nov 7, 2016
// Editor : Kwang Hyun Yoo
// 16110		be Quick-_- Dual Freq
//***************************************************************************

#ifndef	DEFINE_H
#define DEFINE_H

#define	byte						char
#define	word						int16

#define	SAMPL_FREQ 					1800	// 1800Hz = 300Hz와 360Hz의 최소공배수
#define FREQ_100mS					180

#define ANALOG_MAX					4095.0f
#define NOT_USED 					30000

#define BIT32   0x100000000
#define BIT33   0x200000000
#define BIT34   0x400000000
#define BIT35   0x800000000
#define BIT36   0x1000000000
#define BIT37   0x2000000000
#define BIT38   0x4000000000
#define BIT39   0x8000000000
#define BIT40   0x10000000000
#define BIT41   0x20000000000
#define BIT42   0x40000000000
#define BIT43   0x80000000000
#define BIT44   0x100000000000
#define BIT45   0x200000000000
#define BIT46   0x400000000000
#define BIT47   0x800000000000

/////////////////////////////////////////////////////////


/*-----------------*/
/* position & unit */
/*-----------------*/
// ADC Variables
#define	M_NUM						2
#define	ADC_NUMBER					12
#define MODULE_NUM                  7
#define DATA_NUM                    6
#define FAULT_NUM					32
#define WARNING_NUM					8

#define	MAX							0
#define	MINIMUM						1
#define	DFT							2

#define SET_NUM						26
#define SET_NUMBER					SET_NUM

#define SET_IR_OFFSET            0
#define SET_Vbat_OFFSET          1
#define SET_5V_OFFSET            2
#define SET_3_3V_OFFSET          3
#define SET_1_8V_OFFSET          4
#define SET_6V_OFFSET            5
#define SET_Ichg1_OFFSET         6
#define SET_IDC_OFFSET           7
#define SET_Ichg2_OFFSET         8
#define SET_2_5V_OFFSET          9
#define SET_1_65V_OFFSET         10
#define SET_Ichg3_OFFSET         11
#define SET_IR_GAIN              12
#define SET_Vbat_GAIN            13
#define SET_5V_GAIN              14
#define SET_3_3V_GAIN            15
#define SET_1_8V_GAIN            16
#define SET_6V_GAIN              17
#define SET_Ichg1_GAIN           18
#define SET_IDC_GAIN             19
#define SET_Ichg2_GAIN           20
#define SET_2_5V_GAIN            21
#define SET_1_65V_GAIN           22
#define SET_Ichg3_GAIN           23
#define SET_MODEL                24
#define SET_VERSION              25


#define	ADDR_HOUR					(SET_NUM)			// 33	!!! Notice
#define	ADDR_MIN					(ADDR_HOUR+1)		// 34
#define	ADDR_SEC					(ADDR_MIN+1)		// 35
#define EEP_END_ADDR				(ADDR_SEC+1)		// (ADDR_SEC+1)		// EEPROM last save address 30

// RUNSTOP
#define STOP0						0
#define RUN0						1

#define ON							1
#define OFF 						0


/*asm(" RPT #100 || NOP");*/

//=======================================================//

#define TXA_ENABLE					{GpioDataRegs.GPCCLEAR.bit.GPIO83= 1;}
#define TXA_DISABLE					{GpioDataRegs.GPCSET.bit.GPIO83 = 1;}
#define TXB_ENABLE                  {GpioDataRegs.GPCCLEAR.bit.GPIO88= 1;}
#define TXB_DISABLE                 {GpioDataRegs.GPCSET.bit.GPIO88 = 1;}
#define TXC_ENABLE                  {GpioDataRegs.GPDCLEAR.bit.GPIO99= 1;}
#define TXC_DISABLE                 {GpioDataRegs.GPDSET.bit.GPIO99 = 1;}

// Relay define.
#define ONOFF_RELAY1(x)   { if(x) GpioDataRegs.GPASET.bit.GPIO22=1;   else    GpioDataRegs.GPACLEAR.bit.GPIO22=1; }
#define ONOFF_RELAY2(x)   { if(x) GpioDataRegs.GPASET.bit.GPIO23=1;   else    GpioDataRegs.GPACLEAR.bit.GPIO23=1; }
#define ONOFF_RELAY3(x)   { if(x) GpioDataRegs.GPASET.bit.GPIO16=1;   else    GpioDataRegs.GPACLEAR.bit.GPIO16=1; }


// Status Output Define
#define STATUS_ONOFF_MODE			BIT0
#define STATUS_READY				BIT1
#define STATUS_RUNNING				BIT2
#define STATUS_SPARE				BIT3
#define STATUS_HEATING_END			BIT4
#define STATUS_CC_MODE				BIT5
#define STATUS_WARNING				BIT6
#define STATUS_FAULT				BIT7
#define STATUS_CAN_MODE				BIT10

#define STATUS_PO					BIT11
#define STATUS_VO					BIT12
#define STATUS_IO					BIT13

// Inport Define
#define IN_SCR_FAULT				BIT0
#define IN_IOP_OCP					BIT1
#define IN_FAN_FAULT				BIT2
#define IN_UVLO						BIT3
#define IN_OTP						BIT4
#define IN_ONOFFB					BIT5
#define IN_VOP_OVP					BIT6
#define IN_INTERLOCKB				BIT7
#define IN_IO_OCP					BIT8
#define IN_RESETB					BIT9
#define IN_IR1_OCP					BIT10
#define IN_ONOFFA					BIT11 //&
#define IN_VO_OVP					BIT12
#define IN_INTERLOCKA				BIT13
#define IN_IR2_OCP					BIT14
#define IN_RESETA					BIT15 //&


// Warning Output Define
#define WARNING_EEP_WR_ERR			BIT3

#define	GOOD						0
//#define	FAULT					1
#define	WARNING						2

/* 	Code List file from Front Panel to Power Supply
	for PSIH-XXXXXF Induction Heating Power Supply

	receive 	->	DSP to Front Panel
	send		->	Front Panel to DSP

	2010.08.10	Listed by Hwanho Sung			*/

/*	Communication Parameters 	*/
#define ID_START            0x02
#define ID_END              0x03
#define ID_COM_OK           0x99
#define ID_COM_CUT          0x66
#define ID_FAULT            0x06
#define ID_WARNING          0x07
#define ID_RESET            0x08
#define ID_MSG_RESET        0xD0
#define ID_MSG_FAN_ON       0xD1
#define ID_MSG_SHUT_L       0xD2
#define ID_MSG_SHUT_R       0xD3

#define ID_REQ_CMD          0x09
#define ID_REQ_DATA         0x0A
#define ID_EOD              0x0B    // End of Download
#define ALL                 0xFFFF
#define DEFAULT_ALL         0xFFFE

/*	Commands from Front Panel to DSP	*/
#define ID_CMD_RUN          0xf0
#define ID_CMD_STOP         0xff
#define ID_CMD_POWER        0xf2
#define ID_CMD_TEMP         0xf3
#define ID_CMD_TEMP_CTRL    0xf5

// remote mode
#define	LOCAL						0
#define	REMOTE						1

#define	MY_ADDR						1
#define	TD_RESPONSE					3		// 1.4ms=2*700us(=1/1.44), 911us(3.5 charactor times response delay)

#define ST_RUN          1
#define ST_STOP         0

#define INTERNAL        0

enum R_MODE{ST_R_BUILD_VOC=0, ST_R_STOP, ST_R_RESTART, ST_R_NORMAL_WAIT,  ST_R_NORMAL, ST_R_FAIL};

#define AD_IR           0
#define AD_VBAT         1
#define AD_P5V          2
#define AD_P3_3V        3
#define AD_P1_8V        4
#define AD_P6V          5
#define AD_I_Chg1       6
#define AD_IDC          7
#define AD_I_Chg2       8
#define AD_P2_5V        9
#define AD_P1_65V       10
#define AD_I_Chg3       11



#define	LIMITER(data, min, max)\
	data = (data > max) ? max : data; \
	data = (data < min) ? min : data;

#define ADC_CH( ch , y )	Adc##ch##ResultRegs.ADCRESULT##y



#endif	// end of #ifndef DEFINE_H

