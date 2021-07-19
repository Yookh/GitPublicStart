///////////////////////////////////////////////////////////////////////////////////////////////
//																							 //
//																							 //
//							Modbus_485.h													 //
//																							 //
//																							 //
/////////////////////////////////////////////////////////////////////////////////////////////// 
#include "../define.h"
#include "../DUAL_PARAM.h"

/** local definitions **/
#define CPUCLK      200000000L              // CPU Main Clock
#define LSPCLK      (CPUCLK/4)              // Peripheral Low Speed Clock
#define BoudRate    38400                   //communication Boud rate setup
#define SETRATE     ((LSPCLK/(8*BoudRate))-1)


//---- BIT MESSAGE : CUSTOMER --> P.S
// Write Mode (func 6, 16)
#define MB_SET_CONTROL              0   // <-40011      // write only
    #define MB_AUTO_CALI                BIT0
    #define MB_AUTO_AGING               BIT1
    #define MB_RESET                    BIT3

#define MB_SET_IR_OFFSET            1
#define MB_SET_VBAT_OFFSET          2
#define MB_SET_5V_OFFSET            3
#define MB_SET_3_3V_OFFSET          4
#define MB_SET_1_8V_OFFSET          5
#define MB_SET_6V_OFFSET            6
#define MB_SET_I_Chg1_OFFSET        7
#define MB_SET_IDC_OFFSET           8
#define MB_SET_I_Chg2_OFFSET        9
#define MB_SET_2_5V_OFFSET          10
#define MB_SET_1_65V_OFFSET         11
#define MB_SET_I_Chg3_OFFSET        12
#define MB_SET_IR_GAIN              13
#define MB_SET_VBAT_GAIN            14
#define MB_SET_5V_GAIN              15
#define MB_SET_3_3V_GAIN            16
#define MB_SET_1_8V_GAIN            17
#define MB_SET_6V_GAIN              18
#define MB_SET_I_Chg1_GAIN          19
#define MB_SET_IDC_GAIN             20
#define MB_SET_I_Chg2_GAIN          21
#define MB_SET_2_5V_GAIN            22
#define MB_SET_1_65V_GAIN           23
#define MB_SET_I_Chg3_GAIN          24


// Read Mode (func 3, 4 )
//---- Present Value : P.S--> Customer

#define MB_DATA_STATUS              0
#define MB_DATA_WARNNIG             1
#define MB_DATA_FAULT               2

#define MB_DATA_TARGET1_STATUS      3
#define MB_DATA_TARGET1_FAULT       4
#define MB_DATA_TARGET1_POWER       5
#define MB_DATA_TARGET1_VOLTAGE     6
#define MB_DATA_TARGET1_IDC         7
#define MB_DATA_TARGET1_IR          8
#define MB_DATA_TARGET1_Vbat        9
#define MB_DATA_TARGET1_IChg        10
#define MB_DATA_TARGET1_PHASE       11
#define MB_DATA_TARGET1_VERSION     12
#define MB_DATA_TARGET1_OTP1        13
#define MB_DATA_TARGET1_OTP2        14
#define MB_DATA_TARGET1_ID_LSW      15
#define MB_DATA_TARGET1_ID_MSW      16
#define MB_DATA_TARGET1_FREQ        17
#define MB_DATA_TARGET1_RESERVED2   18
#define MB_DATA_TARGET1_RESERVED3   19
#define MB_DATA_REPORT_IR_OFFSET    20
#define MB_DATA_REPORT_IR_GAIN      21
#define MB_DATA_REPORT_IDC_OFFSET   22
#define MB_DATA_REPORT_IDC_GAIN     23
#define MB_DATA_REPORT_Vbat_GAIN    24
#define MB_DATA_REPORT_IChg_OFFSET  25
#define MB_DATA_REPORT_IChg_GAIN    26
#define MB_DATA_TARGET2_STATUS      27
#define MB_DATA_TARGET2_FAULT       28
#define MB_DATA_TARGET2_POWER       29
#define MB_DATA_TARGET2_VOLTAGE     30
#define MB_DATA_TARGET2_IDC         31
#define MB_DATA_TARGET2_IR          32
#define MB_DATA_TARGET2_Vbat        33
#define MB_DATA_TARGET2_IChg        34
#define MB_DATA_TARGET2_PHASE       35
#define MB_DATA_TARGET2_VERSION     36
#define MB_DATA_TARGET2_OTP1        37
#define MB_DATA_TARGET2_OTP2        38
#define MB_DATA_TARGET2_ID_LSW      39
#define MB_DATA_TARGET2_ID_MSW      40
#define MB_DATA_TARGET2_FREQ        41
#define MB_DATA_TARGET2_RESERVED2   42
#define MB_DATA_TARGET2_RESERVED3   43
#define MB_DATA_TARGET3_STATUS      44
#define MB_DATA_TARGET3_FAULT       45
#define MB_DATA_TARGET3_POWER       46
#define MB_DATA_TARGET3_VOLTAGE     47
#define MB_DATA_TARGET3_IDC         48
#define MB_DATA_TARGET3_IR          49
#define MB_DATA_TARGET3_Vbat        50
#define MB_DATA_TARGET3_IChg        51
#define MB_DATA_TARGET3_PHASE       52
#define MB_DATA_TARGET3_VERSION     53
#define MB_DATA_TARGET3_OTP1        54
#define MB_DATA_TARGET3_OTP2        55
#define MB_DATA_TARGET3_ID_LSW      56
#define MB_DATA_TARGET3_ID_MSW      57
#define MB_DATA_TARGET3_FREQ        58
#define MB_DATA_TARGET3_RESERVED2   59
#define MB_DATA_TARGET3_RESERVED3   60
#define MB_DATA_JIG_IR              61
#define MB_DATA_JIG_V_BAT           62
#define MB_DATA_JIG_5V              63
#define MB_DATA_JIG_3_3V            64
#define MB_DATA_JIG_1_8V            65
#define MB_DATA_JIG_6V              66
#define MB_DATA_JIG_IDC             67
#define MB_DATA_JIG_I_Chg1          68
#define MB_DATA_JIG_I_Chg2          69
#define MB_DATA_JIG_I_Chg3          70
#define MB_DATA_JIG_2_5V            71
#define MB_DATA_JIG_1_65V           72
#define MB_DATA_JIG_SET_IR_OFFSET   73
#define MB_DATA_JIG_SET_Vbat_OFFSET 74
#define MB_DATA_JIG_SET_5V_OFFSET   75
#define MB_DATA_JIG_SET_3_3V_OFFSET 76
#define MB_DATA_JIG_SET_1_8V_OFFSET 77
#define MB_DATA_JIG_SET_6V_OFFSET   78
#define MB_DATA_JIG_SET_Ic1_OFFSET  79
#define MB_DATA_JIG_SET_IDC_OFFSET  80
#define MB_DATA_JIG_SET_Ic2_OFFSET  81
#define MB_DATA_JIG_SET_2_5V_OFFSET 82
#define MB_DATA_JIG_SET_1_65V_OFFSET 83
#define MB_DATA_JIG_SET_Ic3_OFFSET  84
#define MB_DATA_JIG_SET_IR_GAIN     85
#define MB_DATA_JIG_SET_Vbat_GAIN   86
#define MB_DATA_JIG_SET_5V_GAIN     87
#define MB_DATA_JIG_SET_3_3V_GAIN   88
#define MB_DATA_JIG_SET_1_8V_GAIN   89
#define MB_DATA_JIG_SET_6V_GAIN     90
#define MB_DATA_JIG_SET_Ic1_GAIN    91
#define MB_DATA_JIG_SET_IDC_GAIN    92
#define MB_DATA_JIG_SET_Ic2_GAIN    93
#define MB_DATA_JIG_SET_2_5V_GAIN   94
#define MB_DATA_JIG_SET_1_65V_GAIN  95
#define MB_DATA_JIG_SET_Ic3_GAIN    96
#define MB_DATA_JIG_VERSION         97


#define FUNC_4					0x04
#define FUNC_16					0x10
#define FUNC_23					0x17
#define FUNC_3                  0x03
#define FUNC_6                  0x06

/** external Data **/
extern int16	system_status, warning_status;
extern long		flag_set_save1, flag_set_save2, flag_time_save, flag_comm_save;
extern const int SET[M_NUM][SET_NUM][3];
extern Uint16 	dlog_index, dlog_tx_index;
extern unsigned char dlog_tx_flag;
extern int16    ADC_Avg[ADC_NUMBER];

extern Uint16   model, My_Address;


extern C1_2 C12;
extern C2_1 C21;

#define MAX_QUE_MB   500

/** public data **/
unsigned char FUNC_QUE_C[MAX_QUE_MB];	// function code
unsigned char ID_QUE_RD_C[MAX_QUE_MB];	// read address
unsigned char NUM_QUE_RD_C[MAX_QUE_MB];	// Num of read data
unsigned char ID_QUE_WR_C[MAX_QUE_MB];	// write address
unsigned char NUM_QUE_WR_C[MAX_QUE_MB];	// Num of write data
//unsigned char IDC_QUE[MAX_A_QUE], TXC_QUE[MAX_A_QUE];
unsigned char TRANSMIT_QUE_C[MAX_QUE_MB];
int16		  DATA_QUE_WR_C[MAX_QUE_MB], mask_c[MAX_QUE_MB];	// data for write
//int16		  RXC_QUE[MAX_A_QUE];

int16		  flag_RS485_receive_C;

unsigned char start_point_C, end_point_C;
unsigned char start_point_data_C, end_point_data_C;
Uint16		  cnt_T3_5_C, flag_rcv_frame_end_C;
Uint16		  wModData_C[MAX_QUE_MB], MODT_BUFF_C[MAX_QUE_MB], bIdxModR_C, bCntRespDelay_C, Addrs_C;
Uint16		  wMb_control_data_C;

unsigned char transmit_flag_C, transmit_start_C, transmit_end_C;
Uint16		  err_flag_C,	err_ID_C,	err_Code_C, cnt_Reply_C;
int			  flag_RS485_data_new_C;
/** public functions **/
void 	INIT_485_VAR_C(void);
void 	scic_fifo_init(void);
void 	SCIC_CHECK(void);
int 	MaskMBData_C(Uint16 addr);

void	scicRxFifoService_MB(void);
void	scicTxFifoService_MB(void);
void    CheckMessageC_MB(void);

void    MakePktC(byte msg,word wData);
void    MakePkt2RD_C(Uint16 bNum, Uint16* pData, unsigned char function);         // func 0x04 Response
void	MakePkt2WR_C(Uint16 wAddr, Uint16 wNum);			// func 0x10 Response
void    MakePkt2WR_F6_C(Uint16 wAddr, Uint16 wData);      // func 0x06 response
void	MakePkt2Fc17_C(Uint16 bNum, Uint16* pData);		// func 0x17 response
void	MakePkt2ERR_C(Uint16 err_id, Uint16 err_code);
Uint16	CRC16_C(Uint16* pbMsg, Uint16 bDataLen); 			// MB
int 	ChangeValue_485_C(char wID);
void    UpdateBuff_C( Uint16 index );
void    RS485_Comm_check_C(void);
void    SciCAutoBusReset ( void );

void    MODBUS_FUNC_3_C(void);
void 	MODBUS_FUNC_4_C(void);
void 	MODBUS_FUNC_16_C(void);
void 	MODBUS_FUNC_23_C(void);
void    MODBUS_FUNC_6_C(void);

extern Uint16 GetJigStatus( void );
extern Uint16 GetJigFault( void );

/* Table of CRC values for high.order byte */
const byte cbCRCHi_C[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
} ;

/* Table of CRC values for low.order byte */
const byte cbCRCLo_C[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
} ;

/****************************************************************
//	You Must Called by main loop that fast speed loop.
*****************************************************************/
#pragma CODE_SECTION(SCIC_CHECK, "ramfuncs");
void SCIC_CHECK(void)
{
	bCntRespDelay_C++; 	// MB
	if(cnt_T3_5_C++>=3)	// SAMPL_FREQ = 2000Hz, 1=0.5ms
	{					// 3==2.1ms, wait 3.5 charactor times(=911us) ?
		if(ScicRegs.SCIRXST.all & 0x80)	ScicRegs.SCICTL1.all =0x0003;     // Relinquish SCI from Reset

		bIdxModR_C=0;		flag_rcv_frame_end_C=1;
		cnt_T3_5_C=0;		ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
	}
}
/****************************************************************
//	You Must Called by Reset service loutine.
*****************************************************************/
void INIT_485_VAR_C(void)
{
	int i;
	for(i=0;i<MAX_QUE_MB;i++){
		FUNC_QUE_C[i]=0;	ID_QUE_RD_C[i]=0;	NUM_QUE_RD_C[i]=0;	
		ID_QUE_WR_C[i]=0;	NUM_QUE_WR_C[i]=0;
		TRANSMIT_QUE_C[i]=0;	DATA_QUE_WR_C[i]=0; wModData_C[i]=0; MODT_BUFF_C[i]=0;
	}
//	txa_flag=0, txa_start=0, txa_end=0;
//	rxa_end=0, rxa_start=0;

	start_point_C=0; end_point_C=0; start_point_data_C=0; end_point_data_C=0;
	cnt_T3_5_C=0; flag_rcv_frame_end_C=0;	flag_RS485_data_new_C=0;	flag_RS485_receive_C=0;

	bIdxModR_C=0; bCntRespDelay_C=0; Addrs_C=0;	wMb_control_data_C=0;

	transmit_flag_C=0; transmit_start_C=0; transmit_end_C=0;
	err_flag_C=0;	err_ID_C=0;	err_Code_C=0; cnt_Reply_C=0;
} 

/****************************************************************
//	You Must Called by DSP setup service loutine.
*****************************************************************/
void scic_fifo_init()
{
   long bps_val;

   bps_val = SETRATE;

   ScicRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScicRegs.SCIFFRX.bit.RXFIFORESET=1;

   ScicRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,   8 char bits,
                                   // async mode, idle-line protocol
   ScicRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
   ScicRegs.SCICTL2.bit.TXINTENA =0;    //1
   ScicRegs.SCICTL2.bit.RXBKINTENA =0;  //1;
   ScicRegs.SCIHBAUD = bps_val >> 8;        // High Value
   ScicRegs.SCILBAUD = bps_val & 0xff;      // Low Value


   ScicRegs.SCIFFTX.all=0xC000; //c020
//  ScibRegs.SCIFFRX.all=0x0021;    //0021
   ScicRegs.SCIFFCT.all=0x00;

   ScicRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScicRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScicRegs.SCIFFRX.bit.RXFIFORESET=1;
}

//#pragma CODE_SECTION(sciaTxFifoService, "ramfuncs");
void scicTxFifoService_MB(void)
{
	if (transmit_flag_C==1) {
		if (++transmit_start_C>=MAX_QUE_MB) transmit_start_C=0;

		if(transmit_start_C!=transmit_end_C) {
			ScicRegs.SCITXBUF = TRANSMIT_QUE_C[transmit_start_C];
		}
		 else {
			ScicRegs.SCIFFTX.bit.TXFFIENA=0;
			transmit_flag_C=0;
		//	TX_DISABLE;
		}
	}
	if((transmit_flag_C==0)&&(transmit_start_C==transmit_end_C)){
		if(ScicRegs.SCICTL2.bit.TXEMPTY==1) TXC_DISABLE;
	} 


	ScicRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = 0x100;    // Issue PIE ACK
}

#pragma CODE_SECTION(scicRxFifoService_MB, "ramfuncs");
void scicRxFifoService_MB(void)
{
	Uint16 ch, i, num_reg;
//	unsigned char checksum;

//	for(;ScicRegs.SCIFFRX.bit.RXFFST>0;) {
	while(ScicRegs.SCIFFRX.bit.RXFFST>0) {		// 081209 ljt
		ch = ScicRegs.SCIRXBUF.all;
		mask_c[bIdxModR_C++] = ch;
		if(bIdxModR_C>=299) bIdxModR_C=299;
	}
	cnt_T3_5_C=0;

	if((bIdxModR_C>=8)&&((mask_c[0]== My_Address))) {
		switch(mask_c[1]) {
          case FUNC_3:      //V0.01
		  case FUNC_4:	// Read Input Registers(30000~39999:3xxxx)
			if(bIdxModR_C>=8) {
				if(CRC16_C((Uint16 *)mask_c,6)==(mask_c[6]<<8|mask_c[7])) {
				    FUNC_QUE_C[end_point_C]     = mask_c[1];
					ID_QUE_RD_C[end_point_C]	= (Uint16)(mask_c[2]<<8) | (Uint16)(mask_c[3]);		// ID start addr
					NUM_QUE_RD_C[end_point_C]	= (Uint16)(mask_c[4]<<8) | (Uint16)(mask_c[5]);		// Num of ID

					if(++end_point_C>=MAX_QUE_MB) end_point_C=0;
				}
				bIdxModR_C=0;	bCntRespDelay_C=0;
			}
			break;
          case FUNC_6:                                              // function 6 commu service //V0.5
            if(bIdxModR_C>=(6+2)) {
                if(CRC16_C((Uint16 *)mask_c,6)==(mask_c[6+0]<<8 | mask_c[6+1])) {    // support only single write
                    FUNC_QUE_C[end_point_C]   = FUNC_6;
                    ID_QUE_WR_C[end_point_C]  = (Uint16)((mask_c[2]<<8) | mask_c[3]);             // ID start addr
                    DATA_QUE_WR_C[end_point_data_C] = (mask_c[4]<<8) | mask_c[5];     // store data

                    if(++end_point_data_C>=MAX_QUE_MB) end_point_data_C=0;
                    if(++end_point_C>=MAX_QUE_MB) end_point_C=0;
                }
                bIdxModR_C=0; bCntRespDelay_C=0;
            }
            break;
		  case FUNC_16:	// Preset Multiple Registers(40000~49999:4xxxx)
			if(bIdxModR_C>=(7+mask_c[6]+2)) {
				if(CRC16_C((Uint16 *)mask_c,(7+(Uint16)mask_c[6]))==(mask_c[7+mask_c[6]+0]<<8 | mask_c[7+mask_c[6]+1])) {	// support only single write
					FUNC_QUE_C[end_point_C]   = 0x10;
					ID_QUE_WR_C[end_point_C]  = (Uint16)((mask_c[2]<<8) | mask_c[3]);				// ID start addr
					num_reg			  = (mask_c[4]<<8) | mask_c[5];		// Num of ID
					NUM_QUE_WR_C[end_point_C] = num_reg;
		
					for(i=0;i<num_reg;i++) {
						DATA_QUE_WR_C[end_point_data_C]	= (mask_c[7 + i*2]<<8) | mask_c[8 + i*2];		// store data
						if(++end_point_data_C>=MAX_QUE_MB) end_point_data_C=0;
					}

					if(++end_point_C>=MAX_QUE_MB) end_point_C=0;
				}
				bIdxModR_C=0;	bCntRespDelay_C=0;
			}
			break;
		  case FUNC_23:
			if(bIdxModR_C>=(11+mask_c[10]+2)) {
				if(CRC16_C((Uint16*)mask_c,(11+(Uint16)mask_c[10]))==(mask_c[11+mask_c[10]+0]<<8 | mask_c[11+mask_c[10]+1])) {	// support only single write
					FUNC_QUE_C[end_point_C]   = 0x17;
					ID_QUE_RD_C[end_point_C]  = (Uint16)((mask_c[2]<<8) | mask_c[3]);		// ID Read start addr
					NUM_QUE_RD_C[end_point_C] = (Uint16)((mask_c[4]<<8) | mask_c[5]);		// Num of data to Read
					ID_QUE_WR_C[end_point_C]  = (Uint16)((mask_c[6]<<8) | mask_c[7]);		// ID Write start addr
					num_reg 			  = (Uint16)((mask_c[8]<<8) | mask_c[9]);		// Num of data to Write
					NUM_QUE_WR_C[end_point_C] = num_reg;

					for(i=0;i<num_reg;i++) {
						DATA_QUE_WR_C[end_point_data_C] = (mask_c[11 + i*2]<<8) | mask_c[12 + i*2];		// store data
						if(++end_point_data_C>=MAX_QUE_MB) end_point_data_C=0;
					}

					if(++end_point_C>=MAX_QUE_MB) end_point_C=0;
				}
				bIdxModR_C=0;	bCntRespDelay_C=0;
			}
			break;
		  default:
			err_flag_C=1;	err_ID_C=mask_c[1]|0x80;	err_Code_C=01;	// Invalid function error
			break;
		}
	}

	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;	// Clear Overflow flag
	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;	// Clear Interrupt flag
	PieCtrlRegs.PIEACK.all = 0x100;  	// Issue PIE ack
}

#pragma CODE_SECTION(CheckMessageC_MB, "ramfuncs");
void CheckMessageC_MB(void)
{
	/* Received Command processing */
	if (start_point_C != end_point_C)
	{
		switch(FUNC_QUE_C[start_point_C])
		{
            case FUNC_3 : //MODBUS_FUNC_3_C();  break;               //V0.01
			case FUNC_4 : MODBUS_FUNC_4_C();  break;		
			case FUNC_16: MODBUS_FUNC_16_C(); break;
			case FUNC_23 :MODBUS_FUNC_23_C(); break;				// Not Used
            case FUNC_6 : MODBUS_FUNC_6_C();  break;
			default   :	if(err_flag_C && flag_rcv_frame_end_C)
						{
 							MakePkt2ERR_C(err_ID_C, 0x01);			// error - Invalid Function
 							err_flag_C = flag_rcv_frame_end_C = 0;
						}break;
		}
	}
 	/* Transmit Data */
 	if(bCntRespDelay_C>=TD_RESPONSE)	// wait until response delay 3.5 charactor times
 	if (transmit_flag_C==0 && (transmit_start_C != transmit_end_C))
 	{
 		transmit_flag_C = 1;
 		ScicRegs.SCIFFTX.bit.TXFFIENA=0;
 		TXC_ENABLE;
 		ScicRegs.SCITXBUF = TRANSMIT_QUE_C[transmit_start_C];
 	}
} 

//#pragma CODE_SECTION(MakePkt2RD_C, "ramfuncs");
void MakePkt2RD_C(Uint16 bNum, Uint16* pData, unsigned char function)         // func 04 response
{
    Uint16 i;
    Uint16 wData;
    Uint16 bByteCnt, chksum;

    bByteCnt=0;
    MODT_BUFF_C[bByteCnt++]=My_Address;  // low  nibble ascii
    MODT_BUFF_C[bByteCnt++]=function;
    MODT_BUFF_C[bByteCnt++]=bNum*2;
    for(i=0;i<bNum;i++) {
        wData=(Uint16)*(pData+i);
        MODT_BUFF_C[bByteCnt++]=(wData>>8);
        MODT_BUFF_C[bByteCnt++]=(wData & 0xff);
    }
    chksum=CRC16_C(MODT_BUFF_C, bByteCnt);
    MODT_BUFF_C[bByteCnt++]=(char)(chksum>>8);
    MODT_BUFF_C[bByteCnt++]=(char)(chksum&0xff);

    for(i=0;i<bByteCnt;i++) {
        TRANSMIT_QUE_C[transmit_end_C++]=MODT_BUFF_C[i];
        if (transmit_end_C>=MAX_QUE_MB) {
            transmit_end_C=0;
        }
    }
}

/****************************************************************
//  485 communication Function 6  Response
*****************************************************************/
//#pragma CODE_SECTION(MakePkt2WR_F6_C, "ramfuncs");
void MakePkt2WR_F6_C(Uint16 wAddr, Uint16 wData)          // func 0x06 response
{
    Uint16 i, bByteCnt, chksum;

    bByteCnt=0;
    MODT_BUFF_C[bByteCnt++]= My_Address;      // low  nibble ascii
    MODT_BUFF_C[bByteCnt++]=FUNC_6;                   // FUNCTION Return
    MODT_BUFF_C[bByteCnt++]=(wAddr>>8);
    MODT_BUFF_C[bByteCnt++]=(wAddr&0xff);

    MODT_BUFF_C[bByteCnt++]=(wData>>8);
    MODT_BUFF_C[bByteCnt++]=(wData & 0xff);

    chksum=CRC16_C(MODT_BUFF_C, bByteCnt);
    MODT_BUFF_C[bByteCnt++]=(char)(chksum>>8);
    MODT_BUFF_C[bByteCnt++]=(char)(chksum&0xff);

    for(i=0;i<bByteCnt;i++) {
        TRANSMIT_QUE_C[transmit_end_C++]=MODT_BUFF_C[i];
        if (transmit_end_C>=MAX_QUE_MB) {
            transmit_end_C=0;
        }
    }
}

//#pragma CODE_SECTION(MakePkt2WR_C, "ramfuncs");
void MakePkt2WR_C(Uint16 wAddr, Uint16 wNum)			// func 0x10 response
{
	Uint16 i, bByteCnt, chksum;

	bByteCnt=0;
	MODT_BUFF_C[bByteCnt++]= My_Address;	// low  nibble ascii
	MODT_BUFF_C[bByteCnt++]=FUNC_16;
	MODT_BUFF_C[bByteCnt++]=(wAddr>>8);
	MODT_BUFF_C[bByteCnt++]=(wAddr&0xff);
	MODT_BUFF_C[bByteCnt++]=(wNum>>8);
	MODT_BUFF_C[bByteCnt++]=(wNum&0xff);

	chksum=CRC16_C(MODT_BUFF_C, bByteCnt);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum>>8);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum&0xff);

	for(i=0;i<bByteCnt;i++) {
		TRANSMIT_QUE_C[transmit_end_C++]=MODT_BUFF_C[i];
		if (transmit_end_C>=MAX_QUE_MB) {
		    transmit_end_C=0;
		}
	}
}

/****************************************************************
//	485 communication function 17 response 
*****************************************************************/
//#pragma CODE_SECTION(MakePkt2Fc17_C, "ramfuncs");
void MakePkt2Fc17_C(Uint16 bNum, Uint16* pData)		// func 17 response
{
	Uint16 i;
	Uint16 wData;
	Uint16 bByteCnt, chksum;

	bByteCnt=0;
	MODT_BUFF_C[bByteCnt++]= My_Address;	// low  nibble ascii
	MODT_BUFF_C[bByteCnt++]=0x17;
	MODT_BUFF_C[bByteCnt++]=bNum*2;
	for(i=0;i<bNum;i++) {
		wData=(Uint16)*(pData+i);
		MODT_BUFF_C[bByteCnt++]=(wData>>8);
		MODT_BUFF_C[bByteCnt++]=(wData & 0xff);
	}
	chksum=CRC16_C(MODT_BUFF_C, bByteCnt);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum>>8);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum&0xff);
	
	for(i=0;i<bByteCnt;i++) {
		TRANSMIT_QUE_C[transmit_end_C++]=MODT_BUFF_C[i];
		if (transmit_end_C>=MAX_QUE_MB) {
			transmit_end_C=0;
		}
	}
//	TRANSMIT_QUE[transmit_end_C++]=0xff;	// dummy data
//	if (transmit_end_C>=MAX_A_QUE) transmit_end_C=0;
} 

//#pragma CODE_SECTION(MakePkt2ERR, "ramfuncs");
void MakePkt2ERR_C(Uint16 err_id, Uint16 err_code)
{
	Uint16 i, bByteCnt, chksum;

	bByteCnt=0;
	MODT_BUFF_C[bByteCnt++]= My_Address;	// low  nibble ascii
	MODT_BUFF_C[bByteCnt++]= err_id;
	MODT_BUFF_C[bByteCnt++]= err_code;

	chksum=CRC16_C(MODT_BUFF_C, bByteCnt);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum>>8);
	MODT_BUFF_C[bByteCnt++]=(byte)(chksum&0xff);

	for(i=0;i<bByteCnt;i++) {
		TRANSMIT_QUE_C[transmit_end_C]=MODT_BUFF_C[i];
		if (++transmit_end_C>=MAX_QUE_MB) transmit_end_C=0;
	}
}

//#pragma CODE_SECTION(CRC16, "ramfuncs");
Uint16 CRC16_C(Uint16* pbMsg, Uint16 bDataLen)
{
	Uint16 bIndex;
	Uint16 bCRCHi=0xff;
	Uint16 bCRCLo=0xff;

	while(bDataLen--) {
		bIndex=bCRCHi ^ (((Uint16)*(pbMsg++))&0xff);
		bCRCHi=bCRCLo ^ cbCRCHi_C[bIndex];
		bCRCLo=cbCRCLo_C[bIndex];
	}
	return (bCRCHi<<8 | bCRCLo);
}

//#pragma CODE_SECTION(ChangeValue_485, "ramfuncs");
int ChangeValue_485_C(char wID)
{
	int Value;
	if(DATA_QUE_WR_C[start_point_data_C]>SET[model][wID][MAX])		    Value=SET[model][wID][MAX];
	else if(DATA_QUE_WR_C[start_point_data_C]<SET[model][wID][MINIMUM])	Value=SET[model][wID][MINIMUM];
	else 														        Value=DATA_QUE_WR_C[start_point_data_C];

	return Value;
}

void RS485_Comm_check_C(void)
{
    SciCAutoBusReset();

    if(ScicRegs.SCIFFRX.bit.RXFFST>0) scicRxFifoService_MB();
    CheckMessageC_MB();
    if(ScicRegs.SCIFFTX.bit.TXFFST==0) scicTxFifoService_MB();
}

